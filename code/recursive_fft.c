#include "Recursive_fft.h"



// Extended FFT function with allocated_memory parameters
void Recursive_FFT_ext(complex double *f, int n, complex double *out,
            complex double *allocated_memory, int allocated_memory_size) {
    // Check if n == 1 and return f(1) (f[0])
    if (n == 1) {
        out[0] = f[0];
        return;
    }

    // Save n/2 in a variable to save computations
    int n_half = n >> 1; // /2

    // Use the passed allocated_memory instead of allocating memory
    // set pointer to start of allocated_memory
    complex double *even_values = allocated_memory;
    // set pointer to the second quarter of allocated memory
    complex double *odd_values = allocated_memory + n_half; 
    // set pointer to the third quarter of allocated memory
    complex double *out_even_values = odd_values + n_half;
    // set pointer to the fourth quarter of allocated memory
    complex double *out_odd_values = out_even_values + n_half;

    // Seperate into odd and even numbers
    int i_double = 0;
    for (int i = 0; i < n_half; i++) {
        i_double = i << 1;
        even_values[i] = f[i_double];
        odd_values[i] = f[i_double + 1];
    }

    // Double recursive call, half the allocated memory since we are splitting the data
    // Here there are 2 recursive calls, which each split the array in half, therefore:
        // T(n) = 2T(n/2) + O(n)
    // Applying the master theorem, here log_2(2) = 1 and C = 1 because f(n) = O(n)
    // Therefore we get the second option and our runtime becomes:
        // T(N) = Θ(n log n)
    Recursive_FFT_ext(even_values, n_half, out_even_values,
                        out_odd_values + n_half, allocated_memory_size >> 1);
    Recursive_FFT_ext(odd_values, n_half, out_odd_values,
                        out_odd_values + n_half, allocated_memory_size >> 1);

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
void Recursive_IFFT_ext(complex double *f, int n, complex double *out,
                complex double *allocated_memory, int allocated_memory_size) {
    if (n == 1) {
        out[0] = f[0];
        return;
    }
    // Save n/2 in a variable to save computations
    int n_half = n >> 1;

    // Use the passed allocated_memory instead of allocating memory
    // set pointer to start of allocated_memory
    complex double *even_values = allocated_memory;
    // set pointer to the second quarter of allocated memory
    complex double *odd_values = allocated_memory + n_half; 
    // set pointer to the third quarter of allocated memory
    complex double *out_even_values = odd_values + n_half;
    // set pointer to the fourth quarter of allocated memory
    complex double *out_odd_values = out_even_values + n_half;

    // Seperate into odd and even numbers
    int i_double = 0;
    for (int i = 0; i < n_half; i++) {
        i_double = i << 1;
        even_values[i] = f[i_double];
        odd_values[i] = f[i_double + 1];
    }

    // Double recursive call, half the allocated memory since we are splitting the data
    Recursive_IFFT_ext(even_values, n_half, out_even_values,
                        out_odd_values + n_half, allocated_memory_size >> 1);
    Recursive_IFFT_ext(odd_values, n_half, out_odd_values,
                        out_odd_values + n_half, allocated_memory_size >> 1);

    // Compute the FFT output
    complex double tmp = 0;
    for (int k = 0; k < n_half; k++) {
        // Use defined TAU to save multiplication and calculate e^{−i*TAU*n/k​}
        // directly in tmp to save calculations
        tmp = cexp(I * TAU * k / n) * out_odd_values[k];
        out[k] = out_even_values[k] + tmp;
        out[k + n_half] = out_even_values[k] - tmp;
    }
}

// Wrapper function for FFT to handle allocated_memory allocation
void Recursive_FFT(complex double *input, int n, complex double *out) {
    // Assign memory outside the recursive loop to save overhead
    // We need 4 arrays, in_even, in_odd, out_even and out_odd. Therefore we need 4 * n
    int n_bitshifted = n << 2; // * 4
    complex double *allocated_memory = (complex double *)malloc(n_bitshifted * sizeof(complex double));
    
    // Call the actual function
    Recursive_FFT_ext(input, n, out, allocated_memory, n >> 2);
    free(allocated_memory);
}


// IFFT function to handle allocated_memory allocation and call actual IFFT function
void Recursive_IFFT(complex double *f, int n, complex double *out) {
    // Assign memory outside the recursive loop to save overhead
    int n_bitshifted = n << 2; // * 4
    complex double *allocated_memory = (complex double *)malloc(n_bitshifted * sizeof(complex double));
    
    // Call the actual function
    Recursive_IFFT_ext(f, n, out, allocated_memory, n >> 2);
    free(allocated_memory);

    // Normalize the output by dividing by n
    for (int i = 0; i < n; i++) {
        out[i] /= n;
    }
}


long polynomial_multiply_Recursive_FFT(complex double* a, complex double* b, int n) {
    
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
    Recursive_FFT(padded_a, n, fa);
    Recursive_FFT(padded_b, n, fb);

    // multiply the FFTs
    for (int i = 0; i < n; i++) {
        fa[i] *= fb[i];
    }

    // Apply IFFT to get the product polynomial
    Recursive_IFFT(fa, n, result);

    long long fft_total_result = 0;
    // Call IFFT normalisation outside the recursive loop
    for (int i = 0; i < n; i++) {
        fft_total_result += (long long)(creal(result[i])+0.5)*pow(10,i); // adding 0.5 to always round up
    }
    
    return fft_total_result;
}
