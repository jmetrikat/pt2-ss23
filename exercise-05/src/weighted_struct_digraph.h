/******************************************************************************
 *
 * A directed graph, where the vertex names are arbitrary strings.
 *
 * Based on the source code from Robert Sedgewick and Kevin Wayne at
 *https://algs4.cs.princeton.edu/
 *
 ******************************************************************************/

#ifndef __STRUCT_DIGRAPH_H__
#define __STRUCT_DIGRAPH_H__

#include <string>

#include "vlib/edge.h"
#include "vlib/redblack_bst.h"
#include "vlib/weighted_digraph.h"

using namespace std;

// Implements a class representing a directed graph, where the vertex names are
// arbitrary strings
template <typename Node>
class WeightedStructDigraph {
    RedBlackBST<Node, int>* st;  // struct -> index
    Node* keys;                  // index -> struct
    EdgeWeightedDigraph* graph;  // the underlying graph

   public:
    // vector constructor
    WeightedStructDigraph(Bag<Node>& nodes) {
        // add nodes to the symbol table to associate strings with indices
        st = new RedBlackBST<Node, int>();
        for (auto node : nodes) {
            st->put(node, st->size());
        }

        // build the inverse index
        keys = new Node[st->size()];
        for (auto node : nodes) {
            keys[*(st->get(node))] = node;
        }

        // build the graph
        graph = new EdgeWeightedDigraph(st->size());
    }

    // constructor
    WeightedStructDigraph() {
        st = new RedBlackBST<Node, int>();
        keys = new Node[st->size()];
        graph = new EdgeWeightedDigraph(st->size());
    }

    // copy constructor
    WeightedStructDigraph(const WeightedStructDigraph& wsdg) {
        st = new RedBlackBST<Node, int>(*wsdg.st);
        graph = new EdgeWeightedDigraph(*wsdg.graph);
        keys = new Node[graph->V()];
        for (auto v = 0; v < graph->V(); v++) keys[v] = wsdg.keys[v];
    }

    // move constructor
    WeightedStructDigraph(WeightedStructDigraph&& wsdg)
        : st(wsdg.st), keys(wsdg.keys), graph(wsdg.graph) {
        wsdg.st = nullptr;
        wsdg.keys = nullptr;
        wsdg.graph = nullptr;
    }

    // copy assignment
    WeightedStructDigraph& operator=(const WeightedStructDigraph& wsdg) {
        // free the existing lists, map and graph
        delete st;
        delete[] keys;
        delete graph;

        // copy the symbol graph passed in
        st = new RedBlackBST<Node, int>(*wsdg.st);
        graph = new EdgeWeightedDigraph(*wsdg.graph);
        keys = new Node[graph->V()];
        for (auto v = 0; v < graph->V(); v++) keys[v] = wsdg.keys[v];
        return (*this);
    }

    // move assignment
    WeightedStructDigraph& operator=(WeightedStructDigraph&& wsdg) {
        // free the existing lists, map and graph
        delete st;
        delete[] keys;
        delete graph;

        // copy the symbol graph passed in
        st = wsdg.st;
        graph = wsdg.graph;
        keys = wsdg.keys;
        wsdg.st = nullptr;
        wsdg.keys = nullptr;
        wsdg.graph = nullptr;
        return (*this);
    }

    // destructor
    ~WeightedStructDigraph() {
        delete st;
        delete[] keys;
        delete graph;
    }

    // checks if the graph contains the vertex named s
    bool contains(const Node& s) const { return st->contains(s); }

    // returns the index associated with the vertex named s from load_airports
    int index_of(const Node& s) const { return *(st->get(s)); }

    // returns the name of the vertex associated with the index v
    Node name_of(const int v) const { return keys[v]; }

    // returns the underlying edge-weighted digraph
    const EdgeWeightedDigraph* get_graph() const { return graph; }

    // add an edge to the graph
    void add_edge(const Node& v, const Node& w, const double weight) {
        const auto* idx_v = st->get(v);
        const auto* idx_w = st->get(w);
        if (idx_v == nullptr || idx_w == nullptr) return;
        graph->add_edge(Edge(index_of(v), index_of(w), weight));
    }
};

#endif
