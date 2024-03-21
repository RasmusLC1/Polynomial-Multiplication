#include "karatsuba.h"
int total_computations;

long karatsuba(long num1, long num2){
    total_computations++;
    // Check for base case if either number is single digit
    if (num1 < 10 && num2 < 10){
        return num1 * num2;    
    }

    // Calculates the size of the numbers
    int size = fmax(get_size(num1), get_size(num2));

    // Get half the size of the largest number and use modulo to get remainder for rounding
    // This is the main idea of Karatsuba to split the numbers into halves
    // >>1 = /2
    size = (size >> 1) + (size % 2);

    long scaler = pow(10, size);

    long high1 = num1 / scaler, high2 = num2 / scaler;
    long low1 = num1 - (high1 * scaler), low2 = num2 - (high2 * scaler);

    // 3 recursive calls, which halfs the size each, this leads to:
        // T(n) = 3T(n/2) + O(n)
    // Here 3T(n/2) is the cost of the recursive calls and O(n) is the time to
    // split and combine
    // Using Master theorem the cost becomes O(n^{log_2^3}) since C=1 because f(n) = O(n) 
    // So we use the first rule
    long z0 = karatsuba(low1, low2);
    long z1 = karatsuba(low1 + high1, low2 + high2);
    long z2 = karatsuba(high1, high2);

    return ((z2 * pow(10, size * 2)) + (z1 - z2 - z0) * scaler ) + z0;
}

int get_size(long value){
   int count = 0;
   while (value > 0) {
      count++;
      value /= 10;
   }
   return count;
}

long polynomial_multiply_karatsuba(complex double *a, complex double *b, int n){
    total_computations = 0;
    //Setting up karatsuba test
    int num1 = 0, num2 = 0;
    for (int i = 0; i < n; i++) {
        num1 += a[i] * pow(10, i);
        num2 += b[i] * pow(10, i);
    }
    long result = karatsuba(num1, num2);


    // printf("karatsuba Computations:\t%d\n", total_computations);
    return result;
}

