#ifndef __TRIE_H__
#define __TRIE_H__

#include <array>
#include <cassert>
#include <functional>
#include <map>

#include "st.h"

// I am also used in the tests. So do not change me! :)
// I am also useful for the implementation of the Trie CLI ;)
template <std::size_t N>
std::array<char, N> strtoarr(const std::string &s) {
    assert(s.size() == N);
    std::array<char, N> arr;
    for (int i = 0; i < N; i++) {
        arr[i] = (char)s[i];
    }
    return (arr);
}

// Trie
template <typename Key, typename Value, size_t U>
class Trie {
    struct Node {
        Key key;
        Value val;
        int size;
        // how would you represent the multiple paths?
        bool is_end;
        std::map<Key, Node *> children;

        // constructor with values
        Node(const Key &k, const Value &v, const int s, bool e, std::map<Key, Node *> c)
            : key(k), val(v), size(s), is_end(e), children(c) {}
    };
    Node *root;  // root of the search forest
    // you will need to save the allowed alphabet somewhere
    // be mindful that you need a fast structure here
    std::array<Key, 5> alphabet = {'A', 'C', 'G', 'T', 'N'};

    // it helps to write a function that returns a index in the alphabet based
    // on the key, be mindful that this function needs to be fast
    int get_index(const Key &key) const {
        switch (key) {
            case 'A':
                return 0;
            case 'C':
                return 1;
            case 'G':
                return 2;
            case 'T':
                return 3;
            case 'N':
                return 4;
            default:
                return -1;
        }
    }

    // copys an existing tree pointed to by n
    const Node *deep_copy_tree(const Node *n) const {
        if (n) {
            auto node = new Node(n->key, n->val, n->size, n->is_end, n->children);
            // how would you handle the paths?
            while (n->children.size() > 0) {
                node->children[n->children.begin()->first] = deep_copy_tree(n->children.begin()->second);
            }
            return (node);
        }
        return (nullptr);
    }

    // frees the tree pointed to by n
    void free_tree(const Node *n) const {
        if (n) {
            // how would you handle the children?
            for (auto &child : n->children) {
                free_tree(child.second);
            }
            delete n;
        }
        return;
    }

   public:
    // default constructor
    template <std::size_t N>  // single functions can have a size template
    Trie(const std::array<Key, N> &a) {
        root = new Node('\0', 0, 1, false, std::map<Key, Node *>());
        add(a, 1);
    }

    // copy constructor
    Trie(const Trie &t) {}

    // move constructor
    Trie(Trie &&t) : root(t.root) { t.root = nullptr; }

    // copy assignment
    Trie &operator=(const Trie &t) {
        // free the existing trie
        free_tree(root);
        // copy the tree
        root = deep_copy_tree(t.root);
        return (*this);
    }

    // move assignment
    Trie &operator=(Trie &&t) {
        // free the existing tree
        free_tree(root);
        root = t.root;
        t.root = nullptr;
        return (*this);
    }

    // destructor
    ~Trie() { free_tree(root); }

    // TODO check update of size
    // put a key-value pair into the table
    template <std::size_t N>
    void add(const std::array<Key, N> &k, const Value a) {
        Node *node = root;
        for (int i = 0; i < N; i++) {
            char current_key = k[i];

            // detect invalid keys
            if (get_index(current_key) == -1) {
                throw std::invalid_argument("Invalid key");
            }

            // node is not in trie yet
            if (node->children.find(current_key) == node->children.end()) {
                node->children[current_key] = new Node(current_key, 0, 1, false, std::map<Key, Node *>());
            }

            // if sequence is over, mark node as end
            if (i == N - 1) {
                node->children[current_key]->is_end = true;
            // otherwise, continue to descend into trie
            } else {
                node = node->children[current_key];
            }
        }

        return;
    }

    // check if character sequence is present in trie
    template <std::size_t N>
    bool contains(const std::array<Key, N> &k) {
        Node *node = root;
        for (int i = 0; i < N; i++) {
            char current_key = k[i];

            // node was not found
            if (node->children.find(current_key) == node->children.end()) {
                return false;
            // node was found, continue the search
            } else {
                node = node->children[current_key];
            }
        }

        return true;
    }

    // check if character sequence is present in trie AND end of a sequence
    template <std::size_t N>
    bool observed(const std::array<Key, N> &k) {
        Node *node = root;
        for (int i = 0; i < N; i++) {
            char current_key = k[i];

            // node was not found
            if (node->children.find(current_key) == node->children.end()) {
                return false;
            // node was found, continue the search
            } else {
                node = node->children[current_key];
            }
        }

        // check if node is end of a sequence
        return node->is_end;
    }

    // we could also implement a function that returns the value of a key
    // this is not needed for the trie CLI, but it would be useful in practice
    // feel free to implement it if you want to - it is not required
};

#endif
