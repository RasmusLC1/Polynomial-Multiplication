#include "fft.h"


int total_computations;

// Extended FFT function with allocated_memory parameters
void FFT_ext(complex double *f, int n, complex double *out,
            complex double *allocated_memory, int allocated_memory_size) {
    total_computations++;
    // Check if n == 1 and return f(1) (f[0])
    if (n == 1) {
        out[0] = f[0];
        return;
    }

    // Save n/2 in a variable to save computations
    int n_half = n / 2;

    // Use the passed allocated_memory instead of allocating memory
    // set pointer to start of allocated_memory
    complex double *even_values = allocated_memory;
    // set pointer to the second quarter of allocated memory
    complex double *odd_values = allocated_memory + n_half; 
    // set pointer to the third quarter of allocated memory
    complex double *out_even_values = odd_values + n_half;
    // set pointer to the fourth quarter of allocated memory
    complex double *out_odd_values = out_even_values + n_half;

    for (int i = 0; i < n_half; i++) {
        even_values[i] = f[2 * i];
        odd_values[i] = f[2 * i + 1];
    }

    // Double recursive call, half the allocated memory since we are splitting the data
    FFT_ext(even_values, n_half, out_even_values, out_odd_values + n_half, allocated_memory_size / 2);
    FFT_ext(odd_values, n_half, out_odd_values, out_odd_values + n_half, allocated_memory_size / 2);

    // Compute the FFT output
    complex double tmp = 0;
    for (int k = 0; k < n_half; k++) {
        // Use defined TAU to save multiplication and calculate e^{−i*TAU*n/k​}
        // directly to save calculations
        tmp = cexp(-I * TAU * k / n) * out_odd_values[k];
        out[k] = out_even_values[k] + tmp;
        out[k + n_half] = out_even_values[k] - tmp;
    }
}

// Extended IFFT function with allocated_memory parameters
void IFFT_ext(complex double *f, int n, complex double *out,
                complex double *allocated_memory, int allocated_memory_size) {
    // total_computations++;
    if (n == 1) {
        out[0] = f[0];
        return;
    }
    // Save n/2 in a variable to save computations
    int n_half = n / 2;

    // Use the passed allocated_memory instead of allocating memory
    // set pointer to start of allocated_memory
    complex double *even_values = allocated_memory;
    // set pointer to the second quarter of allocated memory
    complex double *odd_values = allocated_memory + n_half; 
    // set pointer to the third quarter of allocated memory
    complex double *out_even_values = odd_values + n_half;
    // set pointer to the fourth quarter of allocated memory
    complex double *out_odd_values = out_even_values + n_half;

    // Divide into even (even_values) and odd (odd_values)
    for (int i = 0; i < n_half; i++) {
        even_values[i] = f[2 * i];
        odd_values[i] = f[2 * i + 1];
    }

    // Double recursive call, half the allocated memory since we are splitting the data
    IFFT_ext(even_values, n_half, out_even_values, out_odd_values + n_half, allocated_memory_size / 2);
    IFFT_ext(odd_values, n_half, out_odd_values, out_odd_values + n_half, allocated_memory_size / 2);

    // Compute the FFT output
    complex double tmp = 0;
    for (int k = 0; k < n_half; k++) {
        // Use defined TAU to save multiplication and calculate e^{−i*TAU*n/k​}
        // directly to save calculations
        tmp = cexp(I * TAU * k / n) * out_odd_values[k];
        out[k] = out_even_values[k] + tmp;
        out[k + n_half] = out_even_values[k] - tmp;
    }
}

// Wrapper function for FFT to handle allocated_memory allocation
void FFT(complex double *input, int n, complex double *out) {
    // Assign memory outside the recursive loop to save overhead
    // We need 4 arrays, in_even, in_odd, out_even and out_odd. Therefore we need 4 * n
    complex double *allocated_memory = (complex double *)malloc(4 * n * sizeof(complex double));
    
    // Call the actual function
    FFT_ext(input, n, out, allocated_memory, 4 * n);
    free(allocated_memory);
}


// IFFT function to handle allocated_memory allocation and call actual IFFT function
void IFFT(complex double *f, int n, complex double *out) {
    // Assign memory outside the recursive loop to save overhead
    complex double *allocated_memory = (complex double *)malloc(4 * n * sizeof(complex double));
    
    // Call the actual function
    IFFT_ext(f, n, out, allocated_memory, 4 * n);
    free(allocated_memory);
}


long polynomial_multiply_FFT(complex double* a, complex double* b, int n) {
    total_computations = 0;
    
    complex double padded_a[n], padded_b[n], result[n];
    // Pad the inputs with zeros, the polynomials are represented as arays
    // Padding ensures the data is clean
    // Arrays help structure the data into parts
    memset(padded_a, 0, n * sizeof(complex double));
    memset(padded_b, 0, n * sizeof(complex double));
    memset(result, 0, n * sizeof(complex double));

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

    long fft_total_result = 0;
    // Call IFFT normalisation outside the recursive loop
    for (int i = 0; i < n; i++) {
        result[i] /= n; // Normalise
        fft_total_result += (long)(creal(result[i])+0.5)*pow(10,i); // adding 0.5 to always round up
    }

    // printf("FFT Computations:\t%d\n", total_computations);
    
    return fft_total_result;
}
