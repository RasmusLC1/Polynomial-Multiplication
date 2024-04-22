#include "WhiteBox_test.h"

void Basic_multiplication() {
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