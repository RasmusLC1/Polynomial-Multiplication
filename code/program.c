#include "fft.h"
#include "iterative_fft.h"
#include "dft.h"
#include "karasuba.h"


// Check to see if results are identical
bool Correctness_Check(long result_karasuba, long result_fft, long result_iterative_fft) {
    if (result_karasuba != result_fft || result_fft != result_iterative_fft){
        printf("Results do not match\nresult_dft:\t%ld\nresult_fft:\t%ld\nresult_iterative_fft:\t%ld\n",
                result_karasuba, result_fft, result_iterative_fft);
        exit(1);
        return false;
    }
    return true; // Arrays are equal
}

void Polynomial_Multiply(int n, int iterations) {
    complex double a[n], b[n];

    // Initialize arrays with zeros for padding
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
    
    // Seed randomiser with time
    srand(time(NULL));

    // Check if the seed works and we get true random variables
    assert(rand() != rand());
    int randomValue = 0;

    // Initialize a and b with random single digit values
    for (int i = 0; i < n/4; i++) {
        randomValue = rand() % 10;
        a[i] = randomValue;
        randomValue = rand() % 10;
        b[i] = randomValue;
    }

    // Set up timers
    double time_fft = 0.0, time_dft = 0.0, time_karasuba = 0.0,
            time_iterative_fft = 0.0, time_default = 0.0;
    clock_t start_dft, end_dft, start_fft, end_fft, start_karasuba,
            end_karasuba, start_iterative_fft, end_iterative_fft,
            start_default, end_default;

    // Loop through the test multiple times to allow bigger tests
    // Also allows us to test n size vs iterations and their effect
    long result_fft = 0, result_iterative_fft = 0, result_dft = 0, result_karasuba = 0;
    for (int i = 0; i < iterations; i++) {

        // Time DFT
        // THIS CODE HAS BEEN COMMENTED OUT TO COMPUTATIONAL COST IN TESTING
        start_dft = clock();
        // result_dft = polynomial_multiply_DFT(a, b, n); 
        end_dft = clock();
        time_dft += (double)(end_dft - start_dft) / CLOCKS_PER_SEC;

        // Time FFT
        start_fft = clock();
        result_fft = polynomial_multiply_FFT(a, b, n);
        end_fft = clock();
        time_fft += (double)(end_fft - start_fft) / CLOCKS_PER_SEC;

        // Time iterative_FFT
        start_iterative_fft = clock();
        result_iterative_fft = polynomial_multiply_iterative_FFT(a, b, n);
        end_iterative_fft = clock();
        time_iterative_fft += (double)(end_iterative_fft - start_iterative_fft) / CLOCKS_PER_SEC;

        // time Karasuka
        start_karasuba = clock();
        result_karasuba = polynomial_multiply_Karasuba(a, b, n);
        end_karasuba = clock();
        time_karasuba += (double)(end_karasuba - start_karasuba) / CLOCKS_PER_SEC;

        // set a default time to remove the cost of setting the clock from the time
        start_default = clock();
        end_default = clock();
        time_default += (double)(end_default - start_default) / CLOCKS_PER_SEC;
        if (n < 30){
            // Check if results are the same outside clock, to not affect timer
            Correctness_Check(result_karasuba, result_fft, result_iterative_fft);
        }

    }
    time_dft -= time_default;
    time_fft -= time_default;
    time_iterative_fft -= time_default;
    time_karasuba -= time_default;
    // Output time
    printf("Default time:\t%f seconds.\n", time_default);
    printf("DFT multiplication time:\t%f seconds.\n", time_dft);
    printf("FFT multiplication time:\t%f seconds.\n", time_fft);
    printf("iterative_FFT multiplication time:\t%f seconds.\n", time_iterative_fft);
    printf("Karasuba multiplication time:\t%f seconds.\n", time_karasuba);
}




void White_Box_Testing() {
    int n = 16; // test size needs to be power 2
    complex double a[n], b[n]; //setting up arrays
    
    // Initialize arrays with zeros for padding
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));

    //TEST CASE SETUP:

    // // Initialize a and b with inverse number, I.E 27 = a[0] = 7 and a[1] = 2
    // // Coefficient of x^0 = a[0] and x^1=a[1]
    a[0] = 7; a[1] = 2; // Polynomial for 27
    b[0] = 9; b[1] = 3; // Polynomial for 39
    //What a now says is 7200 and b says 9300 because of n = 4. so we need 4 digits
    // The reason for this is 

    // // See above for explanation
    // a[0] = 4; a[1] = 6; a[2] = 5; 
    // b[0] = 4; b[1] = 3; b[2] = 2;

    long result_karasuba = polynomial_multiply_Karasuba(a, b, n);

    // Compute polynomial multiplication using DFT
    long result_dft = polynomial_multiply_DFT(a, b, n); 

    long result_iterative_fft = polynomial_multiply_iterative_FFT(a, b, n);

    // Compute polynomial multiplication using FFT
    long result_fft = polynomial_multiply_FFT(a, b, n);

    printf("DFT result:\t%ld\n", result_dft);
    printf("FFT result:\t%ld\n", result_fft);
    printf("Iterative FFT result:\t%ld\n", result_iterative_fft);
    printf("KARASUBA result:\t%ld\n", result_karasuba);

}




int main() {
    int n = 16; // test size needs to be power 2, higher than 32 integer overflow
    int iterations = 1000;
    // Polynomial_Multiply(n, iterations);
    White_Box_Testing();
    return 0;
}