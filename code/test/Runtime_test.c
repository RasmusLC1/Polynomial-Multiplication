#include "Runtime_test.h"

void Runtime_test(int n, int iterations) {
    // Set up correctness meassure
    int fail = 0, success = 0;

    mpz_t random_Value_a, random_Value_b;
    mpz_inits(random_Value_a, random_Value_b, NULL);

    // Seed the random state with current time
    gmp_randstate_t state;
    gmp_randinit_default(state);
    gmp_randseed_ui(state, time(NULL));

    // Set up timers
    double time_default = 0.0, time_standard = 0.0, time_dft = 0.0, time_fft = 0.0,
            time_iterative_fft = 0.0, time_karatsuba = 0.0;
    struct timespec start, end;
    double elapsed_time;

    // Loop through the test multiple times to allow bigger tests
    // Also allows us to test n size vs iterations and their effect
    mpz_t result_standard, result_recursive_fft, result_iterative_fft, result_dft, result_karatsuba;
    
    for (int i = 1; i <= iterations; i++) {


        mpz_inits(result_standard, result_recursive_fft, result_iterative_fft, result_dft, result_karatsuba, NULL);

        // Generate a random number with n bits
        mpz_urandomb(random_Value_a, state, n);
        mpz_urandomb(random_Value_b, state, n);

        // Standard TEST
        time_standard += Polynomial_Multiply_Naive(random_Value_a, random_Value_b, n, &result_standard);

        // DFT TEST
        // time_dft += polynomial_multiply_DFT(random_Value_a, random_Value_b, n, &result_dft);

        // Recursive FFT test
        time_fft += polynomial_multiply_Recursive_FFT(random_Value_a, random_Value_b, n, &result_recursive_fft);

        // Iterative FFT test
        time_iterative_fft += polynomial_multiply_iterative_FFT(random_Value_a, random_Value_b, n, &result_iterative_fft);

        // Karatsuba test
        time_karatsuba += polynomial_multiply_karatsuba(random_Value_a, random_Value_b, n, &result_karatsuba);

        
        if (Correctness_Check(result_standard, result_standard) &&
            Correctness_Check(result_standard, result_iterative_fft) &&
            Correctness_Check(result_standard, result_recursive_fft) &&
            Correctness_Check(result_standard, result_karatsuba)){
                success++;
        }else{
            fail ++;
        }
        // Clear the space allocated for the number and the random state
        mpz_clears(result_standard, result_recursive_fft, result_iterative_fft, result_dft, result_karatsuba, NULL);
        Loading_Screen(iterations, i);
        

    }
    mpz_clears(random_Value_a, random_Value_b, NULL);

    printf("\nn size: %d\t iterations: %d\n", n, iterations);
    printf("Successful calculations:\t%d\nWrong calculations:\t%d\n", success, fail);
    printf("standard polynomial multiplication time:\t%f seconds.\n", time_standard);
    printf("DFT polynomial multiplication time:\t\t%f seconds.\n", time_dft);
    printf("Karatsuba polynomial multiplication time:\t%f seconds.\n", time_karatsuba);
    printf("Recursive_FFT polynomial multiplication time:\t%f seconds.\n", time_fft);
    printf("Iterative_FFT polynomial multiplication time:\t%f seconds.\n", time_iterative_fft);
    
    gmp_randclear(state);

}