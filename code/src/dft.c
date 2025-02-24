#include "dft.h"

void DFT(complex double *in, int n, complex double *out) {
    // 2 nested for loops is what causes the runtime n^2
    for (int i = 0; i < n; i++) { // For each output element
        // initialise each element to 0
        out[i] = 0;
        for (int j = 0; j < n; j++) { // For each input element
            // Compute DFT function
            out[i] += in[j] * cexp(-I * TAU * j * i / n);
        }
    }
}

void Python_Plotter(complex double *result, int n){
    char command[1024] = "python plot.py '";
    char number[1024];
    for (int i = 0; i < n; i++) {
        snprintf(number, sizeof(number), "%f%+fj,", creal(result[i]), cimag(result[i]));  
        strcat(command, number);
    }
    command[strlen(command) - 1] = '\'';  // Replace the last comma with a quote
    strcat(command, " &");  // Append '&' to run the plotting in the background
    system(command);
}

// Inverse DFT
void IDFT(complex double *in, int n, complex double *out) {

    // 2 nested for loops is what causes the runtime n^2
    for (int i = 0; i < n; i++) { // For each output element

        // initialise each element to 0
        out[i] = 0;
        
        for (int j = 0; j < n; j++) { // For each input element
            // Compute inverse DFT function by changing the sign
            // This is the only change from DFT
            out[i] += in[j] * cexp(I * TAU * j * i / n);
        }
        out[i] /= n; // Scale by 1/n, ensuring proper normalization
    }
    // Python_Plotter(out, n);
}


double polynomial_multiply_DFT(mpz_t a, mpz_t b, int n, int* dft_total_result) {
    
    // Pad the inputs with zeros, the polynomials are represented as arays
    // Padding ensures the data is clean
    // Arrays help structure the data into parts
    complex double padded_a[n], padded_b[n], dft_result[n];
    memset(padded_a, 0, n * sizeof(complex double));
    memset(padded_b, 0, n * sizeof(complex double));
    memset(dft_result, 0, n * sizeof(complex double));

    mpz_to_complex_array(a, padded_a);
    mpz_to_complex_array(b, padded_b);

    // // Apply DFT to both polynomials
    complex double fa[n], fb[n];
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    DFT(padded_a, n, fa);
    DFT(padded_b, n, fb);

    // // Point-wise multiply the DFTs
    for (int i = 0; i < n; i++) {
        fa[i] *= fb[i];
    }

    // // Apply IDFT to get the product polynomial
    IDFT(fa, n, dft_result);
    clock_gettime(CLOCK_MONOTONIC, &end);

    double elapsed_time = end.tv_sec - start.tv_sec + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
    
    // Perform the conversion from complex double to int by extracting the real part and rounding
    for (int i = 0; i < n; i++) {
        dft_total_result[i] = (int)round(creal(dft_result[i]));
    }

    return elapsed_time;
}