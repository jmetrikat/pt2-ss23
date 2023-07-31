#include <iostream>
#include <string>

#include "../src/a_star.h"
#include "../src/distances.h"
#include "../src/load_airports.cpp"
#include "../src/weighted_struct_digraph.h"

using namespace std;

int main(int argc, char* argv[]) {
    // check number of arguments
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <src> <dest>" << std::endl;
        return 1;
    }

    // load airports and routes
    const WeightedStructDigraph<Airport>* wsdg =
        load_data("../data/airports.csv", "../data/routes.csv");

    // get source and destination airports
    Airport src, dest;
    for (int i = 0; i < wsdg->get_graph()->V(); i++) {
        if (wsdg->name_of(i).iata == argv[1]) {
            src = wsdg->name_of(i);
        }
        if (wsdg->name_of(i).iata == argv[2]) {
            dest = wsdg->name_of(i);
        }
    }

    // check if source and destination airports are valid
    if (src.iata == "" || dest.iata == "") {
        cerr << "Invalid source or destination airport" << endl;
        return 1;
    }

    // run a* algorithm to find shortest path
    Bag<Airport> path = a_star<Airport>(*wsdg, src, dest, euclidean<Airport>);

    // print path
    float total_duration = 0;
    if (path.size() == 0) {
        // no path found
        cout << "-" << endl
             << "inf" << endl;
    } else {
        // path found
        for (auto i = 0; i < path.size() - 1; i++) {
            cout << path[i].iata << "-";

            // find airline with shortest travel duration
            double min = std::numeric_limits<double>::max();

            // calculate distance from current airport to next airport and add
            for (auto e : wsdg->get_graph()->adj(wsdg->index_of(path[i]))) {
                if (e.to() == wsdg->index_of(path[i + 1]) && e.weight() < min) {
                    min = e.weight();
                }
            }
            total_duration += min;
        }
        cout << path[path.size() - 1].iata << endl;

        // print distance
        cout << total_duration << endl;
    }

    return 0;
}
