#pragma once

#include <array>
#include <cassert>
#include <cmath>
#include <functional>
#include <iostream>
#include <string>
#include <random>
#include <algorithm>
#include <climits>
#include <cstdlib>
#include <cstring>

long djb2(long key) {
    return ((key << 5) + key);
}

long djb2(const std::string key) {
    long val = 5381;
    char c;
    for(int i = 0; i < key.length(); i++) {
        std::memcpy(&c, &key[i], sizeof(char));
        val += djb2(val) + static_cast<long>(c);
    }
    return val;
}

template <typename T>
long djb2(const T& key) {
    if(std::is_same_v<T, std::string>) return djb2(key);
    long val = 5381;
    char c;
    for(int i = 0; i < sizeof(key); i++) {
        std::memcpy(&c, (&key)+i, sizeof(char));
        val += djb2(val) + static_cast<long>(c);
    }
    return val;
}

template <typename T, std::size_t N>
std::array<long, N> hash_key(const T& key) {


    auto hashes = std::array<long, N>();
    hashes[0] = djb2<T>(key);
    for(int i = 1; i < N; i++) {
        hashes[i] = (hashes[i-1]);
    }
    return hashes;

    // std::hash<T> init_hasher;
    // std::hash<std::string> hash_hasher;
    // auto hashes = std::array<long, N>();
    // hashes[0] = (long) init_hasher(key);
    // for(int i = 1; i < N; i++) {
    //     hashes[i] = (long) hash_hasher(std::to_string(hashes[i-1]));
    // }
    // return hashes;
}
