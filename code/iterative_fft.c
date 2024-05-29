#include "iterative_fft.h"



void Iterative_FFT(complex double* input, int n, complex double* output) {
    int reverse_bit;
    // bit reversal of the given array, this step from pseudocode: bit-reverse-copy(a, A)
    // Example: Index 3: 011 (binary) → Bit-reversed: 110 → Reverse index 6
    // so instead of working with index 3, we are now working with index 6
    // This reorders the array elements and allows them to be merged more efficiently
    int log2n = log2(n);

    for (unsigned int i = 0; i < n; i++) {
        reverse_bit = Bit_Reverse(i, log2n);
        output[i] = input[reverse_bit];
    }

    int fft_segment_length, fft_half_segment_length;
    complex double unity_root_factor, segment_root_of_unity,
                    twiddle_factor, tmp;
    // FFT computation
    // The outer loop runs log_2(n) times, but within the loops it will cover all n
    // elements, therefore the runtime is O(n log n) times.
    for (int s = 1; s <= log2n; s++) {
        fft_segment_length = 1 << s; // pow(2, s)
         // Principal root of unity for the current segment
        segment_root_of_unity = cexp(-I * TAU / fft_segment_length);

        for (int k = 0; k < n; k += fft_segment_length) {
            // Initialize unity root factor (ω) to 1, use 0*I to create complex number
            unity_root_factor = 1 + 0 * I;
            fft_half_segment_length = fft_segment_length >> 1; // /2
            for (int j = 0; j < fft_half_segment_length; j++) {
                // Twiddle factor application: https://en.wikipedia.org/wiki/Twiddle_factor
                twiddle_factor = unity_root_factor *
                                output[k + j + fft_half_segment_length];
                tmp = output[k + j];

                // Applying FFT butterfly updates
                output[k + j] = tmp + twiddle_factor;
                output[k + j + fft_half_segment_length] = tmp - twiddle_factor;

                // Update the unity root factor
                unity_root_factor *= segment_root_of_unity;
            }
        }
    }
}

void Iterative_IFFT(complex double* input, int n, complex double* output) {
    int reverse_bit;
    // bit reversal of the given array, this step from pseudocode: bit-reverse-copy(a, A)
    // Example: Index 3: 011 (binary) → Bit-reversed: 110 → Reverse index 6
    //          so instead of working with index 3, we are now working with index 6
    // This reorders the array elements and allows them to be merged more efficiently
    int log2n = log2(n);
    for (unsigned int i = 0; i < n; i++) {
        reverse_bit = Bit_Reverse(i, log2n);
        output[i] = input[reverse_bit];
    }

    int fft_segment_length, fft_half_segment_length;
    complex double unity_root_factor, segment_root_of_unity, twiddle_factor, tmp;
    // IFFT computation
    for (int s = 1; s <= log2n; s++) {
        fft_segment_length = pow(2, s);
         // Principal root of unity for the current segment
        segment_root_of_unity = cexp(I * TAU / fft_segment_length);

        for (int k = 0; k < n; k += fft_segment_length) {
            // Initialize unity root factor (ω) to 1, use 0*I to create complex number
            unity_root_factor = 1 + 0 * I;
            fft_half_segment_length = fft_segment_length >> 1;
            for (int j = 0; j < fft_half_segment_length; j++) {
                // Twiddle factor application: https://en.wikipedia.org/wiki/Twiddle_factor
                twiddle_factor = unity_root_factor *
                                output[k + j + fft_half_segment_length];
                tmp = output[k + j];

                // Applying FFT butterfly updates
                output[k + j] = tmp + twiddle_factor;
                output[k + j + fft_half_segment_length] = tmp - twiddle_factor;

                // Update the unity root factor
                unity_root_factor *= segment_root_of_unity;
            }
        }
    }

    // Normalize the output by dividing by n
    for (int i = 0; i < n; i++) {
        output[i] /= n;
    }
}



double polynomial_multiply_iterative_FFT(mpz_t a, mpz_t b, int n,
                                        mpz_t* iterative_fft_total_result) {
    
    // Check for negative numbers
    bool negative = negative_check(a, b);

    
    // Pad the inputs with zeros, the polynomials are represented as arays
    // Padding ensures the data is clean
    // Arrays help structure the data into parts
    complex double padded_a[n], padded_b[n], fft_result[n];
    memset(padded_a, 0, n * sizeof(complex double));
    memset(padded_b, 0, n * sizeof(complex double));
    memset(fft_result, 0, n * sizeof(complex double));

    mpz_to_complex_array(a, padded_a);
    mpz_to_complex_array(b, padded_b);

    // // Apply FFT to both polynomials
    complex double fa[n], fb[n];
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);

    Iterative_FFT(padded_a, n, fa);
    Iterative_FFT(padded_b, n, fb);

    // // Point-wise multiply the FFTs
    for (int i = 0; i < n; i++) {
        fa[i] *= fb[i];
    }

    // // Apply IFFT to get the product polynomial
    Iterative_IFFT(fa, n, fft_result);
    clock_gettime(CLOCK_MONOTONIC, &end);

    double elapsed_time = end.tv_sec - start.tv_sec + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
    


    // //Convert to the real number
    complex_array_to_mpz(fft_result, n, iterative_fft_total_result);

    // Add correct sign back
    if (negative){
        mpz_t negative_value;
        mpz_init(negative_value);
        mpz_set_str(negative_value, "-1", 10);
        mpz_mul(iterative_fft_total_result[0],
                iterative_fft_total_result[0], negative_value);
        mpz_clear(negative_value);
    }

    return elapsed_time;
}