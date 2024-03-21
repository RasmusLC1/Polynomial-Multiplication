// dft.h
#ifndef DFT_H
#define DFT_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define PI 3.141592653589793238462
#define TAU 6.28318530717958647692 // 2 PI
#define EPSILON 1e-6 // Tolerance for comparison, increasing it further causes floating point errors


// Declare the function(s) from dft.c here
void DFT(complex double *in, int n, complex double *out);

void IDFT(complex double *in, int n, complex double *out);

long polynomial_multiply_DFT(complex double *a, complex double *b, int n);

#endif
