#include <gtest/gtest.h>

#include "sorting.h"
#include <vector>

TEST(SortingTest, InsertionSort)
{
    std::vector<int> arr = {5, 1, 7, 9, 2, 5, 6};
    insertion_sort(arr.data(), arr.size());
    EXPECT_EQ(arr, (std::vector<int> {1, 2, 5, 5, 6, 7, 9}));

    std::vector<int> arr2 = {};
    insertion_sort(arr2.data(), arr2.size());
    EXPECT_EQ(arr2, (std::vector<int> {}));

    std::vector<int> arr3 = {1};
    insertion_sort(arr3.data(), arr3.size());
    EXPECT_EQ(arr3, (std::vector<int> {1}));

    std::vector<int> arr4 = {9, 8, 7, 6, 5, 4, 3, 2, 1, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    insertion_sort(arr4.data(), arr4.size());
    EXPECT_EQ(arr4, (std::vector<int> {1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9}));

    std::vector<float> arr5 = {3.5, 2.1, 4.6, 1.0};
    insertion_sort(arr5.data(), arr5.size());
    EXPECT_EQ(arr5, (std::vector<float> {1.0, 2.1, 3.5, 4.6}));
}

TEST(SortingTest, HeapSort)
{
    std::vector<int> arr = {5, 1, 7, 9, 2, 5, 6};
    heap_sort(arr.data(), arr.size());
    EXPECT_EQ(arr, (std::vector<int> {1, 2, 5, 5, 6, 7, 9}));

    std::vector<int> arr2 = {};
    heap_sort(arr2.data(), arr2.size());
    EXPECT_EQ(arr2, (std::vector<int> {}));

    std::vector<int> arr3 = {1};
    heap_sort(arr3.data(), arr3.size());
    EXPECT_EQ(arr3, (std::vector<int> {1}));

    std::vector<int> arr4 = {9, 8, 7, 6, 5, 4, 3, 2, 1, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    heap_sort(arr4.data(), arr4.size());
    EXPECT_EQ(arr4, (std::vector<int> {1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9}));

    std::vector<float> arr5 = {3.5, 2.1, 4.6, 1.0};
    heap_sort(arr5.data(), arr5.size());
    EXPECT_EQ(arr5, (std::vector<float> {1.0, 2.1, 3.5, 4.6}));
}

