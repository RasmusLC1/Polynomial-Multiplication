#ifndef FFT_H
#define FFT_H
#include "Helper_Functions.h"


// X0,...,N−1 ← ditfft2(x, N, s):             DFT of (x0, xs, x2s, ..., x(N-1)s):
//     if N = 1 then
//         X0 ← x0                                      trivial size-1 DFT base case
//     else
//         X0,...,N/2−1 ← ditfft2(x, N/2, 2s)             DFT of (x0, x2s, x4s, ..., x(N-2)s)
//         XN/2,...,N−1 ← ditfft2(x+s, N/2, 2s)           DFT of (xs, xs+2s, xs+4s, ..., x(N-1)s)
//         for k = 0 to N/2−1 do                        combine DFTs of two halves into full DFT:
//             p ← Xk
//             q ← exp(−2πi/N k) Xk+N/2
//             Xk ← p + q 
//             Xk+N/2 ← p − q
//         end for
//     end if

void Recursive_FFT_ext(complex double *input, int n, complex double *out, complex double *allocated_memory, int allocated_memory_size);

void Recursive_IFFT_ext(complex double *input, int n, complex double *out, complex double *allocated_memory, int allocated_memory_size);

void Recursive_FFT(complex double *input, int n, complex double *out);

void Recursive_IFFT(complex double *input, int n, complex double *out);

void polynomial_multiply_Recursive_FFT(mpz_t a, mpz_t b, int n, mpz_t* dft_total_result);


#endif