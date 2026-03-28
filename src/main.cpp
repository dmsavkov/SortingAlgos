#include <iostream>
#include <functional>
#include <vector>

#include "sorting.h"

void make_sorting(int *array, size_t size, std::function<void(int *, size_t)> sorting_algorithm)
{
    std::vector<int> array_copy(array, array + size);

    sorting_algorithm(array_copy.data(), size);
    for (size_t i = 0; i < size; ++i)
    {
        std::cout << array_copy[i] << " ";
    }
}

int main()
{
    std::vector<int> array = {5, 1, 7, 9, 2, 5, 6};
    size_t size = array.size();
    std::cout << "Insertion Sort: ";
    make_sorting(array.data(), size, insertion_sort<int>);
    std::cout << "\nHeap Sort: ";
    make_sorting(array.data(), size, heap_sort<int>);
    std::cout << std::endl;
    return 0;
}
