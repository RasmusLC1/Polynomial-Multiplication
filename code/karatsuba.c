#include "karatsuba.h"


// NOT WORKING
// Recursive Karatsuba multiplication
void karatsuba(mpz_t num1, mpz_t num2, mpz_t karatsuba_result) {
    // Base case: if either number is small
    if (mpz_cmp_ui(num1, 10) < 0 || mpz_cmp_ui(num2, 10) < 0) {
        mpz_mul(karatsuba_result, num1, num2);
        return;
    }

    int half_length = fmax(get_half_length(num1), get_half_length(num2));
    half_length = (half_length + 1) / 2;  // Adjust half length to split correctly

    // Setting up variables
    mpz_t high1, high2, low1, low2, product_low, product_middle, product_high, temp, temp2;
    mpz_inits(high1, high2, low1, low2, product_low, product_middle, product_high, temp, temp2, NULL);

    // Get half the half_length of the largest number and use modulo to get remainder for rounding
    // This is the main idea of Karatsuba to split the numbers into halves
    // >>1 = /2
    mpz_t split_factor;
    mpz_init(split_factor);
    mpz_ui_pow_ui(split_factor, 10, half_length);

    // Splitting the numbers
    mpz_fdiv_q(high1, num1, split_factor);
    mpz_fdiv_r(low1, num1, split_factor);
    mpz_fdiv_q(high2, num2, split_factor);
    mpz_fdiv_r(low2, num2, split_factor);

    // 3 recursive calls, which halfs the half_length each, this leads to:
        // T(n) = 3T(n/2) + O(n)
    // Here 3T(n/2) is the cost of the recursive calls and O(n) is the time to
    // split and combine
    // Using Master theorem the cost becomes O(n^{log_2^3}) since C=1 because f(n) = O(n) 
    // So we use the first rule
    karatsuba(low1, low2, product_low);  
    karatsuba(high1, high2, product_high);

    // Final recursive call int product_high = karatsuba(high1, high2);
    mpz_add(temp, low1, high1);
 
    mpz_add(temp2, low2, high2);
    karatsuba(temp, temp2, product_middle); 

    // Calculate the final result
    mpz_sub(product_middle, product_middle, product_low);
    mpz_sub(product_middle, product_middle, product_high);
    mpz_ui_pow_ui(temp, 10, half_length);
    mpz_mul(product_middle, product_middle, temp);
    mpz_mul(product_high, product_high, temp);
    mpz_mul(product_high, product_high, temp);
    mpz_add(temp, product_low, product_middle);
    mpz_add(karatsuba_result, temp, product_high);

    // Clear memory
    mpz_clears(high1, high2, low1, low2, product_low, product_middle, product_high, temp, temp2, split_factor, NULL);
}

void add(int *a, int *b, int n) {
    for (int i = 0; i < n; i++) {
        a[i] += b[i];
    }
}

void subtract(int *a, int *b, int n) {
    for (int i = 0; i < n; i++) {
        a[i] -= b[i];
    }
}

// Helper functions
void Array_Addition(int *a, int *b, int length, int *result) {
    for (int i = 0; i < length; i++) {
        result[i] = a[i] + b[i];
    }
}

void Array_Subtraction(int *a, int *b, int length, int *result) {
    for (int i = 0; i < length; i++) {
        result[i] = a[i] - b[i];
    }
}

void Array_Multiplication(int *input1, int *input2, int length_input1, int length_input2, int *result) {
    memset(result, 0, (length_input1 + length_input2 - 1) * sizeof(int)); // Clearing result buffer
    for (int i = 0; i < length_input1; i++) {
        for (int j = 0; j < length_input2; j++) {
            result[i + j] += input1[i] * input2[j];
        }
    }
}

