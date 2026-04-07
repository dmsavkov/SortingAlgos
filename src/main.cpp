#include <iostream>
#include <functional>
#include <vector>

#include "sorting.h"

// deep copy of a vector
void make_sorting(std::vector<int> array_copy, void (*sorting_algorithm)(std::vector<int>&))
{
    sorting_algorithm(array_copy);
    for (size_t i = 0; i < array_copy.size(); ++i)
    {
        std::cout << array_copy[i] << " ";
    }
}

int main()
{
    std::vector<int> array = {5, 1, 7, 9, 2, 5, 6};
    std::cout << "Insertion Sort: ";
    make_sorting(array, insertion_sort<int>);
    std::cout << "\nHeap Sort: ";
    make_sorting(array, heap_sort<int>);
    std::cout << std::endl;
    return 0;
}
