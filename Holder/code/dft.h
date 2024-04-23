// dft.h
#ifndef DFT_H
#define DFT_H
#include "Helper_Functions.h"

// Declare the function(s) from dft.c here
void DFT(complex double *in, int n, complex double *out);

void IDFT(complex double *in, int n, complex double *out);

long long polynomial_multiply_DFT(long a, long b, int n);

#endif
