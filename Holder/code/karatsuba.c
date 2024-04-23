#include "karatsuba.h"




long long karatsuba(long long num1, long long num2){
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
    long long product_low = karatsuba(low1, low2);
    long long product_middle  = karatsuba(low1 + high1, low2 + high2);
    long long product_high = karatsuba(high1, high2);

    return ((product_high * pow(10, half_length << 1)) +
            (product_middle - product_high - product_low) * split_factor )
            + product_low;
}



long long polynomial_multiply_karatsuba(long a, long b, int n){
    
    bool negative = false;

    if (a < 0 && b >= 0){
        negative = true;
        a *= -1;
    } else if (b < 0 && a >= 0){
        negative = true;
        b *= -1;
    }
    
    long long karatsuba_total_result = karatsuba(a, b);

    if (negative){
        karatsuba_total_result *= -1;
    }

    // Adding empty array data handling to balance out the equations, since
    // The FFT algorithms have to do these for setup 

    complex double padded_a[n], padded_b[n], result[n];
    memset(padded_a, 0, n * sizeof(complex double));
    memset(padded_b, 0, n * sizeof(complex double));
    memset(result, 0, n * sizeof(complex double));
    
    Int_to_Array(a, padded_a);
    Int_to_Array(b, padded_b);
    // End of Filler
    

    return karatsuba_total_result;
}

