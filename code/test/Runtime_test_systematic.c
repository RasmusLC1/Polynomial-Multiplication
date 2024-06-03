#include "Runtime_test_systematic.h"

void Runtime_test_systematic() {
    // Set up correctness meassure
    int fail = 0, n = 0;

    mpz_t random_Value_a, random_Value_b;
    mpz_inits(random_Value_a, random_Value_b, NULL);

    // Seed the random state with current time
    gmp_randstate_t state;
    gmp_randinit_default(state);
    gmp_randseed_ui(state, time(NULL));

    // Set up timers
    double time_naive = 0.0, time_dft = 0.0, time_fft = 0.0,
            time_iterative_fft = 0.0, time_karatsuba = 0.0;


    // Open the file in write mode ("w")
    FILE *file;
    file = fopen("test/Computation_times.txt", "w");

    // Check if the file was opened successfully
    if (file == NULL) {
        printf("Error opening file!\n");
        exit(1);
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
        int *naive_result = (int *)malloc(n * sizeof(int));
        int *dft_result = (int *)malloc(n * sizeof(int));
        int *karatsuba_result = (int *)malloc(n * sizeof(int));
        int *recursive_FFT_result = (int *)malloc(n * sizeof(int));
        int *iterative_FFT_result = (int *)malloc(n * sizeof(int));



        memset(naive_result, 0, n * sizeof(int));
        memset(karatsuba_result, 0, n * sizeof(int));
        memset(dft_result, 0, n * sizeof(int));
        memset(recursive_FFT_result, 0, n * sizeof(int));
        memset(iterative_FFT_result, 0, n * sizeof(int));


        mpz_inits(result_standard, result_recursive_fft, result_iterative_fft, result_dft, result_karatsuba, NULL);

        // Generate a random number with n bits
        mpz_urandomb(random_Value_a, state, n);
        mpz_urandomb(random_Value_b, state, n);

        // Standard TEST
        time_naive = Polynomial_Multiply_Naive(random_Value_a, random_Value_b, n, naive_result);
        naive_time_array[i] = time_naive;

        // DFT TEST
        // time_dft = polynomial_multiply_DFT(random_Value_a, random_Value_b, n, dft_result);
        dft_time_array[i] = time_dft;


        // Recursive FFT test
        time_fft = polynomial_multiply_Recursive_FFT(random_Value_a, random_Value_b, n, recursive_FFT_result);

        recursive_fft_time_array[i] = time_fft;


        // Iterative FFT test
        time_iterative_fft = polynomial_multiply_iterative_FFT(random_Value_a, random_Value_b, n, iterative_FFT_result);
        iterative_fft_time_array[i] = time_iterative_fft;

        // Karatsuba test
        time_karatsuba = polynomial_multiply_karatsuba(random_Value_a, random_Value_b, n, karatsuba_result);
        karatsuba_time_array[i] = time_karatsuba;

        
        if (Polynomial_Correctness(naive_result, karatsuba_result, n)  &&
            Polynomial_Correctness(naive_result, naive_result, n)  &&
            Polynomial_Correctness(naive_result, recursive_FFT_result, n)  &&
            Polynomial_Correctness(naive_result, iterative_FFT_result, n)){
                
        }else{
        }
        // Clear the space allocated for the number and the random state
        mpz_clears(result_standard, result_recursive_fft, result_iterative_fft, result_dft, result_karatsuba, NULL);
        // Ensure to free the allocated memory when it's no longer needed
        free(naive_result);
        free(dft_result);
        free(karatsuba_result);
        free(recursive_FFT_result);
        free(iterative_FFT_result);

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
