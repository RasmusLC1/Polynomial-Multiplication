#ifndef karatsuba_H
#define karatsuba_H
#include "Helper_Functions.h"

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

void polynomial_multiply_karatsuba(mpz_t a, mpz_t b, int n, mpz_t* karatsuba_total_result);

#endif

// PROOF 'OF CORRECTNESS FOR REPORT

// \section*{Proof of Correctness for Karatsuba's Algorithm}

// Karatsuba's algorithm splits two \( n \)-digit integers \( x \) and \( y \) into parts, performs recursive multiplications, and then combines the results. We will demonstrate that the algorithm correctly computes the product of two large integers.

// \subsection*{Karatsuba's Algorithm}

// For two \( n \)-digit integers \( x \) and \( y \):
// \begin{enumerate}
//     \item Split \( x \) and \( y \) into two halves each:
//     \[
//     x = x_1 \cdot B^m + x_0 \quad \text{and} \quad y = y_1 \cdot B^m + y_0
//     \]
//     where \( B \) is the base (typically 10), \( m = \left\lceil \frac{n}{2} \right\rceil \), and \( x_1, x_0, y_1, y_0 \) are the higher and lower halves of \( x \) and \( y \).

//     \item Compute the products:
//     \[
//     z_0 = x_0 \cdot y_0
//     \]
//     \[
//     z_2 = x_1 \cdot y_1
//     \]
//     \[
//     z_1 = (x_1 + x_0) \cdot (y_1 + y_0) - z_2 - z_0
//     \]

//     \item Combine the results:
//     \[
//     xy = z_2 \cdot B^{2m} + z_1 \cdot B^m + z_0
//     \]
// \end{enumerate}

// \subsection*{Proof of Correctness}

// To prove the correctness of Karatsuba's algorithm, we need to show that the final result of the algorithm matches the mathematical product of \( x \) and \( y \).

// \subsubsection*{1. Splitting Step}

// By definition, the split of \( x \) and \( y \) is:
// \[
// x = x_1 \cdot B^m + x_0
// \]
// \[
// y = y_1 \cdot B^m + y_0
// \]

// This step is trivially correct by the definition of digit splitting in positional notation.

// \subsubsection*{2. Intermediate Products}

// We compute three intermediate products:
// \[
// z_0 = x_0 \cdot y_0
// \]
// \[
// z_2 = x_1 \cdot y_1
// \]
// \[
// z_1 = (x_1 + x_0) \cdot (y_1 + y_0) - z_2 - z_0
// \]

// \subsubsection*{3. Combining the Results}

// The key step is to show that combining these intermediate products results in the correct product \( xy \).

// Consider:
// \[
// xy = (x_1 \cdot B^m + x_0) \cdot (y_1 \cdot B^m + y_0)
// \]
// Expanding this:
// \[
// xy = x_1 y_1 \cdot B^{2m} + x_1 y_0 \cdot B^m + x_0 y_1 \cdot B^m + x_0 y_0
// \]

// Now, let's relate this to the intermediate products:

// - \( z_2 = x_1 \cdot y_1 \)
// - \( z_0 = x_0 \cdot y_0 \)

// Next, consider the term \( (x_1 + x_0) \cdot (y_1 + y_0) \):
// \[
// (x_1 + x_0) \cdot (y_1 + y_0) = x_1 y_1 + x_1 y_0 + x_0 y_1 + x_0 y_0
// \]
// Therefore:
// \[
// z_1 = (x_1 + x_0) \cdot (y_1 + y_0) - z_2 - z_0 = x_1 y_0 + x_0 y_1
// \]

// Thus, the product can be written as:
// \[
// xy = z_2 \cdot B^{2m} + z_1 \cdot B^m + z_0
// \]

// This matches the expanded form of \( xy \):
// \[
// xy = x_1 y_1 \cdot B^{2m} + (x_1 y_0 + x_0 y_1) \cdot B^m + x_0 y_0
// \]

// Hence, combining \( z_2 \), \( z_1 \), and \( z_0 \) as per the algorithm's steps yields the correct product \( xy \).

// \subsection*{Conclusion}

// Karatsuba's algorithm correctly computes the product of two integers by breaking the problem into smaller parts, solving the subproblems recursively, and then combining the results using a mathematically sound method. The proof shows that each step maintains the correctness of the final product, thus demonstrating the overall correctness of the algorithm.
// '