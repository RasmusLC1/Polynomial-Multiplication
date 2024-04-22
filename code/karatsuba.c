#include "karatsuba.h"



int get_half_length(long long value){
   int count = 0;
   while (value > 0) {
      count++;
      value /= 10;
   }
   return count;
}

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



long long polynomial_multiply_karatsuba(complex double *a, complex double *b, int n){
    //Convert array to integer
    long long num1 = 0, num2 = 0;
    for (int i = 0; i < n; i++) {
        num1 += a[i] * pow(10, i);
        num2 += b[i] * pow(10, i);
    }
    long long result = karatsuba(num1, num2);


    // printf("karatsuba Computations:\t%d\n", total_computations);
    return result;
}

