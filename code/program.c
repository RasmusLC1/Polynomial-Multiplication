#include "Recursive_fft.h"
#include "iterative_fft.h"
#include "dft.h"
#include "karatsuba.h"
#include "test/WhiteBox_test.h"
#include "Helper_Functions.h"

void Polynomial_Multiply() {
    int n = 516 ; // test size needs to be power 2
    int iterations = 10;
    // Set up correctness meassure
    int fail = 0, success = 0;

    mpz_t random_Value_a, random_Value_b;
    mpz_inits(random_Value_a, random_Value_b, NULL);

    // Seed the random state with current time
    gmp_randstate_t state;
    gmp_randinit_default(state);
    gmp_randseed_ui(state, time(NULL));

    // Set up timers
    double time_default = 0.0, time_dft = 0.0, time_fft = 0.0,
            time_iterative_fft = 0.0, time_karatsuba = 0.0, time_standard = 0.0;
    struct timespec start, end;
    double elapsed_time;

    // Loop through the test multiple times to allow bigger tests
    // Also allows us to test n size vs iterations and their effect
    mpz_t result_recursive_fft, result_iterative_fft, result_dft, result_karatsuba;
    
    for (int i = 1; i <= iterations; i++) {


        mpz_inits(result_recursive_fft, result_iterative_fft, result_dft, result_karatsuba, NULL);

        // Generate a random number with n bits
        mpz_urandomb(random_Value_a, state, n);
        mpz_urandomb(random_Value_b, state, n);

        // DFT TEST
        clock_gettime(CLOCK_MONOTONIC, &start);
        polynomial_multiply_DFT(random_Value_a, random_Value_b, n, &result_dft);
        clock_gettime(CLOCK_MONOTONIC, &end);
        elapsed_time = end.tv_sec - start.tv_sec + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
        time_dft += elapsed_time - time_default;
        
        // Recursive FFT test
        clock_gettime(CLOCK_MONOTONIC, &start);
        polynomial_multiply_Recursive_FFT(random_Value_a, random_Value_b, n, &result_recursive_fft);
        clock_gettime(CLOCK_MONOTONIC, &end);
        elapsed_time = end.tv_sec - start.tv_sec + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
        time_fft += elapsed_time - time_default;

        // Iterative FFT test
        clock_gettime(CLOCK_MONOTONIC, &start);
        polynomial_multiply_iterative_FFT(random_Value_a, random_Value_b, n, &result_iterative_fft);
        clock_gettime(CLOCK_MONOTONIC, &end);
        elapsed_time = end.tv_sec - start.tv_sec + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
        time_iterative_fft += elapsed_time - time_default;

        // Karatsuba test
        clock_gettime(CLOCK_MONOTONIC, &start);
        polynomial_multiply_karatsuba(random_Value_a, random_Value_b, n, result_karatsuba);
        clock_gettime(CLOCK_MONOTONIC, &end);
        elapsed_time = end.tv_sec - start.tv_sec + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
        time_karatsuba += elapsed_time - time_default;

        

        if (Correctness_Check(result_dft, result_iterative_fft) &&
            Correctness_Check(result_dft, result_recursive_fft) &&
            Correctness_Check(result_dft, result_karatsuba)){
                success++;
        }else{
            fail ++;
        }
        // Clear the space allocated for the number and the random state
        mpz_clears(result_recursive_fft, result_iterative_fft, result_dft, result_karatsuba, NULL);
        // Loading_Screen(iterations, i);
        

    }
    mpz_clears(random_Value_a, random_Value_b, NULL);

    printf("\nn size: %d\t iterations: %d\n", n, iterations);
    printf("Successful calculations:\t%d\nWrong calculations:\t%d\n", success, fail);
    printf("DFT multiplication time:\t%f seconds.\n", time_dft);
    printf("Karatsuba multiplication time:\t%f seconds.\n", time_karatsuba);
    printf("Recursive_FFT multiplication time:\t%f seconds.\n", time_fft);
    printf("Iterative_FFT multiplication time:\t%f seconds.\n", time_iterative_fft);
    
    gmp_randclear(state);

}




int main() {
    Polynomial_Multiply();
    // Test_Setup();
    return 0;
}