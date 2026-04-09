#ifndef PROFILING_H
#define PROFILING_H

#include "sorting.h"
#include <chrono>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

struct Value
{
    double mean;
    double var;
};

struct ProfileRes
{
    Value swaps;
    Value comps;
    Value deltas;
};

struct BenchRes
{
    Value swaps;
    Value comps;
    Value time;
    std::string name_of_algo;
    int n_iters;
    size_t array_size;
    std::string data_type;
};

// extern to avoid bloated executable
extern const std::vector<std::string> available_dtypes;
extern const std::vector<std::string> available_algos;

using SortProfileFn = std::function<ProfileRes(
                          size_t, int)>; // similar to typing.Annotated[] in python
using ProfileMap = std::map<std::string, SortProfileFn>;

template <typename T> std::vector<T> generate_array(size_t size)
{
    std::vector<T> array(size);
    // 2. Setting up generator (Mersenne Twister)
    std::random_device rd;  // Entropy source
    std::mt19937 gen(rd()); // Generator

    if constexpr (std::is_integral_v<T>)
    {
        std::uniform_int_distribution<T> dist(-100, 100);
        for (size_t i = 0; i < size; ++i)
        {
            array[i] = dist(gen);
        }
    }
    else if constexpr (std::is_floating_point_v<T>)
    {
        std::uniform_real_distribution<T> dist(-100.0, 100.0);
        for (size_t i = 0; i < size; ++i)
        {
            array[i] = dist(gen);
        }
    }
    else
    {
        throw std::invalid_argument("Unsupported type for generation");
    }

    return array;
}

template <typename T> Value calc_value(const std::vector<T> &results)
{
    if (results.empty())
        return {0.0, 0.0};
    double sum = 0;
    for (const auto &val : results)
    {
        sum += static_cast<double>(val);
    }
    double mean = sum / results.size();

    double var = 0;
    for (const auto &val : results)
    {
        double diff = static_cast<double>(val) - mean;
        var += diff * diff;
    }
    var /= results.size();

    return {mean, var};
}

template <typename T, typename Callable>
ProfileRes profile(Callable sort_fn, size_t array_size, int n_iterations)
{
    std::vector<size_t> swaps(n_iterations);
    std::vector<size_t> comps(n_iterations);
    std::vector<double> deltas(n_iterations);

    for (int i = 0; i < n_iterations; ++i)
    {
        std::vector<T> array = generate_array<T>(array_size);
        DynamicMetrics cur_metrics;

        auto start = std::chrono::high_resolution_clock::now();
        sort_fn(array.data(), array.size(), cur_metrics);
        auto now = std::chrono::high_resolution_clock::now();

        std::chrono::duration<double> delta = now - start;

        swaps[i] = cur_metrics.n_swaps;
        comps[i] = cur_metrics.n_comparisons;
        deltas[i] = delta.count();
    }

    return ProfileRes{calc_value(swaps), calc_value(comps), calc_value(deltas)};
}

#define REGISTER(MAP, NAME, FN)                                                \
  MAP[std::string(NAME) + "_int"] = [](size_t size, int iters) -> ProfileRes { \
    auto wrapper = [](int *arr, size_t s, DynamicMetrics &m) {                 \
      FN<int>(arr, s, m);                                                      \
    };                                                                         \
    return profile<int>(wrapper, size, iters);                                 \
  };                                                                           \
  MAP[std::string(NAME) + "_float"] = [](size_t size,                          \
                                         int iters) -> ProfileRes {            \
    auto wrapper = [](float *arr, size_t s, DynamicMetrics &m) {               \
      FN<float>(arr, s, m);                                                    \
    };                                                                         \
    return profile<float>(wrapper, size, iters);                               \
  };                                                                           \
  MAP[std::string(NAME) + "_double"] = [](size_t size,                         \
                                          int iters) -> ProfileRes {           \
    auto wrapper = [](double *arr, size_t s, DynamicMetrics &m) {              \
      FN<double>(arr, s, m);                                                   \
    };                                                                         \
    return profile<double>(wrapper, size, iters);                              \
  };

void orchestrate(const std::vector<std::string> &dtypes,
                 const std::vector<std::string> &algos,
                 const std::vector<size_t> &sizes, int iters,
                 std::filesystem::path output_csv_path, ProfileMap &MAP);

#endif // PROFILING_H
