#pragma once

#include <array>
#include <functional>
#include <iostream>
#include <vector>

template <typename T, std::size_t N>
class BloomFilter {
   private:
    // dynamic array to store the bloomfilter
    std::vector<char> filter;
    // polymorphic function pointer to the key hash function
    std::function<std::array<long, N>(T &)> key_function;
    // configurable size of the filter
    int filter_size;

   public:
    // constructor
    BloomFilter(int filter_size,
                std::function<std::array<long, N>(T &)> key_function) {
        this->filter_size = filter_size;
        this->key_function = key_function;
        filter = std::vector<char>(filter_size, 0);
    }

    // helper function to get the index of a key in the filter
    int key_idx(long key) {
        int idx = key % filter_size;
        return idx < 0 ? idx + filter_size : idx;
    }

    // returns the fill ratio of the filter
    float fill_ratio() {
        float count = 0;
        for (auto i = 0; i < filter_size; i++) {
            if (filter[i] == 1) {
                count++;
            }
        }
        return count / filter_size;
    }

    // adds an item to the filter
    void add(T &item) {
        for (auto key : key_function(item)) {
            filter[key_idx(key)] = 1;
        }
    }

    // returns false if item is definitely not in the set, true if it might be
    bool contains(T &item) {
        for (auto key : key_function(item)) {
            if (filter[key_idx(key)] == 0) {
                return false;
            }
        }
        return true;
    }
};
