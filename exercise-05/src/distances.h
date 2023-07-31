#ifndef __DISTANCES_H
#define __DISTANCES_H
#include <cmath>

#include "weighted_struct_digraph.h"

// In all of these cases I assume that a and b are of the same type
// and that a is the current node and b is the node I want to go to

// Earth's radius in kilometers (use this one)
const double EARTH_RADIUS = 6371.0;

template <typename T>
float haversine(const WeightedStructDigraph<T> &g, const T &a, const T &b) {
    // I return the geodesic distance between a and b
    // Meaning the distance on a great circle.

    // convert lat and lon from degrees to radians
    float lat1 = a.lat * M_PI / 180;
    float lat2 = b.lat * M_PI / 180;
    float lon1 = a.lon * M_PI / 180;
    float lon2 = b.lon * M_PI / 180;

    // haversine formula
    return 2 * EARTH_RADIUS *
           asin(sqrt(pow(sin((lat2 - lat1) / 2), 2) +
                     pow(sin((lon2 - lon1) / 2), 2) * cos(lat1) * cos(lat2)));
}

template <typename T>
float euclidean(const WeightedStructDigraph<T> &sdg, const T &a, const T &b) {
    /*
    I return the euclidean distance between a and b
    S . . . .
    . \ . . .
    . . \ . .
    . . . Z .
    . . . . .
    */
    // use pythagorean theorem to calculate the distance
    return sqrt(pow(min(abs(a.lat - b.lat), 360 - abs(a.lat - b.lat)), 2) +
                pow(min(abs(a.lon - b.lon), 360 - abs(a.lon - b.lon)), 2));
};

template <typename T>
float manhattan(const WeightedStructDigraph<T> &g, const T &a, const T &b) {
    /*
    I return the manhattan distance between a and b
    S - - ┐ .
    . . . | .
    . . . | .
    . . . Z .
    . . . . .
    */
    // add absolute differences of lat and lon
    return min(abs(a.lat - b.lat), 360 - abs(a.lat - b.lat)) +
           min(abs(a.lon - b.lon), 360 - abs(a.lon - b.lon));
};

template <typename T>
float out_degree(const WeightedStructDigraph<T> &g, const T &a, const T &b) {
    // I return a heuristik which is dependend on the outdegree of b
    // meaning the number of edges going out of b
    return -g.get_graph()->outdegree(g.index_of(b));
};

#endif
