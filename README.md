# Sorting Algorithms Profiling Project

This project focuses on benchmarking and profiling the execution of mathematical sorting algorithms across different array sizes and numeric data types. The results are gathered automatically using rigorous `std::chrono` bindings and formatted into structured datasets.

## Empirical Conclusions

Based on the execution of the profiling suite (`make benchmark`), we can draw several concrete conclusions regarding the operational complexity of **Insertion Sort** versus **Heap Sort**:

### 1. Big-O Complexity Realisms (Space/Time Analysis)

At major array sizes (i.e. $N = 50,000$), the theoretical complexities perfectly trace the empirical data:

*   **Insertion Sort ($O(n^2)$)**:
    Required **~622,000,000+** swaps and comparisons, aligning closely with the average-case $n^2/4$ mathematical expectation. It required approximately **~0.27 seconds** to complete.
*   **Heap Sort ($O(n \log n)$)**:
    Downtrended drastically, executing only **~734,800** swaps and **~1,400,000** comparisons (aligning closely with theoretical $n \log_2 n$ expectations). This completed in a blistering **~0.005 seconds**.

**Conclusion:** Heap sort vastly outperforms insertion sort uniformly on large datasets, scaling roughly 50x to 60x faster at N=50,000.  

### 2. Small Array Characteristics

When operating on micro-datasets (i.e. $N = 10$), the overhead dynamic changes slightly. 
*   **Insertion Sort** averaged **23** swaps and **30** comparisons.
*   **Heap Sort** averaged **26** swaps and **39** comparisons.

**Conclusion:** For extremely small arrays, insertion sort proves to be slightly more computationally efficient. Because compiling the heap structure adds overhead relative to simple linear element bubbling, insertion sort natively wins micro-sort batches.

### 3. Data Type Overheads (Int vs Float vs Double)

Using polymorphic array generation, we tracked the penalty of standard integer vs. IEEE-754 floating point arithmetic scaling across 50,000 elements.

**Insertion Sort @ 50,000 Elements (Seconds):**
| Data Type | Time Mean |
|-----------|-----------|
| `int`     | 0.268s    |
| `double`  | 0.330s    |
| `float`   | 0.332s    |

**Heap Sort @ 50,000 Elements (Seconds):**
| Data Type | Time Mean |
|-----------|-----------|
| `int`     | 0.0050s   |
| `double`  | 0.0054s   |
| `float`   | 0.0054s   |

### 4. Timing Stability and Variance

Across all 20 iterations for each configuration, the **Time Variance** remained effectively negligible:

| Algorithm | Data Type | Array Size | Time Mean | Time Var |
|-----------|-----------|------------|-----------|----------|
| `heap`    | `double`  | 50,000     | 0.005432s | 0.000000 |
| `heap`    | `int`     | 50,000     | 0.005004s | 0.000000 |
| `insertion`| `int`    | 50,000     | 0.268238s | 0.000087 |

**Conclusion:** The extremely low variance (approaching zero in many cases) indicates high consistency in the execution environment and algorithmic performance. Even for the more compute-intensive `insertion` sort, the variance is orders of magnitude smaller than the mean, confirming that these benchmarks provide a reliable representation of real-world performance stability.
