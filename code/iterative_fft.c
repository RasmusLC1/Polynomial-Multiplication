#include "iterative_fft.h"



void Iterative_FFT(complex double* input, int n, complex double* output) {
    int reverse_bit;
    // bit reversal of the given array, this step from pseudocode: bit-reverse-copy(a, A)
    // Example: Index 3: 011 (binary) → Bit-reversed: 110 → Reverse index 6
    // so instead of working with index 3, we are now working with index 6
    // This reorders the array elements and allows them to be merged more efficiently
    int log2n = log2(n);

    for (unsigned int i = 0; i < n; ++i) {
        reverse_bit = Bit_Reverse(i, log2n);
        output[i] = input[reverse_bit];
    }

    int fft_segment_length, fft_half_segment_length;
    complex double unity_root_factor, segment_root_of_unity, twiddle_factor, tmp;
    // FFT computation
    // The outer loop runs log_2(n) times, but within the loops it will cover all n
    // elements, therefore the runtime is O(n log n) times.
    for (int s = 1; s <= log2n; ++s) {
        fft_segment_length = 1 << s; // pow(2, s)
         // Principal root of unity for the current segment
        segment_root_of_unity = cexp(-I * TAU / fft_segment_length);

        for (int k = 0; k < n; k += fft_segment_length) {
            // Initialize unity root factor (ω) to 1, use 0*I to create complex number
            unity_root_factor = 1 + 0 * I;
            fft_half_segment_length = fft_segment_length >> 1; // /2
            for (int j = 0; j < fft_half_segment_length; ++j) {
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
    for (unsigned int i = 0; i < n; ++i) {
        reverse_bit = Bit_Reverse(i, log2n);
        output[i] = input[reverse_bit];
    }

    int fft_segment_length, fft_half_segment_length;
    complex double unity_root_factor, segment_root_of_unity, twiddle_factor, tmp;
    // IFFT computation
    for (int s = 1; s <= log2n; ++s) {
        fft_segment_length = pow(2, s);
         // Principal root of unity for the current segment
        segment_root_of_unity = cexp(I * TAU / fft_segment_length);

        for (int k = 0; k < n; k += fft_segment_length) {
            // Initialize unity root factor (ω) to 1, use 0*I to create complex number
            unity_root_factor = 1 + 0 * I;
            fft_half_segment_length = fft_segment_length >> 1;
            for (int j = 0; j < fft_half_segment_length; ++j) {
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



long polynomial_multiply_iterative_FFT(long a, long b, int n) {
    
    bool negative = false;

    if (a < 0 && b >= 0){
        negative = true;
        a *= -1;
    } else if (b < 0 && a >= 0){
        negative = true;
        b *= -1;
    }
    
    // Pad the inputs with zeros, the polynomials are represented as arays
    // Padding ensures the data is clean
    // Arrays help structure the data into parts
    complex double padded_a[n], padded_b[n], result[n];
    memset(padded_a, 0, n * sizeof(complex double));
    memset(padded_b, 0, n * sizeof(complex double));
    memset(result, 0, n * sizeof(complex double));
    
    Int_to_Array(a, padded_a);
    Int_to_Array(b, padded_b);
    // outputpply FFT to both padded polynomials
    complex double fa[n], fb[n];
    Iterative_FFT(padded_a, n, fa);
    Iterative_FFT(padded_b, n, fb);

    // multiply the FFTs
    for (int i = 0; i < n; i++) {
        fa[i] *= fb[i];
    }

    // output IFFT to get the product polynomial
    Iterative_IFFT(fa, n, result);

    long long fft_total_result = 0;
    // Call IFFT normalisation outside the recursive loop
    for (int i = 0; i < n; i++) {
        fft_total_result += (long long)(creal(result[i])+0.5)*pow(10,i); // adding 0.5 to always round up
    }

    if (negative){
        fft_total_result *= -1;
    }
    
    return fft_total_result;
}