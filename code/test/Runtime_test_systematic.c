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
    file = fopen("test/Computation_times.txt", "w");

    // Check if the file was opened successfully
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    int max_n_size = 16;

    // Loop through the test multiple times to allow bigger tests
    // Also allows us to test n size vs iterations and their effect
    mpz_t result_standard, result_recursive_fft, result_iterative_fft, result_dft, result_karatsuba;
    int n_array[20];
    float naive_time_array[20], karatsuba_time_array[20], dft_time_array[20], recursive_fft_time_array[20], iterative_fft_time_array[20];
    for (int i = 1; i <= max_n_size; i++) {
        n = pow(2, i);
        n_array[i] = n;

        mpz_inits(result_standard, result_recursive_fft, result_iterative_fft, result_dft, result_karatsuba, NULL);

        // Generate a random number with n bits
        mpz_urandomb(random_Value_a, state, n);
        mpz_urandomb(random_Value_b, state, n);

        // Standard TEST
        time_standard = Polynomial_Multiply_Naive(random_Value_a, random_Value_b, n, &result_standard);
        naive_time_array[i] = time_standard;

        // DFT TEST
        // time_dft = polynomial_multiply_DFT(random_Value_a, random_Value_b, n, &result_dft);
        dft_time_array[i] = time_dft;


        // Recursive FFT test
        time_fft = polynomial_multiply_Recursive_FFT(random_Value_a, random_Value_b, n, &result_recursive_fft);

        recursive_fft_time_array[i] = time_fft;


        // Iterative FFT test
        time_iterative_fft = polynomial_multiply_iterative_FFT(random_Value_a, random_Value_b, n, &result_iterative_fft);
        iterative_fft_time_array[i] = time_iterative_fft;

        // Karatsuba test
        time_karatsuba = polynomial_multiply_karatsuba(random_Value_a, random_Value_b, n, &result_karatsuba);
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
    fprintf(file, "n_size:\t");
    for (int i = 1; i <= max_n_size; i++) {
        fprintf(file, "%d ", n_array[i]);
    }
    fprintf(file, "\nNaive multiplication:\t");
    for (int i = 1; i <= max_n_size; i++) {
        fprintf(file, "%f ", naive_time_array[i]);
    }
    fprintf(file, "\nDFT multiplication:\t");
    for (int i = 1; i <= max_n_size; i++) {
        fprintf(file, "%f ", dft_time_array[i]);
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
