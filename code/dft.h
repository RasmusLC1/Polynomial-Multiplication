// dft.h
#ifndef DFT_H
#define DFT_H
#include "Helper_Functions.h"

// Declare the function(s) from dft.c here
void DFT(complex double *in, int n, complex double *out);

void IDFT(complex double *in, int n, complex double *out);

long long polynomial_multiply_DFT(complex double *a, complex double *b, int n);

#endif
