#include "Helper_Functions.h"



//Source Introduction to Algorithms P. 917

// RECURSIVE-FFT(a)
//     input: Array a of n complex values where n is a power of 2.
//     output: Array A the DFT of a.
    
//     n = a.length  # n is a power of 2
//     if n == 1:
//         return a
//     w_n = e^{2pi i/n}$
//     w = 1$
//     a[0] = (a0, a2, ..., an-2)
//     a[1] = (a1, a3, ..., an-1)
//     y[0] = RECURSIVE-FFT(a[0])
//     y[1] = RECURSIVE-FFT(a[1])
//     for k = 0 to n/2 - 1:
//         y[k] = y[0][k] + w * y[1][k]
//         y[k+n/2] = y[0][k] - w * y[1][k]
//         w = w * w_n$
//     return y # y is assumed to be a column vector


void Iterative_FFT(complex double* input, int n, complex double* output);

void Iterative_IFFT(complex double* input, int n, complex double* output);

double polynomial_multiply_iterative_FFT(mpz_t a, mpz_t b, int n, mpz_t* iterative_fft_total_result);
