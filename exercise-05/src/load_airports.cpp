#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "weighted_struct_digraph.h"

using namespace std;

struct Airport {
    int id;
    string iata;
    float lat;
    float lon;
    bool operator<(const Airport& rhs) const { return id < rhs.id; }
    bool operator>(const Airport& rhs) const { return id > rhs.id; }
    bool operator==(const Airport& rhs) const { return id == rhs.id; }
};

WeightedStructDigraph<Airport>* load_data(string airports_file,
                                          string routes_file) {
    // read airports
    ifstream file1(airports_file);
    if (!file1.is_open()) {
        std::cerr << "Could not open file " << airports_file << std::endl;
        exit(1);
    }

    // store iata with corresponding id for later use
    Bag<Airport> airports;
    string line;

    // read line by line from airports csv
    while (getline(file1, line)) {
        string token;
        vector<string> tokens;
        stringstream ss(line);

        // use stringstream to split line by comma
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        // if line is valid, add airport to graph with id, iata, lat, lon
        if (tokens.size() == 18) {
            int id = stoi(tokens[0]);
            string iata = tokens[4] == "\\N" ? tokens[5] : tokens[4];
            float lat = stof(tokens[6]);
            float lon = stof(tokens[7]);
            airports.add(Airport{id, iata, lat, lon});
            tokens.clear();
        } else {
            cerr << "Invalid airport: " << line << endl;
            tokens.clear();
        }
    }

    WeightedStructDigraph<Airport>* wsdg =
        new WeightedStructDigraph<Airport>(airports);

    // read routes
    ifstream file2(routes_file);
    if (!file2.is_open()) {
        std::cerr << "Could not open file " << routes_file << std::endl;
        exit(1);
    }

    // read line by line from routes csv
    while (getline(file2, line)) {
        string token;
        vector<string> tokens;
        stringstream ss(line);

        // use stringstream to split line by comma
        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        // if line is valid, add route from source to destination with distance
        if (tokens.size() == 9) {
            int source = stoi(tokens[3]);
            int destination = stoi(tokens[5]);
            float distance = stof(tokens[8]);
            wsdg->add_edge(Airport{source}, Airport{destination}, distance);
            tokens.clear();
        } else {
            cerr << "Invalid route: " << line << endl;
            tokens.clear();
        }
    }

    return wsdg;
}
