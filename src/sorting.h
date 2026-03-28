#ifndef SORTING_H
#define SORTING_H

#include <iostream>

template <typename T>
void insertion_sort(T *array, size_t size) {
    for (size_t i = 1; i < size; ++i) {
        T key = array[i];
        for (int j = i; j >= 0; --j) {
            if (array[j - 1] <= key) {
                array[j] = key;
                break;
            } else {
                array[j] = array[j - 1];
            }
        }
    }
}

template <typename T>
void heapify(T *array, size_t size, size_t root) {
    size_t largest = root;
    size_t left = 2 * root + 1;
    size_t right = 2 * root + 2;

    if (left < size && array[left] > array[largest]) {
        largest = left;
    }

    if (right < size && array[right] > array[largest]) {
        largest = right;
    }

    if (largest != root) {
        std::swap(array[root], array[largest]);
        heapify(array, size, largest);
    }
}

template <typename T>
void heap_sort(T *array, size_t size) {
    // Build max heap
    for (int i = size / 2; i >= 0; --i) {
        heapify(array, size, (size_t)i);
    }

    // Sort
    for (int i = size - 1; i > 0; --i) {
        std::swap(array[0], array[i]);
        heapify(array, i, 0);
    }
}

#endif //#ifndef SORTING_H
