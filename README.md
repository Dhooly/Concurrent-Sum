## Concurrent‑Sum

A lightweight C++ demo showing how to split work across threads to compute the sum of a large array in parallel, complete with CPU‑core affinity and timing.

---

### Table of Contents

- [Features](#features)
- [Prerequisites](#prerequisites)
- [Building](#building)
- [Usage](#usage)
- [Example](#example)
- [Code Structure](#code-structure)
- [Performance Notes](#performance-notes)

---

## Features

- **Configurable thread count** via `--thread-count`  
- **CPU affinity**: binds each worker to a different core  
- **Array size**: fixed at 1 000 000 elements  
- **Per‑element workload**: includes an artificial `sqrt` loop to simulate compute load  
- **Timing**: reports wall‑clock duration  

---

## Prerequisites

- A modern C++ compiler with C++11 support (e.g. `g++` ≥ 4.8)  
- POSIX threads library (`pthread`)  
- Standard UNIX build tools: `make`, `bash`, etc.  

---

## Building

You can compile directly with `g++`:

```bash
git clone https://github.com/Dhooly/Concurrent-Sum.git
cd Concurrent-Sum

# Single‑step compile & link
 g++ -std=c++17 -pthread -O3 -I include/ src/* -o concurrent_sum
```
---

## Usage

`./concurrent_sum [--thread-count N]`
- With no flags, defaults to 1 thread.
- `--thread-count N`: use up to N concurrent workers (capped to the number of physical cores).

---

## Example

```bash
./concurrent_sum --thread-count 1
Calculating the sum of 1000000 numbers with 1 thread(s)...
Elapsed time: 7.47017 seconds with a result of 49498583

./concurrent_sum --thread-count 24
Calculating the sum of 1000000 numbers with 24 thread(s)...
Elapsed time: 0.375271 seconds with a result of 49497838
```

---

## Code Structure

```
.
├── include/
│   ├── sum_context.hpp         # Manages array allocation, init & result accumulation
│   ├── sum_main.hpp            # CLI parsing & usage declaration
│   ├── sum_pthread.hpp         # Wrapper around pthread_create, affinity & thread entry
│   └── sum_pthread_manager.hpp # Spawns, starts & joins all threads
└── src/
    ├── sum_context.cpp
    ├── sum_main.cpp
    ├── sum_pthread.cpp
    └── sum_pthread_manager.cpp
```
- **sum_context:** Allocates a 1 000 000‑int array, seeds it with rand()%100, and holds the global result.

- **sum_pthread:** Each worker computes a local partial sum over its slice and atomically adds to the global result under a mutex, with CPU affinity set.

- **sum_pthread_manager:** Orchestrates thread creation, start, and join logic.

- **sum_main:** Parses `--thread-count`, initializes everything, times the run, and prints the elapsed time and final sum.

---

## Performance Notes

- The inner std::sqrt loop (1 000 calls per element) simulates compute intensity, so you’ll see more dramatic speedups for higher thread counts on multi‑core machines.

- Array size is fixed via concurrent_sum::arrSize (1 000 000), but you can adjust it in sum_context.hpp to experiment.

- For best results, compile with -O2 or higher and run on a system with at least as many cores as your thread count.
