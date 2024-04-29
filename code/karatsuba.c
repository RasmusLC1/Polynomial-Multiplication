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


// Karatsuba multiplication for polynomials
void Karatsuba_Polynomial(int *input1, int *input2, int length_input1, int length_input2, int *result) {
    
    // Check if either number is 2 digits, if yes then multiply.
    // C is really fast for small number multiplication, so it doesn't need to check for 1 digit
    if (length_input1 <= 2 || length_input2 <= 2) { // Base case for the smallest size
        Array_Multiplication(input1, input2, length_input1, length_input2, result);
        return;
    }
    // Calculate half length
    int half_length1 = (length_input1 >> 1) + (length_input1 % 2);
    int half_length2 = (length_input2 >> 1) + (length_input2 % 2);

    // Find the longest number and set it to half length
    int half_length;
    if (half_length1 >= half_length2) {
        half_length = half_length1;
    } else {
        half_length = half_length2;
    }

    // Allocate memory
    int *low1 = calloc(half_length, sizeof(int));
    int *low2 = calloc(half_length, sizeof(int));
    int *high1 = calloc(half_length, sizeof(int));
    int *high2 = calloc(half_length, sizeof(int));
    int *result_low = calloc(length_input1 + length_input2 - 1, sizeof(int));
    int *result_high = calloc(length_input1 + length_input2 - 1, sizeof(int));
    int *result_middle = calloc(length_input1 + length_input2 - 1, sizeof(int));

    // Seperate the polynomials into highs and lows
    memcpy(low1, input1, half_length * sizeof(int));
    memcpy(low2, input2, half_length * sizeof(int));
    memcpy(high1, input1 + half_length, (length_input1 - half_length1) * sizeof(int));
    memcpy(high2, input2 + half_length, (length_input2 - half_length2) * sizeof(int));
    
    // First 2 recursive calls
    Karatsuba_Polynomial(low1, low2, half_length, half_length, result_low);
    Karatsuba_Polynomial(high1, high2, half_length, half_length, result_high);

    // Third recursive call
    // long long product_middle  = karatsuba(low1 + high1, low2 + high2);
    int *temp1 = calloc(half_length, sizeof(int));
    int *temp2 = calloc(half_length, sizeof(int));
    Array_Addition(low1, high1, half_length, temp1);
    Array_Addition(low2, high2, half_length, temp2);
    Karatsuba_Polynomial(temp1, temp2, half_length, half_length, result_middle);

    // Calculate middle coefficients (result_middle = result_middle - result_low - result_high)
    Array_Subtraction(result_middle, result_low, length_input1 + length_input2 - 1, result_middle);
    Array_Subtraction(result_middle, result_high, length_input1 + length_input2 - 1, result_middle);

    // Assemble final result
    // result = result_low + (result_middle << half_length1) + (result_high << (half_length1 * 2))
    int max_length = length_input1 + length_input2 - 1;

    for (int i = 0; i < max_length; i++) {
        result[i] = result_low[i];  // Set result to low part

        // Add middle part if within its valid range
        if (i >= half_length) {
            result[i] += result_middle[i - half_length];
        }

        // Add high part if within its valid range
        if (i >= 2 * half_length) {
            result[i] += result_high[i - 2 * half_length];
        }
    }

    free(low1);
    free(low2);
    free(high1);
    free(high2);
    free(result_low);
    free(result_middle);
    free(result_high);
    free(temp1);
    free(temp2);
}


void polynomial_multiply_karatsuba(mpz_t a, mpz_t b, int n, mpz_t* karatsuba_total_result) {
    
    // Check for negative numbers
    bool negative = false;
    mpz_t negative_value;
    // Negative check
    if (mpz_sgn(a) < 0 && mpz_sgn(b) >= 0){
        negative = true;
        mpz_init(negative_value);
        mpz_set_str(negative_value, "-1", 10);
        mpz_mul(a, a, negative_value);
    } else if (mpz_sgn(b) < 0 && mpz_sgn(a) >= 0){
        negative = true;
        mpz_init(negative_value);
        mpz_set_str(negative_value, "-1", 10);
        mpz_mul(b, b, negative_value);
    }
    
    int padded_a[n], padded_b[n], karatsuba_result[n];

    memset(padded_a, 0, n * sizeof(int));
    memset(padded_b, 0, n * sizeof(int));
    memset(karatsuba_result, 0, n * sizeof(int));

    int length_input1 = mpz_to_int_array(a, padded_a); // Assume correct implementation
    int length_input2 = mpz_to_int_array(b, padded_b);


    Karatsuba_Polynomial(padded_a, padded_b, length_input1, length_input2, karatsuba_result);

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

    // Add correct sign back
    if (negative){
        mpz_mul(karatsuba_total_result, karatsuba_total_result, negative_value);
        mpz_clear(negative_value);
    }

    return;
}
