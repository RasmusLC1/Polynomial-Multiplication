#include "dft.h"

int dft_computations = 0;


void DFT(complex double *in, int n, complex double *out) {
    // 2 nested for loops is what causes the runtime n^2
    for (int i = 0; i < n; i++) { // For each output element

        // initialise each element to 0
        out[i] = 0;
        for (int t = 0; t < n; t++) { // For each input element
            dft_computations++;
            // Compute DFT function
            out[i] += in[t] * cexp(-I * TAU * t * i / n);
        }
    }
}

// Inverse DFT
void IDFT(complex double *in, int n, complex double *out) {

    // 2 nested for loops is what causes the runtime n^2
    for (int i = 0; i < n; i++) { // For each output element

        // initialise each element to 0
        out[i] = 0;
        for (int k = 0; k < n; k++) { // For each input element
            dft_computations++;
            // Compute inverse DFT function by changing the sign
            // This is the only change from DFT
            out[i] += in[k] * cexp(I * TAU * k * i / n);
        }
        out[i] /= n; // Scale by 1/n, ensuring proper normalization
    }
}


long polynomial_multiply_DFT(complex double *a, complex double *b, int n) {
    
    // Pad the inputs with zeros, the polynomials are represented as arays
    // Padding ensures the data is clean
    // Arrays help structure the data into parts
    complex double padded_a[n], padded_b[n], result[n];
    memset(padded_a, 0, n * sizeof(complex double));
    memset(padded_b, 0, n * sizeof(complex double));
    memset(result, 0, n * sizeof(complex double));
    
    // Write the initial polynomials onto the padded polynomials
    for (int i = 0; i < n; i++) {
        padded_a[i] = a[i];
        padded_b[i] = b[i];
    }

    // Apply DFT to both polynomials
    complex double fa[n], fb[n];
    DFT(padded_a, n, fa);
    DFT(padded_b, n, fb);

    // Point-wise multiply the DFTs
    for (int i = 0; i < n; i++) {
        fa[i] *= fb[i];
    }

    // Apply IDFT to get the product polynomial
    IDFT(fa, n, result);

    //Convert to the real number
    long dft_total_result = 0;
    for (int i = 0; i < n; i++) {
        // Get the actual result of the fft
        dft_total_result += (int)(creal(result[i])+0.5)*pow(10,i); // adding 0.5 to always round up
        // printf("FFT sum:\t%d\n", fft_current_result); // print the increment steps
    }
    return dft_total_result;

}