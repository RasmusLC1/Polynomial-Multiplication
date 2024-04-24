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

    // Final recursive call long long product_high = karatsuba(high1, high2);
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




void polynomial_multiply_karatsuba(mpz_t a, mpz_t b, mpz_t karatsuba_result){
       
    karatsuba(a, b, karatsuba_result);

    return;
}

