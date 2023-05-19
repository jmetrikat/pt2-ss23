#include "Set.h"

template <typename T>
Set<T> intersection(Set<T> &a, Set<T> &b) {
    Set<T> result = Set<T>();

    for (int i = 0; i < a.size(); i++) {
        if (b.contains(a[i])) {
            result.add(a[i]);
        }
    }

    return result;
}

template <typename T>
Set<T> union_(Set<T> &a, Set<T> &b) {
    Set<T> result = Set<T>(a);

    for (int i = 0; i < b.size(); i++) {
        result.add(b[i]);
    }

    return result;
}

template <typename T>
Set<T> difference(Set<T> &a, Set<T> &b) {
    Set<T> result = Set<T>(a);

    for (int i = 0; i < b.size(); i++) {
        result.remove(b[i]);
    }

    return result;
}
