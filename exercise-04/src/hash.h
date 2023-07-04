#pragma once

#include <array>
#include <cassert>
#include <cmath>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

// create N hashes from the standard hash function and return them in an array
// function implements approach 1: generate hashes by hashing the previous one
template <typename T, std::size_t N>
std::array<long, N> hash_key(const T& a) {
    std::hash<T> hash_fn;
    std::array<long, N> hash_values;

    hash_values[0] = hash_fn(a);
    for (auto i = 1; i < N; i++) {
        hash_values[i] = hash_fn(std::to_string(hash_values[i - 1]));
    }

    return hash_values;
}
