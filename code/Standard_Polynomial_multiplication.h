// dft.h
#ifndef STANDARD_H
#define STANDARD_H
#include "Helper_Functions.h"

// Declare the function(s) from dft.c here
void Standard_Polynomial_Multiplication(int *input1, int *input2, int n, int *out);

void Polynomial_Multiply_Standard(mpz_t a, mpz_t b, int n, mpz_t* total_result);

#endif
