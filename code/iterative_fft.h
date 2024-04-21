#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "math.h"



//Source Introduction to Algorithms P. 917

// algorithm iterative-fft is
//     input: Array a of n complex values where n is a power of 2.
//     output: Array A the DFT of a.
 
//     bit-reverse-copy(a, A)
//     n ← a.length 
//     for s = 1 to log(n) do
//         m ← 2s
//         ωm ← exp(−2πi/m) 
//         for k = 0 to n-1 by m do
//             ω ← 1
//             for j = 0 to m/2 – 1 do
//                 t ← ω A[k + j + m/2]
//                 u ← A[k + j]
//                 A[k + j] ← u + t
//                 A[k + j + m/2] ← u – t
//                 ω ← ω ωm
   
//     return A

unsigned int bitReverse(unsigned int x, int log2n);

void Iterative_FFT(complex double* input, int n, complex double* output);

void Iterative_IFFT(complex double* input, int n, complex double* output);

long polynomial_multiply_iterative_FFT(complex double* a, complex double* b, int n);