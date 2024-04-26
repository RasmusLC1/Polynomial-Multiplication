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

void add(int *a, int *b, int n) {
    for (int i = 0; i < n; i++) {
        a[i] += b[i];
    }
}

void subtract(int *a, int *b, int n) {
    for (int i = 0; i < n; i++) {
        a[i] -= b[i];
    }
}

void Karatsuba_Recursive(int *input1, int *input2, int degree, int *result, int *temp_storage) {
    if (degree <= 8) {
        // Use naive multiplication for small degree
        for (int i = 0; i < degree; i++) {
            for (int j = 0; j < degree; j++) {
                result[i + j] += input1[i] * input2[j];
            }
        }
        return;
    }

    int mid = degree / 2;

    int *low1 = input1;
    int *high1 = input1 + mid;
    int *low2 = input2;
    int *high2 = input2 + mid;

    int *z0 = temp_storage;
    int *z1 = temp_storage + degree;
    int *z2 = temp_storage + 2 * degree;
    int *tmp = temp_storage + 3 * degree;

    Karatsuba_Recursive(low1, low2, mid, z0, temp_storage);
    Karatsuba_Recursive(high1, high2, degree - mid, z2, temp_storage);

    add(low1, high1, mid);
    add(low2, high2, mid);
    Karatsuba_Recursive(low1, low2, mid, z1, tmp);
    subtract(z1, z0, degree);
    subtract(z1, z2, degree);

    memcpy(result, z0, 2 * degree * sizeof(int));
    add(result + mid, z1, degree);
    add(result + degree, z2, degree);
}

void Karatsuba_Multiply(int *input1, int *input2, int degree, int *result) {
    int new_degree = 1;
    while (new_degree < degree) {
        new_degree <<= 1; // Find the next power of 2 greater than degree
    }

    int *allocated_memory = (int *)malloc(12 * new_degree * sizeof(int));
    memset(result, 0, 2 * new_degree * sizeof(int));

    Karatsuba_Recursive(input1, input2, new_degree, result, allocated_memory);

    free(allocated_memory);
}

void polynomial_multiply_karatsuba(mpz_t a, mpz_t b, int n, mpz_t karatsuba_total_result) {
    int *padded_a = calloc(n, sizeof(int));
    int *padded_b = calloc(n, sizeof(int));
    int *karatsuba_result = calloc(2 * n, sizeof(int));

    mpz_to_int_array(a, padded_a); // Assume correct implementation
    mpz_to_int_array(b, padded_b);

    Karatsuba_Multiply(padded_a, padded_b, n, karatsuba_result);

    mpz_set_ui(karatsuba_total_result, 0); // Initialize result
    mpz_t temp, power;
    mpz_inits(temp, power, NULL);

    for (int i = 0; i < 2 * n; i++) {
        if (karatsuba_result[i] != 0) {
            mpz_ui_pow_ui(power, 10, i);
            mpz_set_si(temp, karatsuba_result[i]);
            mpz_mul(temp, temp, power);
            mpz_add(karatsuba_total_result, karatsuba_total_result, temp);
        }
    }

    mpz_clears(temp, power, NULL);
    free(padded_a);
    free(padded_b);
    free(karatsuba_result);

    gmp_printf("a: %Zd\nb: %Zd\nkaratsuba_total_result: %Zd\n", a, b, karatsuba_total_result);
}
