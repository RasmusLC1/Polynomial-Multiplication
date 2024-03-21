#include "fft.h"


int fft_computations = 0;

// Recursive implementation of FFT
void FFT(complex double *f, int n, complex double *out) {
    // Check if n == 1 and return f(1) (f[0])
    if (n == 1) {
        out[0] = f[0];
        return;
    }
    // Save n/2 in a variable to save computations
    int n_half = n/2;

    // Allocate memory
    complex double *even_values = (complex double *)malloc(n_half * sizeof(complex double));
    complex double *odd_values = (complex double *)malloc(n_half * sizeof(complex double));
    complex double *out_even_values = (complex double *)malloc(n_half * sizeof(complex double));
    complex double *out_odd_values = (complex double *)malloc(n_half * sizeof(complex double));

    // Divide into even (even_values) and odd (odd_values)
    for (int i = 0; i < n_half; i++) {
        fft_computations++;
        even_values[i] = f[2 * i];
        odd_values[i] = f[2 * i + 1];
    }

    // Recursively call each half
    FFT(even_values, n_half, out_even_values);
    FFT(odd_values, n_half, out_odd_values);

    // Compute the FFT output
    complex double temp = 0;
    for (int k = 0; k < n_half; k++) {
        // Use defined TAU to save multiplication and calculate e^{−i*TAU*n/k​}
        // directly to save calculations
        temp = cexp(- I * TAU * k / n) * out_odd_values[k]; 
        out[k] = out_even_values[k] + temp; // Assign left half of return array
        out[k + n_half] = out_even_values[k] - temp; // Assign right half of return array
        fft_computations++;

    }

    // Free allocated memory
    free(even_values);
    free(odd_values);
    free(out_even_values);
    free(out_odd_values);
}

// Recursive implementation of Inverse FFT
void IFFT(complex double *f, int n, complex double *out) {
    // Check if n == 1 and return f(1) (f[0]) 
    if (n == 1) {
        out[0] = f[0];
        return;
    }

    // Save n/2 in a variable to save computations
    int n_half = n/2;

    // Allocate memory
    complex double *even_values = (complex double *)malloc(n_half * sizeof(complex double));
    complex double *odd_values = (complex double *)malloc(n_half * sizeof(complex double));
    complex double *out_even_values = (complex double *)malloc(n_half * sizeof(complex double));
    complex double *out_odd_values = (complex double *)malloc(n_half * sizeof(complex double));
    
    // Divide into even and odd values
    for (int i = 0; i < n_half; i++) {
        fft_computations++;
        even_values[i] = f[2 * i];
        odd_values[i] = f[2 * i + 1];
    }

    // Recursively call each half
    IFFT(even_values, n_half, out_even_values);
    IFFT(odd_values, n_half, out_odd_values);

    // Compute the FFT output, use k instead of i because we use I to represent
    // imaginary numbers
    for (int k = 0; k < n_half; k++) {
        // Use defined TAU to save multiplication and calculate e^{−i*TAU*n/k​}
        // directly to save calculations
        // The only change from FFT is the sign in the exponent
        fft_computations++;

        complex double t = cexp(I * TAU * k / n) * out_odd_values[k];
        out[k] = out_even_values[k] + t;
        out[k + n_half] = out_even_values[k] - t;
    }

    //Free allocated memory
    free(even_values);
    free(odd_values);
    free(out_even_values);
    free(out_odd_values);

}


void polynomial_multiply_FFT(complex double* a, complex double* b, int n, complex double* result) {
    
    // Pad the inputs with zeros, the polynomials are represented as arays
    // Padding ensures the data is clean
    // Arrays help structure the data into parts
    complex double padded_a[n], padded_b[n];
    memset(padded_a, 0, n * sizeof(complex double));
    memset(padded_b, 0, n * sizeof(complex double));

    // Write the initial polynomials onto the padded polynomials
    for (int i = 0; i < n; i++) {
        padded_a[i] = a[i];
        padded_b[i] = b[i];
    }

    // Apply FFT to both padded polynomials
    complex double fa[n], fb[n];
    FFT(padded_a, n, fa);
    FFT(padded_b, n, fb);

    // multiply the FFTs
    for (int i = 0; i < n; i++) {
        fa[i] *= fb[i];
    }

    // Apply IFFT to get the product polynomial
    IFFT(fa, n, result);

    // Call IFFT normalisation outside the recursive loop
    for (int i = 0; i < n; i++) {
        result[i] /= n;
    }
}
