#include <fstream>
#include <iomanip>
#include <iostream>
#include <queue>
#include <string>

#include "BloomFilter.h"
#include "hash.h"

using namespace std;

int main(int argc, char **argv) {
    // check number of arguments
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <path_to_file>" << endl;
        return 1;
    }

    // open file
    ifstream file(argv[1]);
    if (!file.is_open()) {
        cerr << "Error opening file" << endl;
        return 1;
    }

    // configure bloom filter
    const int filter_size = 975242344;
    const size_t no_of_hashes = 17;

    BloomFilter<string, no_of_hashes> bloom_filter(
        filter_size, hash_key<string, no_of_hashes>);

    // count number of unique 12 character strings
    const int string_length = 12;
    int no_of_unique_12_character_strings = 0;

    // read characters from file
    char c;
    string current_string;
    while (file.get(c)) {
        // ignore whitespace
        if (c <= 32) {
            continue;
        }

        current_string += c;
        if (current_string.length() == string_length) {
            // add string to bloom filter if not already present
            if (!bloom_filter.contains(current_string)) {
                bloom_filter.add(current_string);
                no_of_unique_12_character_strings++;
            }

            // remove first character
            current_string.erase(0, 1);
        } else {
            continue;
        }
    }

    // print results
    cout << "Number of unique 12 character strings: "
         << no_of_unique_12_character_strings << endl;

    return 0;
}
