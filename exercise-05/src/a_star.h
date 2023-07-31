#include <algorithm>
#include <functional>
#include <limits>
#include <map>
#include <set>

#include "vlib/bag.h"
#include "vlib/index_min_pq.h"
#include "weighted_struct_digraph.h"

#define plane_speed 900.0

using namespace std;

template <typename T>
Bag<T> a_star(
    const WeightedStructDigraph<T>& sdg, const T& source, const T& dest,
    function<float(const WeightedStructDigraph<T>&, const T&, const T&)>
        heuristic) {
    // return empty path if source or destination are not in the graph
    if (!sdg.contains(source) || !sdg.contains(dest)) {
        return Bag<T>();
    }

    int src_idx = sdg.index_of(source);
    int dest_idx = sdg.index_of(dest);

    // priority queue of open nodes
    IndexMinPQ<float> open(sdg.get_graph()->V());
    open.insert(src_idx, 0.0);

    // set of closed nodes
    set<T> closed;

    // map of costs to reach each node
    map<int, float> costs;
    for (auto v = 0; v < sdg.get_graph()->V(); v++)
        costs[v] = numeric_limits<float>::infinity();
    costs[src_idx] = 0.0;

    // map of parents of each node
    map<int, int> parents;

    // while there are nodes to visit
    while (!open.is_empty()) {
        // get node with lowest cost
        int v = open.del_min();

        // check if we reached the destination
        if (v == dest_idx) {
            Bag<T> path;

            // reconstruct the path
            for (auto node = dest_idx; node != src_idx; node = parents[node]) {
                path.add(sdg.name_of(node));
            }
            path.add(source);
            return path;
        }

        // add the node to the closed set
        closed.insert(sdg.name_of(v));

        // for each neighbor of v
        for (auto e : sdg.get_graph()->adj(v)) {
            int w = e.to();

            // if the neighbor is in the closed set, skip it
            if (closed.find(sdg.name_of(w)) != closed.end()) continue;

            // calculate the cost to reach the neighbor
            float new_cost = costs[v] + e.weight();

            // if cost is lower than the one we already have, update it, add
            // v as the parent of w and add w to the open set
            if (new_cost < costs[w]) {
                costs[w] = new_cost;
                parents[w] = v;

                float h = heuristic(sdg, sdg.name_of(w), dest) / plane_speed;
                if (open.contains(w)) {
                    open.decrease_key(w, new_cost + h);
                } else {
                    open.insert(w, new_cost + h);
                }
            }
        }
    }

    // no path found
    return Bag<T>();
}
