#include "generator.h"

#include <iostream>

void swap(int* data, int i, int j) {
    int x = data[i];
    data[i] = data[j];
    data[j] = x;
}

// already sorted
int* generateSorted(int n) {
    int* data = new int[n];

    for (int i = 0; i < n; i++) {
        data[i] = i;
    }

    return data;
}

// use for worst-case of mergesort
void merge(int* data, int* left, int* right, int size, int m) {
    for (int i = 0; i < size; i++) {
        if (i < m) {
            data[i] = left[i];
        } else {
            data[i] = right[i - m];
        }
    }
}

// use for worst-case of mergesort
void separate(int* data, int size) {
    int m = size / 2;
    int* left = new int[m];
    int* right = new int[size - m];

    for (int i = 0; i < size; i++) {
        if (i % 2 != 0) {
            left[i / 2] = data[i];
        } else {
            right[i / 2] = data[i];
        }
    }

    if (size > 2) {
        separate(left, m);
        separate(right, size - m);
    }

    swap(data, 0, size - 1);
    merge(data, left, right, size, m);
}

// reverse sorted
int* generateWorstCaseBubblesort(int n) {
    int* data = new int[n];

    for (int i = 0; i < n; i++) {
        data[i] = n - i;
    }

    if (n == 10) {
        std::cout << std::endl << "Worst-Case Bubble Sort - Reverse Sorted: ";
        for (int i = 0; i < n; i++) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }

    return data;
}

// reverse merge logic
int* generateWorstCaseMergesort(int n) {
    int* data = generateSorted(n);
    separate(data, n);
    if (n == 10) {
        std::cout << std::endl << "Worst-Case Merge Sort - Reversed Logic: ";
        for (int i = 0; i < n; i++) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }
    return data;
}

// pivot is always the smallest element, for this case the array is already sorted
int* generateWorstCaseQuicksort(int n) {
    int* data = generateSorted(n);

    if (n == 10) {
        std::cout << std::endl << "Worst-Case Quick Sort - Pivot is smallest element: ";
        for (int i = 0; i < n; i++) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }
    return data;
}

// already sorted
int* generateBestCaseBubblesort(int n) {
    int* data = generateSorted(n);
    if (n == 10) {
        std::cout << std::endl << "Best-Case Bubble Sort - Already Sorted: ";
        for (int i = 0; i < n; i++) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }
    return data;
}

// already sorted
int* generateBestCaseMergesort(int n) {
    int* data = generateSorted(n);
    if (n == 10) {
        std::cout << std::endl << "Best-Case Merge Sort - Already Sorted: ";
        for (int i = 0; i < n; i++) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }
    return data;
}

// use for best case of quicksort
void rearrange(int* data, int lo, int hi, bool pivot_to_left) {
    if (hi - lo < 2) {
        return;
    }

    // choose the middle element as the pivot and swap it to the first position for left partition and last position for right partition
    int mid = (lo + hi) / 2;

    // swap(data, lo, mid);
    if (pivot_to_left) {
        for (int i = mid; i > lo; i--) {
            swap(data, i, i - 1);
        }
    } else {
        for (int i = mid; i < hi; i++) {
            swap(data, i, i + 1);
        }
    }

    rearrange(data, lo + 1, mid, false);
    rearrange(data, mid + 1, hi, true);
}

// pivot is always the middle element
int* generateBestCaseQuicksort(int n) {
    int* data = generateSorted(n);
    rearrange(data, 0, n - 1, true);

    if (n == 10) {
        std::cout << std::endl << "Best-Case Quick Sort - Pivot is middle element: ";
        for (int i = 0; i < n; i++) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }
    return data;
}
