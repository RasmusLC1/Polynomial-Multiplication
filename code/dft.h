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
#include "math.h"

// Declare the function(s) from dft.c here
void DFT(complex double *in, int n, complex double *out);

void IDFT(complex double *in, int n, complex double *out);

long polynomial_multiply_DFT(complex double *a, complex double *b, int n);

#endif
