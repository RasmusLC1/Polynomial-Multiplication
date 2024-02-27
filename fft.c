#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define PI 3.141592653589793238462
#define TAU 6.28318530717958647692 // 2 PI
#define EPSILON 1e-6 // Tolerance for comparison, increasing it further causes floating point errors

// Base case
//1  if n = 1 then
//2      return f (1)
// Collect the even (f0) degree terms and odd (f1) degree terms of f to write it as
//3  f = f0(x2) + x f1(x2).
// // Observe that ω2 is a principal (n~2)-th root of of unity.
//4 Recursively compute FFT( f0, ω2) and FFT( f1, ω2).
//5  for i = 0, ⋯, n − 1 do
//6      k = 2i mod n~2
//7      // This is to ensure that 0 ≤ k < n~2, and also note that k will be f0.
//8      Let β = f0(ωk) and γ = f1(ωk), which were computed earlier.
//9      Store the value f (ωi) = β + γωi.
//10      return  f (1), . . . , f (ωn−1).

int fft_computations = 0;
int dft_computations = 0;

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
    complex double *f0 = (complex double *)malloc(n_half * sizeof(complex double));
    complex double *f1 = (complex double *)malloc(n_half * sizeof(complex double));
    complex double *out_f0 = (complex double *)malloc(n_half * sizeof(complex double));
    complex double *out_f1 = (complex double *)malloc(n_half * sizeof(complex double));

    // Divide into even (f0) and odd (f1)
    for (int i = 0; i < n_half; i++) {
        fft_computations++;
        f0[i] = f[2 * i];
        f1[i] = f[2 * i + 1];
    }

    // Recursively call each half
    FFT(f0, n_half, out_f0);
    FFT(f1, n_half, out_f1);

    // Compute the FFT output
    complex double temp = 0;
    for (int k = 0; k < n_half; k++) {
        // Use defined TAU to save multiplication and calculate e^{−i*TAU*n/k​}
        // directly to save calculations
        temp = cexp(- I * TAU * k / n) * out_f1[k]; 
        out[k] = out_f0[k] + temp; // Assign left half of return array
        out[k + n_half] = out_f0[k] - temp; // Assign right half of return array
        fft_computations++;

    }

    // Free allocated memory
    free(f0);
    free(f1);
    free(out_f0);
    free(out_f1);
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
    complex double *f0 = (complex double *)malloc(n_half * sizeof(complex double));
    complex double *f1 = (complex double *)malloc(n_half * sizeof(complex double));
    complex double *out_f0 = (complex double *)malloc(n_half * sizeof(complex double));
    complex double *out_f1 = (complex double *)malloc(n_half * sizeof(complex double));
    
    // Divide into even (f0) and odd (f1)
    for (int i = 0; i < n_half; i++) {
        fft_computations++;

        f0[i] = f[2 * i];
        f1[i] = f[2 * i + 1];
    }

    // Recursively call each half
    IFFT(f0, n_half, out_f0);
    IFFT(f1, n_half, out_f1);

    // Compute the FFT output
    for (int k = 0; k < n_half; k++) {
        // Use defined TAU to save multiplication and calculate e^{−i*TAU*n/k​}
        // directly to save calculations
        // The only change from FFT is the sign in the exponent
        fft_computations++;

        complex double t = cexp(I * TAU * k / n) * out_f1[k];
        out[k] = out_f0[k] + t;
        out[k + n_half] = out_f0[k] - t;
    }

    //Free allocated memory
    free(f0);
    free(f1);
    free(out_f0);
    free(out_f1);

}

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


void polynomial_multiply_DFT(complex double *a, complex double *b, int n, complex double *result) {
    
    // Pad the inputs with zeros, the polynomials are represented as arays
    complex double padded_a[n], padded_b[n];
    memset(padded_a, 0, n * sizeof(complex double));
    memset(padded_b, 0, n * sizeof(complex double));
    
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
}


