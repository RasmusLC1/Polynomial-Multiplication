#ifndef karatsuba_H
#define karatsuba_H
#include "Helper_Functions.h"
#include "Naive_Polynomial_Multiplication.h"

//PseudoCode from Wiki

// function karatsuba(num1, num2)
//     if (num1 < 10 or num2 < 10)
//         return num1 × num2 /* fall back to traditional multiplication */
    
//     /* Calculates the size of the numbers. */
//     m = max(size_base10(num1), size_base10(num2))
//     m2 = floor(m / 2) 
//     /* m2 = ceil (m / 2) will also work */
    
//     /* Split the digit sequences in the middle. */
//     high1, low1 = split_at(num1, m2)
//     high2, low2 = split_at(num2, m2)
    
//     /* 3 recursive calls made to numbers approximately half the size. */
//     z0 = karatsuba(low1, low2)
//     z2 = karatsuba(high1, high2)
//     z1 = karatsuba(low1 + high1, low2 + high2)

//     Combine the results with appropriate positional shifts
//     return (z2 × 10 ^ (m2 × 2)) + ((z1 - z2 - z0) × 10 ^ m2) + z0

void karatsuba(mpz_t num1, mpz_t num2, mpz_t karatsuba_result);


// void Karatsuba_Recursive(int *input1, int *input2, int degree, int *result, int *temp_storage) ;

void Karatsuba_Multiply(int *input1, int *input2, int degree, int *result);

double polynomial_multiply_karatsuba(mpz_t a, mpz_t b, int n,
                                    int* karatsuba_total_result) ;
#endif