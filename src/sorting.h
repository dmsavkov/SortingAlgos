#ifndef SORTING_H
#define SORTING_H

#include <iostream>
#include <utility>
#include <vector>

struct DynamicMetrics 
{
    size_t n_swaps = 0;
    size_t n_comparisons = 0;
};

template <typename T>
void insertion_sort(T *array, size_t size, DynamicMetrics &metrics)
{
    for (size_t i = 1; i < size; ++i)
    {
        T key = array[i];
        size_t j = i;
        while (j > 0)
        {
            metrics.n_comparisons++;
            if (array[j - 1] <= key)
            {
                break;
            }

            array[j] = array[j - 1];
            metrics.n_swaps++;
            --j;
        }

        array[j] = key;
    }
}

template <typename T>
void insertion_sort(std::vector<T>& array)
{
    DynamicMetrics dummy;
    insertion_sort(array.data(), array.size(), dummy);
}

template <typename T>
void heapify(T *array, size_t size, size_t root, DynamicMetrics &metrics)
{
    size_t largest = root;
    size_t left = 2 * root + 1;
    size_t right = 2 * root + 2;

    if (left < size)
    {
        metrics.n_comparisons++;
        if (array[left] > array[largest])
        {
            largest = left;
        }
    }

    if (right < size)
    {
        metrics.n_comparisons++;
        if (array[right] > array[largest])
        {
            largest = right;
        }
    }

    if (largest != root)
    {
        std::swap(array[root], array[largest]);
        metrics.n_swaps++;
        heapify(array, size, largest, metrics);
    }
}

template <typename T>
void heap_sort(T *array, size_t size, DynamicMetrics &metrics)
{
    // Build max heap
    for (size_t i = size / 2; i > 0; --i)
    {
        heapify(array, size, i - 1, metrics);
    }

    // Sort
    for (size_t i = size; i > 1; --i)
    {
        std::swap(array[0], array[i - 1]);
        metrics.n_swaps++;
        heapify(array, i - 1, 0, metrics);
    }
}

template <typename T>
void heap_sort(std::vector<T>& array)
{
    DynamicMetrics dummy;
    heap_sort(array.data(), array.size(), dummy);
}

#endif //#ifndef SORTING_H