void polynomial_multiply_FFT(complex double* a, complex double* b, int n, complex double* result) {
    

    // Pad the inputs with zeros, the polynomials are represented as arays
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

    // Point-wise multiply the FFTs
    for (int i = 0; i < n; i++) {
        fa[i] *= fb[i];
    }

    // Apply IFFT to get the product polynomial
    IFFT(fa, n, result);

    // Call IFFT normalisation outside the recursive loop to prf0t
    // multiple normalisations
    for (int i = 0; i < n; i++) {
        result[i] /= n;
    }
}

// Check to see if results are identical
bool complex_array_equal(complex double *result_dft, complex double *result_fft, int n) {
    for (int i = 0; i < n; i++) {
        if (cabs(result_dft[i] - result_fft[i]) > EPSILON) {
            return false; // Arrays are not equal
        }
    }
    return true; // Arrays are equal
}

void FFT_DFT_Correctness(complex double* a, complex double* b, int n,
                        complex double* result_dft, complex double* result_fft){
    // Perform polynomial multiplication using DFT and FFT
    polynomial_multiply_DFT(a, b, n, result_dft);
    polynomial_multiply_FFT(a, b, n, result_fft);
    int sum_dft = 0;
    int sum_fft = 0;

    // Modify n so we only print the first 4 values
    int print_loops = n;
    if ( n > 4){
        print_loops = 4;
    }
    // Print the first 4 values
    for (int i = 0; i < print_loops; i++) {
        printf("DFT[%d] = %.2f + %.2fi\n", i, creal(result_dft[i]), cimag(result_dft[i]));
        printf("FFT[%d] = %.2f + %.2fi\n", i, creal(result_fft[i]), cimag(result_fft[i]));
        sum_dft += result_dft[i];
        sum_fft += result_fft[i];
    }
    // Print the sum of the first 4 values
    printf("DFT computations: %i\n", dft_computations);
    printf("FFT computations: %i\n", fft_computations);


    // Check if the results from DFT and FFT are the same
    if (complex_array_equal(result_dft, result_fft, n)) {
        printf("DFT and FFT results match.\n");
    } else {
        // Exit code if it does not match
        printf("DFT and FFT results do not match.\n");
        exit(1);
    }
}



void Polynomial_Multiply(int n, int iterations) {
    complex double a[n], b[n], result_dft[n], result_fft[n];
    
    // Seed randomiser with time
    srand(time(NULL));

    // Check if the seed works and we get true random variables
    assert(rand() != rand());
    int randomValue = 0;

    // Initialize a and b with random values
    for (int i = 0; i < n; i++) {
        // set a fixed random variable so both a and b have the same test 
        randomValue = rand() % 100;
        a[i] = randomValue;
        b[i] = randomValue;
    }

    // Verify with first iteration that the results are identical for both algorithms
    FFT_DFT_Correctness(a, b, n, result_dft, result_fft);

    // Set up timers
    double time_fft = 0.0, time_dft = 0.0;

    // Loop through the test multiple times to allow bigger tests
    // Also allows us to test n size vs iterations and their effect
    for (int i = 0; i < iterations; i++) {
        // Time DFT
        clock_t start_dft = clock();
        polynomial_multiply_DFT(a, b, n, result_dft); 
        clock_t end_dft = clock();
        time_dft += (double)(end_dft - start_dft) / CLOCKS_PER_SEC;

        // Time FFT
        clock_t start_fft = clock();
        polynomial_multiply_FFT(a, b, n, result_fft);
        clock_t end_fft = clock();
        time_fft += (double)(end_fft - start_fft) / CLOCKS_PER_SEC;
    }
    // Output time
    printf("FFT multiplication time:  %f seconds.\n", time_fft);
    printf("DFT multiplication time: %f seconds.\n", time_dft);
}


int main() {
    int n = 2048; // test size needs to be power 2
    Polynomial_Multiply(n, 10);
    return 0;
}