#ifndef Helper_Function_H
#define Helper_Function_H
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <gmp.h>
#include "math.h"

#define TAU 6.283185307179586


int mpz_to_complex_array(mpz_t input_int, complex double *output_array);

void complex_array_to_mpz(complex double *polynomial_result, int n, mpz_t* total_result);

int mpz_to_int_array(mpz_t input_int, int *output_array);

void int_array_to_mpz(int *polynomial_result, int n, mpz_t* total_result);

// // Initialize a and b with inverse number, I.E 27 = a[0] = 7 and a[1] = 2
    // // Coefficient of x^0 = a[0] and x^1=a[1]
    // a[0] = 7; a[1] = 2; // Polynomial for 27
void Int_to_Array(long long input_int, complex double *output_array);

bool negative_check(mpz_t a, mpz_t b);

// Loading screen to help visualise progress
void Loading_Screen(int iteration, int current_Iteration);

// Check if two values are the same
bool Correctness_Check(mpz_t result1, mpz_t result2);

// Utility function for reversing the bits
// of given index x
unsigned int Bit_Reverse(unsigned int x, int log2n);

// calculate the half length of a value
int get_half_length(mpz_t num);

void Array_Addition(int *a, int *b, int length, int *result);

void Array_Subtraction(int *a, int *b, int length, int *result);

void Array_Multiplication(int *input1, int *input2, int length_input1, int length_input2, int *result);

#endif