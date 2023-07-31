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
    return arr;
}

// Trie
template <typename Key, typename Value, size_t U>
class Trie {
    struct Node {
        Key key;
        Value val;
        int size;
        bool is_end;
        std::array<Node *, U> children{};

        // constructor with values
        Node(const Key &k, const Value &v, const int s)
            : key(k), val(v), size(s), is_end(false), children() {}
    };
    Node *root;  // root of the search forest

    // allowed alphabet
    std::map<Key, int> alphabet;

    // return index of key in alphabet
    int get_index(const Key &key) const {
        auto idx = alphabet.find(key);
        if (idx == alphabet.end()) {
            return -1;
        }
        return idx->second;
    }

    // copys an existing tree pointed to by n
    const Node *deep_copy_tree(const Node *n) const {
        if (n) {
            auto node =
                new Node(n->key, n->val, n->size, n->is_end, n->children);
            for (int i = 0; i < U; i++) {
                node->children[i] = deep_copy_tree(n->children[i]);
            }
            return node;
        }
        return nullptr;
    }

    // frees the tree pointed to by n
    void free_tree(const Node *n) const {
        if (n) {
            for (int i = 0; i < U; i++) {
                free_tree(n->children[i]);
            }
            delete n;
        }
        return;
    }

   public:
    // default constructor
    template <std::size_t N>  // single functions can have a size template
    Trie(const std::array<Key, N> &a) {
        root = new Node('\0', 0, 1);
        for (int i = 0; i < N; i++) {
            alphabet[a[i]] = i;
        }
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
        return *this;
    }

    // move assignment
    Trie &operator=(Trie &&t) {
        // free the existing tree
        free_tree(root);
        root = t.root;
        t.root = nullptr;
        return *this;
    }

    // destructor
    ~Trie() { free_tree(root); }

    // put a key-value pair into the table
    template <std::size_t N>
    void add(const std::array<Key, N> &k, const Value a) {
        Node *node = root;
        for (int i = 0; i < N; i++) {
            int idx = get_index(k[i]);

            // detect invalid keys
            if (idx == -1) {
                throw std::invalid_argument("Invalid key");
            }

            // node is not in trie yet
            if (node->children[idx] == nullptr) {
                // create new node
                node->children[idx] = new Node(k[i], 0, 1);
            }

            // if sequence is over, mark node as end
            if (i == N - 1) {
                node->children[idx]->is_end = true;
                // otherwise, continue to descend into trie
            } else {
                node = node->children[idx];
            }
        }

        return;
    }

    // check if character sequence is present in trie
    template <std::size_t N>
    bool contains(const std::array<Key, N> &k) {
        Node *node = root;
        for (int i = 0; i < N; i++) {
            int idx = get_index(k[i]);

            // node was not found
            if (idx == -1 || node->children[idx] == nullptr) {
                return false;
                // node was found, continue the search
            } else {
                node = node->children[idx];
            }
        }

        return true;
    }

    // check if character sequence is present in trie AND end of a sequence
    template <std::size_t N>
    bool observed(const std::array<Key, N> &k) {
        Node *node = root;
        for (int i = 0; i < N; i++) {
            int idx = get_index(k[i]);

            // node was not found
            if (idx == -1 || node->children[idx] == nullptr) {
                return false;
            // node was found, continue the search
            } else {
                node = node->children[idx];
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
