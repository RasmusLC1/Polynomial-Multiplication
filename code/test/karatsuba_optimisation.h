#ifndef karatsuba_optimisation_H
#define karatsuba_optimisation_H
#include "../src/Helper_Functions.h"
#include "../src/karatsuba.h"
#include "../src/Naive_Polynomial_Multiplication.h"

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

void Karatsuba_Multiply_optimised(int *input1, int *input2, int naive_switch, int length_input1,
                            int length_input2, int *result);

double measure_karatsuba_time(int* a, int* b, int naive_switch, int length1, int length2, int* result);

void polynomial_multiply_karatsuba_optimisation();

#endif
