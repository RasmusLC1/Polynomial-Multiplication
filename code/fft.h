#ifndef FFT_H
#define FFT_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define PI 3.141592653589793238462
#define TAU 2 * PI // 2 PI
#define EPSILON 1e-6 // Tolerance for comparison, increasing it further causes floating point errors

// Base case
//1  if n = 1 then
//2      return f (1)
// Collect the even (even_values) degree terms and odd (odd_values) degree terms of f to write it as
//3  f = even_values(x2) + x odd_values(x2).
// // Observe that ω2 is a principal (n~2)-th root of of unity.
//4 Recursively compute FFT( even_values, ω2) and FFT( odd_values, ω2).
//5  for i = 0, ⋯, n − 1 do
//6      k = 2i mod n~2
//7      // This is to ensure that 0 ≤ k < n~2, and also note that k will be even_values.
//8      Let β = even_values(ωk) and γ = odd_values(ωk), which were computed earlier.
//9      Store the value f (ωi) = β + γωi.
//10      return  f (1), . . . , f (ωn−1).

void FFT_ext(complex double *f, int n, complex double *out, complex double *allocated_memory, int allocated_memory_size);

void IFFT_ext(complex double *f, int n, complex double *out, complex double *allocated_memory, int allocated_memory_size);

void FFT(complex double *f, int n, complex double *out);

void IFFT(complex double *f, int n, complex double *out);

long polynomial_multiply_FFT(complex double* a, complex double* b, int n);


#endif