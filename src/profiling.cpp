#include "profiling.h"

const std::vector<std::string> available_dtypes = {"int", "float", "double"};
const std::vector<std::string> available_algos = {"insertion", "heap"};

void orchestrate(const std::vector<std::string>& dtypes,
                 const std::vector<std::string>& algos,
                 const std::vector<size_t>& sizes,
                 int iters,
                 std::filesystem::path output_csv_path,
                 ProfileMap& MAP) 
{
    std::ofstream output_file(output_csv_path);
    output_file << "Algorithm,Data Type,N Iters,Array Size,Swaps Mean,Swaps Var,Comps Mean,Comps Var,Time Mean,Time Var\n";

    for (const auto& str_dtype : dtypes) {
        for (const auto& str_algo : algos) {
            std::string full_str = str_algo + "_" + str_dtype;

            if (MAP.find(full_str) == MAP.end()) {
                std::cerr << "Algorithm " << full_str << " not found in map!\n";
                continue;
            }

            for (size_t size : sizes) {
                ProfileRes res = MAP[full_str](size, iters);
                BenchRes benchmark{res.swaps, res.comps, res.deltas, str_algo, iters, size, str_dtype};
                
                std::string final_line = benchmark.name_of_algo + "," +
                                         benchmark.data_type + "," +
                                         std::to_string(benchmark.n_iters) + "," +
                                         std::to_string(benchmark.array_size) + "," +
                                         std::to_string(benchmark.swaps.mean) + "," +
                                         std::to_string(benchmark.swaps.var) + "," +
                                         std::to_string(benchmark.comps.mean) + "," +
                                         std::to_string(benchmark.comps.var) + "," +
                                         std::to_string(benchmark.time.mean) + "," +
                                         std::to_string(benchmark.time.var);
                
                // std::cout << final_line << std::endl; // optional: output to cout as diagram showed final_line output
                std::cout << final_line << std::endl;
                output_file << final_line << "\n";
            }
        }
    }
}
