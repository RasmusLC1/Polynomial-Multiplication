#include "Runtime_test_systematic.h"

void Runtime_test_systematic() {
    // Set up correctness meassure
    int fail = 0, success = 0, n = 0;

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


    // Open the file in write mode ("w")
    FILE *file;
    file = fopen("Computation_times.txt", "w");

    // Check if the file was opened successfully
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    int max_n_size = 10;

    // Loop through the test multiple times to allow bigger tests
    // Also allows us to test n size vs iterations and their effect
    mpz_t result_standard, result_recursive_fft, result_iterative_fft, result_dft, result_karatsuba;
    float naive_time_array[20], karatsuba_time_array[20], dft_time_array[20], recursive_fft_time_array[20], iterative_fft_time_array[20];
    for (int i = 1; i <= max_n_size; i++) {
        n = pow(2, i);

        mpz_inits(result_standard, result_recursive_fft, result_iterative_fft, result_dft, result_karatsuba, NULL);

        // Generate a random number with n bits
        mpz_urandomb(random_Value_a, state, n);
        mpz_urandomb(random_Value_b, state, n);

        // Standard TEST
        clock_gettime(CLOCK_MONOTONIC, &start);
        Polynomial_Multiply_Naive(random_Value_a, random_Value_b, n, &result_standard);
        clock_gettime(CLOCK_MONOTONIC, &end);
        elapsed_time = end.tv_sec - start.tv_sec + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
        time_standard += elapsed_time - time_default;
        naive_time_array[i] = time_standard;

        // DFT TEST
        clock_gettime(CLOCK_MONOTONIC, &start);
        // polynomial_multiply_DFT(random_Value_a, random_Value_b, n, &result_dft);
        clock_gettime(CLOCK_MONOTONIC, &end);
        elapsed_time = end.tv_sec - start.tv_sec + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
        time_dft += elapsed_time - time_default;
        
        // Recursive FFT test
        clock_gettime(CLOCK_MONOTONIC, &start);
        polynomial_multiply_Recursive_FFT(random_Value_a, random_Value_b, n, &result_recursive_fft);
        clock_gettime(CLOCK_MONOTONIC, &end);
        elapsed_time = end.tv_sec - start.tv_sec + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
        time_fft += elapsed_time - time_default;
        recursive_fft_time_array[i] = time_fft;

        

        // Iterative FFT test
        clock_gettime(CLOCK_MONOTONIC, &start);
        polynomial_multiply_iterative_FFT(random_Value_a, random_Value_b, n, &result_iterative_fft);
        clock_gettime(CLOCK_MONOTONIC, &end);
        elapsed_time = end.tv_sec - start.tv_sec + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
        time_iterative_fft += elapsed_time - time_default;
        iterative_fft_time_array[i] = time_iterative_fft;

        // Karatsuba test
        clock_gettime(CLOCK_MONOTONIC, &start);
        polynomial_multiply_karatsuba(random_Value_a, random_Value_b, n, &result_karatsuba);
        clock_gettime(CLOCK_MONOTONIC, &end);
        elapsed_time = end.tv_sec - start.tv_sec + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
        time_karatsuba += elapsed_time - time_default;
        karatsuba_time_array[i] = time_karatsuba;

        
        if (Correctness_Check(result_standard, result_standard) &&
            Correctness_Check(result_standard, result_iterative_fft) &&
            Correctness_Check(result_standard, result_recursive_fft) &&
            Correctness_Check(result_standard, result_karatsuba)){
                
        }else{
            exit(1);
        }
        // Clear the space allocated for the number and the random state
        mpz_clears(result_standard, result_recursive_fft, result_iterative_fft, result_dft, result_karatsuba, NULL);
        
    }
    
    fprintf(file, "Naive multiplication:\t");
    for (int i = 1; i <= max_n_size; i++) {
        fprintf(file, "%f ", naive_time_array[i]);
    }
    fprintf(file, "\nKaratsuba multiplication:\t");
    for (int i = 1; i <= max_n_size; i++) {
        fprintf(file, "%f ", karatsuba_time_array[i]);
    }
    fprintf(file, "\nRecursive_FFT multiplication:\t");
    for (int i = 1; i <= max_n_size; i++) {
        fprintf(file, "%f ", recursive_fft_time_array[i]);
    }
    fprintf(file, "\nIterative_FFT multiplication:\t");
    for (int i = 1; i <= max_n_size; i++) {
        fprintf(file, "%f ", iterative_fft_time_array[i]);
    }

    fclose(file);
    mpz_clears(random_Value_a, random_Value_b, NULL);

    gmp_randclear(state);
}
