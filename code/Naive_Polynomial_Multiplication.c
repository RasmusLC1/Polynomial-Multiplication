#include "Naive_Polynomial_Multiplication.h"


void Naive_Polynomial_Multiplication(int *input1, int *input2, int n, int *out){
    for (int i = 0; i < n; i++) { // For each element of input1
        for (int j = 0; j < n; j++) { // For each element of input2
            out[i + j] += input1[i] * input2[j];
        }
    }
}

void Polynomial_Multiply_Naive(mpz_t a, mpz_t b, int n, mpz_t* total_result){
    
    // Check for negative numbers
    bool negative = negative_check(a, b);

    
    int padded_a[n], padded_b[n], polynomial_result[n];

    memset(padded_a, 0, n * sizeof(int));
    memset(padded_b, 0, n * sizeof(int));
    memset(polynomial_result, 0, n * sizeof(int));

    mpz_to_int_array(a, padded_a); // Assume correct implementation
    mpz_to_int_array(b, padded_b);


    Naive_Polynomial_Multiplication(padded_a, padded_b, n, polynomial_result);
    // Convert to the real number
    int_array_to_mpz(polynomial_result, n, total_result);

    // Add correct sign back
    if (negative){
        mpz_t negative_value;
        mpz_init(negative_value);
        mpz_set_str(negative_value, "-1", 10);
        mpz_mul(total_result[0],
                total_result[0], negative_value);
        mpz_clear(negative_value);
    }

    return;
}