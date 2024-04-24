#include "karatsuba.h"




long long karatsubaHolder(long long num1, long long num2){
    // Check for base case if either number is single digit, then fastest way
    // is to multiply like normal
    if (num1 < 10 || num2 < 10){
        return num1 * num2;    
    }

    // Calculates the half_length of the numbers
    int half_length = fmax(get_half_length(num1), get_half_length(num2));

    // Get half the half_length of the largest number and use modulo to get remainder for rounding
    // This is the main idea of Karatsuba to split the numbers into halves
    // >>1 = /2
    half_length = (half_length >> 1) + (half_length % 2);

    long long split_factor = pow(10, half_length);

    long long high1 = num1 / split_factor;
    long long high2 = num2 / split_factor;
    long long low1 = num1 - (high1 * split_factor);
    long long low2 = num2 - (high2 * split_factor);

    // 3 recursive calls, which halfs the half_length each, this leads to:
        // T(n) = 3T(n/2) + O(n)
    // Here 3T(n/2) is the cost of the recursive calls and O(n) is the time to
    // split and combine
    // Using Master theorem the cost becomes O(n^{log_2^3}) since C=1 because f(n) = O(n) 
    // So we use the first rule
    long long product_low = karatsubaHolder(low1, low2);
    long long product_middle  = karatsubaHolder(low1 + high1, low2 + high2);
    long long product_high = karatsubaHolder(high1, high2);

    return ((product_high * pow(10, half_length << 1)) +
            (product_middle - product_high - product_low) * split_factor )
            + product_low;
}

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

    // Variables for splitting numbers
    mpz_t high1, high2, low1, low2, z0, z1, z2, temp;
    mpz_inits(high1, high2, low1, low2, z0, z1, z2, temp, NULL);

    mpz_t split_factor;
    mpz_init(split_factor);
    mpz_ui_pow_ui(split_factor, 10, half_length);

    // Splitting the numbers
    mpz_fdiv_q(high1, num1, split_factor);
    mpz_fdiv_r(low1, num1, split_factor);
    mpz_fdiv_q(high2, num2, split_factor);
    mpz_fdiv_r(low2, num2, split_factor);

    // Recursively calculate z0, z1, and z2
    karatsuba(low1, low2, z0);  // z0 = low1 * low2
    karatsuba(high1, high2, z2);  // z2 = high1 * high2

    mpz_add(temp, low1, high1);
    mpz_t temp2;
    mpz_init(temp2);
    mpz_add(temp2, low2, high2);
    karatsuba(temp, temp2, z1);  // z1 = (low1 + high1) * (low2 + high2)

    // Calculate the final result
    mpz_sub(z1, z1, z0);
    mpz_sub(z1, z1, z2);
    mpz_ui_pow_ui(temp, 10, half_length);
    mpz_mul(z1, z1, temp);
    mpz_mul(z2, z2, temp);
    mpz_mul(z2, z2, temp);
    mpz_add(temp, z0, z1);
    mpz_add(karatsuba_result, temp, z2);

    // Clear memory
    mpz_clears(high1, high2, low1, low2, z0, z1, z2, temp, temp2, split_factor, NULL);
}

// Helper function to determine the number of digits
// Helper function to determine the number of digits
int num_digits(const mpz_t x) {
    char *str = mpz_get_str(NULL, 10, x);
    int len = strlen(str);
    free(str);
    return len;
}





void polynomial_multiply_karatsuba(mpz_t a, mpz_t b, mpz_t karatsuba_result){
       
    karatsuba(a, b, karatsuba_result);

    return;
}

