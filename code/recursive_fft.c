#include "Recursive_fft.h"



// Extended FFT function with allocated_memory parameters
void Recursive_FFT_ext(complex double *input, int n, complex double *out,
            complex double *allocated_memory, int allocated_memory_size) {
    // Check if n == 1 and return f(1) (f[0])
    if (n == 1) {
        out[0] = input[0];
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
        even_values[i] = input[i_double];
        odd_values[i] = input[i_double + 1];
    }

    // Double recursive call, half the allocated memory since we are splitting the data
    // Here there are 2 recursive calls, which each split the array in half, therefore:
        // T(n) = 2T(n/2) + O(n)
    // Applying the master theorem, here log_2(2) = 1 and C = 1 because f(n) = O(n)
    // Therefore we get the second option and our runtime becomes:
        // T(N) = Θ(n log n)
    Recursive_FFT_ext(even_values, n_half, out_even_values,
                        out_odd_values + n_half, allocated_memory_size);
    Recursive_FFT_ext(odd_values, n_half, out_odd_values,
                        out_odd_values + n_half, allocated_memory_size);

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

// FFT function to allocate memory and call actual FFT functionn
void Recursive_FFT(complex double *input, int n, complex double *out) {
    // Assign memory outside the recursive loop to save overhead
    // We need 4 arrays, in_even, in_odd, out_even and out_odd. Therefore we need 4 * n
    int n_bitshifted = n << 2; // * 4
    complex double *allocated_memory = (complex double *) malloc(n_bitshifted *
                                        sizeof(complex double));
    
    // Call the actual function
    Recursive_FFT_ext(input, n, out, allocated_memory, n);
    free(allocated_memory);

}

// Extended IFFT function with allocated_memory parameters
void Recursive_IFFT_ext(complex double *input, int n, complex double *out,
                complex double *allocated_memory, int allocated_memory_size) {
    if (n == 1) {
        out[0] = input[0];
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
        even_values[i] = input[i_double];
        odd_values[i] = input[i_double + 1];
    }

    // Double recursive call, half the allocated memory since we are splitting the data
    Recursive_IFFT_ext(even_values, n_half, out_even_values,
                        out_odd_values + n_half, allocated_memory_size);
    Recursive_IFFT_ext(odd_values, n_half, out_odd_values,
                        out_odd_values + n_half, allocated_memory_size);

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




// IFFT function to allocate memory and call actual IFFT function
void Recursive_IFFT(complex double *input, int n, complex double *out) {
    // Assign memory outside the recursive loop to save overhead
    int n_bitshifted = n << 2; // * 4
    complex double *allocated_memory = (complex double *)malloc(n_bitshifted *
                                        sizeof(complex double));
    
    // Call the actual function
    Recursive_IFFT_ext(input, n, out, allocated_memory, n);
    free(allocated_memory);

    // Normalize the output by dividing by n
    for (int i = 0; i < n; i++) {
        out[i] /= n;
    }
}


void polynomial_multiply_Recursive_FFT(mpz_t a, mpz_t b, int n,
                                        mpz_t* recursive_fft_total_result) {

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
    Recursive_FFT(padded_a, n, fa);
    Recursive_FFT(padded_b, n, fb);

    // // Point-wise multiply the FFTs
    for (int i = 0; i < n; i++) {
        fa[i] *= fb[i];
    }

    // // Apply IFFT to get the product polynomial
    Recursive_IFFT(fa, n, fft_result);

    // //Convert to the real number
    complex_array_to_mpz(fft_result, n, recursive_fft_total_result);
    // Add correct sign back
    if (negative){
        mpz_t negative_value;
        mpz_init(negative_value);
        mpz_set_str(negative_value, "-1", 10);
        mpz_mul(recursive_fft_total_result[0],
                recursive_fft_total_result[0], negative_value);
        mpz_clear(negative_value);
    }

    return;
}
