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
#include "math.h"

// // Initialize a and b with inverse number, I.E 27 = a[0] = 7 and a[1] = 2
    // // Coefficient of x^0 = a[0] and x^1=a[1]
    // a[0] = 7; a[1] = 2; // Polynomial for 27
void Int_to_Array(long long input_int, complex double *output_array);

// Loading screen to help visualise progress
void Loading_Screen(int iteration, int current_Iteration);

// Check if two values are the same
bool Correctness_Check(long long result1, long long result2);

// Utility function for reversing the bits
// of given index x
unsigned int Bit_Reverse(unsigned int x, int log2n);

// calculate the half length of a value
int get_half_length(long long value);

#endif