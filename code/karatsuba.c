#include "karatsuba.h"




// long long karatsuba(long long num1, long long num2){
//     // Check for base case if either number is single digit, then fastest way
//     // is to multiply like normal
//     if (num1 < 10 || num2 < 10){
//         return num1 * num2;    
//     }

//     // Calculates the half_length of the numbers
//     int half_length = fmax(get_half_length(num1), get_half_length(num2));

//     // Get half the half_length of the largest number and use modulo to get remainder for rounding
//     // This is the main idea of Karatsuba to split the numbers into halves
//     // >>1 = /2
//     half_length = (half_length >> 1) + (half_length % 2);

//     long long split_factor = pow(10, half_length);

//     long long high1 = num1 / split_factor;
//     long long high2 = num2 / split_factor;
//     long long low1 = num1 - (high1 * split_factor);
//     long long low2 = num2 - (high2 * split_factor);

//     // 3 recursive calls, which halfs the half_length each, this leads to:
//         // T(n) = 3T(n/2) + O(n)
//     // Here 3T(n/2) is the cost of the recursive calls and O(n) is the time to
//     // split and combine
//     // Using Master theorem the cost becomes O(n^{log_2^3}) since C=1 because f(n) = O(n) 
//     // So we use the first rule
//     long long product_low = karatsuba(low1, low2);
//     long long product_middle  = karatsuba(low1 + high1, low2 + high2);
//     long long product_high = karatsuba(high1, high2);

//     return ((product_high * pow(10, half_length << 1)) +
//             (product_middle - product_high - product_low) * split_factor )
//             + product_low;
// }


// Helper function to determine the number of digits
// Helper function to determine the number of digits
int num_digits(const mpz_t x) {
    char *str = mpz_get_str(NULL, 10, x);
    int len = strlen(str);
    free(str);
    return len;
}

// NOT WORKING
// Recursive Karatsuba multiplication
void karatsuba(mpz_t x, mpz_t y, mpz_t karatsuba_result) {
    // Base case: if either number is less than 10
    if (mpz_cmp_ui(x, 10) < 0 || mpz_cmp_ui(y, 10) < 0) {
        mpz_mul(karatsuba_result, x, y);
        return;
    }

    int m2 = num_digits(x) / 2;
    mpz_t high1, high2, low1, low2, z0, z1, z2, sum1, sum2;
    mpz_inits(high1, high2, low1, low2, z0, z1, z2, sum1, sum2, NULL);

    mpz_t base;
    mpz_init(base);
    mpz_ui_pow_ui(base, 10, m2);

    mpz_fdiv_q(high1, x, base);
    mpz_fdiv_r(low1, x, base);
    mpz_fdiv_q(high2, y, base);
    mpz_fdiv_r(low2, y, base);

    karatsuba(z0, low1, low2);
    karatsuba(z1, high1, high2);

    mpz_add(sum1, low1, high1);
    mpz_add(sum2, low2, high2);
    karatsuba(z2, sum1, sum2);

    mpz_sub(z2, z2, z0);
    mpz_sub(z2, z2, z1);

    mpz_mul(karatsuba_result, z1, base); // z1 * 10^(m2*2)
    mpz_mul(base, base, base);
    mpz_addmul(karatsuba_result, z2, base); // z2 * 10^m2
    mpz_add(karatsuba_result, karatsuba_result, z0); // add z0

    mpz_clears(high1, high2, low1, low2, z0, z1, z2, sum1, sum2, base, NULL);
}



void polynomial_multiply_karatsuba(mpz_t a, mpz_t b, mpz_t karatsuba_result){
       
    karatsuba(a, b, karatsuba_result);

    return;
}

