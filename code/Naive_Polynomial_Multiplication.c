#include "Naive_Polynomial_Multiplication.h"


void Naive_Polynomial_Multiplication(int *input1, int *input2, int n, int *out){
    for (int i = 0; i < n; i++) { // For each element of input1
        for (int j = 0; j < n; j++) { // For each element of input2
            out[i + j] += input1[i] * input2[j];
        }
    }
}

double Polynomial_Multiply_Naive(mpz_t a, mpz_t b, int n, int* total_result){ 
 
    int padded_a[n], padded_b[n], polynomial_result[n];

    memset(padded_a, 0, n * sizeof(int));
    memset(padded_b, 0, n * sizeof(int));
    memset(polynomial_result, 0, n * sizeof(int));

    mpz_to_int_array(a, padded_a); // Assume correct implementation
    mpz_to_int_array(b, padded_b);

    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    Naive_Polynomial_Multiplication(padded_a, padded_b, n, total_result);
    clock_gettime(CLOCK_MONOTONIC, &end);
    double elapsed_time = end.tv_sec - start.tv_sec + (end.tv_nsec - start.tv_nsec) / 1000000000.0;

    return elapsed_time;
}