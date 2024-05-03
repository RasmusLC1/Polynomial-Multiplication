#include "Standard_Polynomial_multiplication.h"


void Standard_Polynomial_Multiplication(int *input1, int *input2, int n, int *out){
    for (int i = 0; i < n; i++) { // For each element of input1
        for (int j = 0; j < n; j++) { // For each element of input2
            out[i + j] += input1[i] * input2[j];
        }
    }
}

void Polynomial_Multiply_Standard(mpz_t a, mpz_t b, int n, mpz_t* total_result){
    
    // Check for negative numbers
    bool negative = false;
    mpz_t negative_value;
    // Negative check
    if (mpz_sgn(a) < 0 && mpz_sgn(b) >= 0){
        negative = true;
        mpz_init(negative_value);
        mpz_set_str(negative_value, "-1", 10);
        mpz_mul(a, a, negative_value);
    } else if (mpz_sgn(b) < 0 && mpz_sgn(a) >= 0){
        negative = true;
        mpz_init(negative_value);
        mpz_set_str(negative_value, "-1", 10);
        mpz_mul(b, b, negative_value);
    }
    
    int padded_a[n], padded_b[n], polynomial_result[n];

    memset(padded_a, 0, n * sizeof(int));
    memset(padded_b, 0, n * sizeof(int));
    memset(polynomial_result, 0, n * sizeof(int));

    int length_input1 = mpz_to_int_array(a, padded_a); // Assume correct implementation
    int length_input2 = mpz_to_int_array(b, padded_b);


    Standard_Polynomial_Multiplication(padded_a, padded_b, n, polynomial_result);
    // //Convert to the real number
    mpz_t temp, result, power;

    // The below for loop is calculating the following line using GMP
    // FFT_total_result += (long long)(creal(result[i])+0.5)*pow(10,i);
    for (int i = 0; i < n; i++) {
        mpz_inits(temp, result, power, NULL);
        // Calculate 10^i using GMP
        mpz_ui_pow_ui(power, 10, i);

        // Convert creal(result[i]) to nearest integer and multiply by 10^i
        mpz_set_d(temp, floor(creal(polynomial_result[i]) + 0.5));
        mpz_mul(result, temp, power);

        // Add to the total result
        mpz_add(total_result[0], total_result[0], result);
        // Cleanup
        mpz_clears(temp, result, power, NULL);
    }

    // Add correct sign back
    if (negative){
        mpz_mul(total_result[0], total_result[0], negative_value);
        mpz_clear(negative_value);
    }

    return;
}