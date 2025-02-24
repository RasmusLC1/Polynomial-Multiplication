# Polynomial Multiplication in C

## Overview

This project implements various polynomial multiplication algorithms in C, including naive multiplication, Karatsuba’s algorithm, and Fast Fourier Transform (FFT) methods. It is designed to evaluate and compare the efficiency of these algorithms in terms of computational performance.

## Features

Naive Polynomial Multiplication: A straightforward approach with O(n²) complexity.

Karatsuba’s Algorithm: A divide-and-conquer technique that reduces complexity to O(n^{1.59}).

Discrete Fourier Transform (DFT): Transforms polynomial coefficients for multiplication in the frequency domain.

Recursive Fast Fourier Transform (FFT): Optimized polynomial multiplication using recursive FFT with O(n log n) complexity.

Iterative FFT: An optimized non-recursive version of FFT for better efficiency.

Performance Analysis: Runtime testing and correctness verification using unit tests.

## Installation

Prerequisites

Ensure you have the following installed:

GCC (GNU Compiler Collection)

MPFR and GMP Libraries (for arbitrary precision arithmetic)

Check Library (for unit testing)

## Compilation

To compile the program, run:

make

To clean up compiled files:

make clean

Usage

After compiling, run the program with:

./program

This executes the polynomial multiplication algorithms and displays the results along with performance metrics.

## File Structure
### A typical top-level directory layout

.
├── src                     # Source files
│   ├── Naive_Polynomial_Multiplication.c
│   ├── karatsuba.c
│   ├── Recursive_fft.c
│   ├── iterative_fft.c
│   ├── dft.c
│   ├── Helper_Functions.c
├── test                    # Test files
│   ├── WhiteBox_test.c
│   ├── Runtime_test.c
│   ├── Runtime_test_systematic.c
│   ├── karatsuba_optimisation.c
├── Makefile                # Makefile for building the project
├── README.md               # Project documentation

## Testing

The project includes unit tests to verify correctness:

make test

Key Insights from the Thesis

Algorithmic Trade-offs: While Karatsuba improves over the naive method, FFT-based methods offer the best performance for large polynomials.

Recursive vs. Iterative FFT: The iterative approach avoids recursion overhead and improves efficiency.

Optimization Challenges: Efficient memory allocation and cache usage significantly impact runtime performance.

Author

Developed by Rasmus Ladefoged as part of a Bachelor’s thesis at the University of Copenhagen.

License

MIT License. See LICENSE file for details.

References

For a detailed theoretical background, refer to the thesis: Polynomial Multiplication - Rasmus Ladefoged, University of Copenhagen (2024).

