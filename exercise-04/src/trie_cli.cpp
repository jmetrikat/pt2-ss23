#include <array>
#include <fstream>
#include <iostream>
#include <queue>

#include "trie.h"

using namespace std;

int main(int argc, char const *argv[]) {
    // check number of arguments
    if (argc != 3) {
        cerr << "Usage: " << argv[0]
             << " <path-to-chromosome> <path-to-csv>"
             << std::endl;
        return 1;
    }

    // open file1 to create trie with all substrings of length 12
    ifstream file1(argv[1]);
    if (!file1.is_open()) {
        cerr << "Error opening file" << endl;
        return 1;
    }

    // create trie
    Trie<char, int, 5> root(strtoarr<5>("ACGTN"));

    // read characters from file
    char c;
    string current_string;
    size_t string_length = 12;
    while (file1.get(c)) {
        // ignore whitespace
        if (c <= 32) {
            continue;
        }

        current_string += c;
        if (current_string.length() == string_length) {
            // add string to bloom filter if not already present
            root.add(strtoarr<12>(current_string), 0);

            // remove first character
            current_string.erase(0, 1);
        } else {
            continue;
        }
    }

    // open file2 to check if substrings of length 12 are present in trie
    ifstream file2(argv[2]);
    if (!file2.is_open()) {
        cerr << "Error opening file" << endl;
        return 1;
    }

    string line;
    while (getline(file2, line)) {
        if (root.contains(strtoarr<12>(line))) {
            cout << "1" << endl;
        } else {
            cout << "0" << endl;
        }
    }

    file1.close();
    file2.close();

    return 0;
}
