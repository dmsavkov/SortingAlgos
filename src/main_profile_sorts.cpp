#include "profiling.h"
#include <iostream>
#include <vector>

int main() {
  std::cout << "Available dtypes: ";
  for (const auto &dt : available_dtypes) {
    std::cout << dt << " ";
  }
  std::cout << std::endl;

  std::cout << "Available algos: ";
  for (const auto &algo : available_algos) {
    std::cout << algo << " ";
  }
  std::cout << std::endl;

  std::filesystem::path output_path = "../build/profiling_results.csv";
  if (output_path.has_parent_path()) {
    std::filesystem::create_directories(output_path.parent_path());
  }

  ProfileMap MAP;
  REGISTER(MAP, "insertion", insertion_sort);
  REGISTER(MAP, "heap", heap_sort);

  std::vector<size_t> sizes = {10, 100, 5000, 50000};
  int iters = 20;

  orchestrate(available_dtypes, available_algos, sizes, iters, output_path,
              MAP);

  return 0;
}
