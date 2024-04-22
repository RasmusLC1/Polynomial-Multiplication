#include "Recursive_fft.h"
#include "iterative_fft.h"
#include "dft.h"
#include "karatsuba.h"
#include "test/WhiteBox_test.h"
#include "Helper_Functions.h"
// Getting terminal





void Polynomial_Multiply(int n, int iterations) {

    // Set up correctness meassure
    int fail = 0, success = 0;


    complex double a[n], b[n];

    // Initialize arrays with zeros for padding
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
    
    // Seed randomiser with time
    srand(time(NULL));

    // Check if the seed works and we get true random variables
    assert(rand() != rand());
    long long random_Value_a = 0, random_Value_b = 0;

    // Set up timers
    double time_dft = 0.0, time_fft = 0.0, time_iterative_fft = 0.0, time_karatsuba = 0.0;
    struct timespec start, end;
    double elapsed_time;


    // Loop through the test multiple times to allow bigger tests
    // Also allows us to test n size vs iterations and their effect
    long long result_fft = 0, result_iterative_fft = 0, result_dft = 0, result_karatsuba = 0;
    for (int i = 1; i <= iterations; i++) {
        
        // Calculate random values
        random_Value_a = rand() % (long long)pow(10, n/2);
        random_Value_b = rand() % (long long)pow(10, n/2);

        Int_to_Array(random_Value_a, a);
        Int_to_Array(random_Value_b, b);

        // Time DFT
        // THIS CODE HAS BEEN COMMENTED OUT TO COMPUTATIONAL COST IN TESTING
        // Time Recursive FFT using CLOCK_MONOTONIC for accuracy
        clock_gettime(CLOCK_MONOTONIC, &start);
        // result_dft = polynomial_multiply_DFT(a, b, n);
        clock_gettime(CLOCK_MONOTONIC, &end);
        elapsed_time = end.tv_sec - start.tv_sec + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
        time_dft += elapsed_time;

        // Time Recursive FFT using CLOCK_MONOTONIC for accuracy
        clock_gettime(CLOCK_MONOTONIC, &start);
        result_fft = polynomial_multiply_Recursive_FFT(a, b, n);
        clock_gettime(CLOCK_MONOTONIC, &end);
        elapsed_time = end.tv_sec - start.tv_sec + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
        time_fft += elapsed_time;

        // Time Iterative FFT using CLOCK_MONOTONIC for accuracy
        clock_gettime(CLOCK_MONOTONIC, &start);
        result_iterative_fft = polynomial_multiply_iterative_FFT(a, b, n);
        clock_gettime(CLOCK_MONOTONIC, &end);
        elapsed_time = end.tv_sec - start.tv_sec + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
        time_iterative_fft += elapsed_time;

        // Time Karatsuba using CLOCK_MONOTONIC for accuracy
        clock_gettime(CLOCK_MONOTONIC, &start);
        result_karatsuba = polynomial_multiply_karatsuba(a, b, n);
        clock_gettime(CLOCK_MONOTONIC, &end);
        elapsed_time = end.tv_sec - start.tv_sec + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
        time_karatsuba += elapsed_time;
        
        if (n <= 32){
            // Check if results are the same outside clock, to not affect timer
            if (Correctness_Check(result_fft, result_iterative_fft) && Correctness_Check(result_fft, result_karatsuba)){
                success++;
            } else{
                fail++;
            }
            // printf("%ld\n", result_fft); //Print results
        } else{
            printf("integer overflow!!!\n");
            exit(1);
        }
        Loading_Screen(iterations, i);

    }
    // Output time
    printf("\nn size: %d\t iterations: %d\n", n, iterations);
    printf("Successful calculations:\t%d\nWrong calculations:\t%d\n", success, fail);
    printf("DFT multiplication time:\t%f seconds.\n", time_dft);
    printf("Recursive_FFT multiplication time:\t%f seconds.\n", time_fft);
    printf("Iterative_FFT multiplication time:\t%f seconds.\n", time_iterative_fft);
    printf("karatsuba multiplication time:\t%f seconds.\n", time_karatsuba);
}




void White_Box_Testing() {
    int n = 16; // test size needs to be power 2
    complex double a[n], b[n]; //setting up arrays
    
    // Initialize arrays with zeros for padding
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));

    //TEST CASE SETUP:

    // Convert numbers to reverse arrays
    Int_to_Array(100, a);
    Int_to_Array(10, b);

    // Compute polynomial multiplication using DFT
    long result_dft = polynomial_multiply_DFT(a, b, n); 

    long result_karatsuba = polynomial_multiply_karatsuba(a, b, n);

    long result_iterative_fft = polynomial_multiply_iterative_FFT(a, b, n);

    // Compute polynomial multiplication using FFT
    long result_fft = polynomial_multiply_Recursive_FFT(a, b, n);

    printf("DFT result:\t%ld\n", result_dft);
    printf("karatsuba result:\t%ld\n", result_karatsuba);
    printf("FFT result:\t%ld\n", result_fft);
    printf("Iterative FFT result:\t%ld\n", result_iterative_fft);

}




int main() {
    int n = 16; // test size needs to be power 2, higher than 16 integer overflow
    int iterations = 100000;
    Polynomial_Multiply(n, iterations);
    // White_Box_Testing();
    return 0;
}