// Karatsuba multiplication for polynomials
void Karatsuba_Recursive(int *input1, int *input2, int length_input1, int length_input2, int *result) {
    if (length_input1 == 1 || length_input2 == 1) { // Base case for the smallest size
        Array_Multiplication(input1, input2, length_input1, length_input2, result);
        return;
    }

    int half_length1 = (length_input1 >> 1) + (length_input1 % 2);
    int half_length2 = (length_input2 >> 1) + (length_input2 % 2);

    int half_length;

    if (half_length1 >= half_length2) {
        half_length = half_length1;
    } else {
        half_length = half_length2;
    }

    int *low1 = calloc(half_length, sizeof(int));
    int *low2 = calloc(half_length, sizeof(int));
    int *high1 = calloc(half_length, sizeof(int));
    int *high2 = calloc(half_length, sizeof(int));
    int *result_low = calloc(length_input1 + length_input2 - 1, sizeof(int));
    int *result_high = calloc(length_input1 + length_input2 - 1, sizeof(int));
    int *result_middle = calloc(length_input1 + length_input2 - 1, sizeof(int));

    memcpy(low1, input1, half_length * sizeof(int));
    memcpy(low2, input2, half_length * sizeof(int));
    memcpy(high1, input1 + half_length, (length_input1 - half_length1) * sizeof(int));
    memcpy(high2, input2 + half_length, (length_input2 - half_length2) * sizeof(int));
    Karatsuba_Recursive(low1, low2, half_length, half_length, result_low);
    Karatsuba_Recursive(high1, high2, half_length, half_length, result_high);

    int *temp1 = calloc(half_length, sizeof(int));
    int *temp2 = calloc(half_length, sizeof(int));
    Array_Addition(low1, high1, half_length, temp1);
    Array_Addition(low2, high2, half_length, temp2);
    Karatsuba_Recursive(temp1, temp2, half_length, half_length, result_middle);

    // Calculate middle coefficients (result_middle = result_middle - result_low - result_high)
    Array_Subtraction(result_middle, result_low, length_input1 + length_input2 - 1, result_middle);
    Array_Subtraction(result_middle, result_high, length_input1 + length_input2 - 1, result_middle);

    // Assemble final result
    // result = result_low + (result_middle << half_length1) + (result_high << (half_length1 * 2))
    int max_length = length_input1 + length_input2 - 1;

for (int i = 0; i < max_length; i++) {
  result[i] = result_low[i];  // Set result to low part (avoid unnecessary comparison)

  // Add middle part if within its valid range (half_length1 <= i < max_length)
  if (i >= half_length) {
    result[i] += result_middle[i - half_length];
  }

  // Add high part if within its valid range (2 * half_length1 <= i < max_length)
  if (i >= 2 * half_length) {
    result[i] += result_high[i - 2 * half_length];
  }
}

    free(low1);
    free(low2);
    free(high1);
    free(high2);
    free(result_low);
    free(result_high);
    free(result_middle);
    free(temp1);
    free(temp2);
}


void polynomial_multiply_karatsuba(mpz_t a, mpz_t b, int n, mpz_t* karatsuba_total_result) {
    int padded_a[n], padded_b[n], karatsuba_result[n];

    memset(padded_a, 0, n * sizeof(int));
    memset(padded_b, 0, n * sizeof(int));
    memset(karatsuba_result, 0, n * sizeof(int));

    int length_input1 = mpz_to_int_array(a, padded_a); // Assume correct implementation
    int length_input2 = mpz_to_int_array(b, padded_b);


    Karatsuba_Recursive(padded_a, padded_b, length_input1, length_input2, karatsuba_result);

    // //Convert to the real number
    mpz_t temp, result, power;

    // The below for loop is calculating the following line using GMP
    // FFT_total_result += (long long)(creal(result[i])+0.5)*pow(10,i);
    for (int i = 0; i < n; i++) {
        mpz_inits(temp, result, power, NULL);
        // Calculate 10^i using GMP
        mpz_ui_pow_ui(power, 10, i);

        // Convert creal(result[i]) to nearest integer and multiply by 10^i
        mpz_set_d(temp, floor(creal(karatsuba_result[i]) + 0.5));
        mpz_mul(result, temp, power);

        // Add to the total result
        mpz_add(karatsuba_total_result, karatsuba_total_result, result);
        // Cleanup
        mpz_clears(temp, result, power, NULL);
   
    }
}
