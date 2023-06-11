#include "sorting.h"

void SortingAlgorithm::swap(int i, int j) {
    int x = data[i];
    data[i] = data[j];
    data[j] = x;
}

void BubbleSort::sort() {
    bool swapped;

    // iterate through the array
    for (int i = 0; i < size - 1; i++) {
        swapped = false;

        // move element up the array if it is greater than the next element
        for (int j = 0; j < size - i - 1; j++) {
            if (comp.compare(data, j, j + 1) > 0) {
                swap(j, j + 1);
                swapped = true;
            }
        }

        // exit early if no swaps were made
        if (!swapped) {
            break;
        }
    }
}

void MergeSort::split(int lo, int hi) {
    // exit if the array is empty or has only one element
    if (lo >= hi) {
        return;
    }

    // split the array in half
    int mid = (lo + hi) / 2;
    split(lo, mid);
    split(mid + 1, hi);

    // merge the two halves back together
    merge(lo, mid, hi);
}

void MergeSort::merge(int lo, int mid, int hi) {
    int* aux = new int[size];

    // exit early if the two halves are already sorted
    if (comp.compare(data, mid, mid + 1) < 0) {
        return;
    }

    // copy elements from the original array into the auxiliary array
    for (int i = lo; i <= hi; i++) {
        aux[i] = data[i];
    }

    int i = lo;
    int j = mid + 1;

    // merge elements from both halves into the original array
    for (int k = lo; k <= hi; k++) {
        if (i > mid) {
            data[k] = aux[j++];
        } else if (j > hi) {
            data[k] = aux[i++];
        } else if (comp.compare(aux, i, j) > 0) {
            data[k] = aux[j++];
        } else {
            data[k] = aux[i++];
        }
    }

    delete[] aux;
}

void MergeSort::sort() {
    split(0, size - 1);
}

int QuickSort::divide(int lo, int hi) {
    int i = lo + 1;
    int j = hi;

    // move elements less than the pivot to the left and elements greater than the pivot (lo) to the right
    while (true) {
        // move 1st cursor to the right until it reaches an element greater than the pivot
        while (i <= j && comp.compare(data, i, lo) <= 0) {
            i++;
        }

        // move 2nd cursor to the left until it reaches an element less than the pivot
        while (i <= j && comp.compare(data, j, lo) >= 0) {
            j--;
        }

        // exit if the pointers cross
        if (i >= j) {
            break;
        }

        swap(i, j);
    }

    // move the pivot to the middle and return its index
    swap(lo, j);
    return j;
}

void QuickSort::qs(int lo, int hi) {
    // exit if the array is empty or has only one element
    if (lo >= hi) {
        return;
    }

    // sort the two halves according to pivot and repeat process for each half
    int p = divide(lo, hi);
    qs(lo, p - 1);
    qs(p + 1, hi);
}

void QuickSort::sort() {
    qs(0, size - 1);
}
