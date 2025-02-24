#include "karatsuba_optimisation.h"

// Karatsuba multiplication for polynomials
void Karatsuba_Multiply_optimised(int *input1, int *input2, int naive_switch, int length_input1,
                            int length_input2, int *result) {
    
    // Check if either number is 2 digits, if yes then multiply.
    // C is really fast for small number multiplication, so it doesn't need to check for 1 digit
    if (length_input1 <= naive_switch || length_input2 <= naive_switch) { // Base case for the smallest size
        Array_Multiplication(input1, input2, length_input1,
                                length_input2, result);
        return;
    }
    // Calculate half length
    int half_length1 = (length_input1 + 1) >> 1; // Equivalent to ceil(length_input1 / 2)
    int half_length2 = (length_input2 + 1) >> 1; // Equivalent to ceil(length_input2 / 2)

    // Find the longest half length
    int half_length = (half_length1 > half_length2) ? half_length1 : half_length2;


    // Allocate memory
    int *low1 = calloc(half_length, sizeof(int));
    int *low2 = calloc(half_length, sizeof(int));
    int *high1 = calloc(half_length, sizeof(int));
    int *high2 = calloc(half_length, sizeof(int));
    int *result_low = calloc(length_input1 + length_input2 - 1, sizeof(int));
    int *result_high = calloc(length_input1 + length_input2 - 1, sizeof(int));
    int *result_middle = calloc(length_input1 + length_input2 - 1, sizeof(int));

    // Seperate the polynomials into highs and lows
    memcpy(low1, input1, half_length * sizeof(int));
    memcpy(low2, input2, half_length * sizeof(int));
    memcpy(high1, input1 + half_length,
            (length_input1 - half_length1) * sizeof(int));
    memcpy(high2, input2 + half_length,
            (length_input2 - half_length2) * sizeof(int));
    
    // First 2 recursive calls
    Karatsuba_Multiply_optimised(low1, low2, naive_switch, half_length, half_length, result_low);
    Karatsuba_Multiply_optimised(high1, high2, naive_switch, half_length, half_length, result_high);

    // Third recursive call
    // long long product_middle  = karatsuba(low1 + high1, low2 + high2);
    int *temp1 = calloc(half_length, sizeof(int));
    int *temp2 = calloc(half_length, sizeof(int));
    Array_Addition(low1, high1, half_length, temp1);
    Array_Addition(low2, high2, half_length, temp2);
    Karatsuba_Multiply_optimised(temp1, temp2, naive_switch, half_length, half_length, result_middle);

    // Calculate middle coefficients (result_middle = result_middle - result_low - result_high)
    Array_Subtraction(result_middle, result_low, length_input1 + length_input2
                        - 1, result_middle);
    Array_Subtraction(result_middle, result_high, length_input1 + length_input2
                        - 1, result_middle);

    // Assemble final result
    // result = result_low + (result_middle << half_length1) + (result_high << (half_length1 * 2))
    int max_length = length_input1 + length_input2 - 1;

    for (int i = 0; i < max_length; i++) {
        result[i] = result_low[i];  // Set result to low part

        // Add middle part if within its valid range
        if (i >= half_length) {
            result[i] += result_middle[i - half_length];
        }

        // Add high part if within its valid range
        if (i >= 2 * half_length) {
            result[i] += result_high[i - 2 * half_length];
        }
    }
    free(low1);
    free(low2);
    free(high1);
    free(high2);
    free(result_low);
    free(result_middle);
    free(result_high);
    free(temp1);
    free(temp2);
}

// Function to measure execution time of the Karatsuba function
double measure_karatsuba_time(int* a, int* b, int naive_switch, int length1, int length2, int* result) {
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    Karatsuba_Multiply_optimised(a, b, naive_switch, length1, length2, result);
    clock_gettime(CLOCK_MONOTONIC, &end);
    return (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1000000000.0;
}

void polynomial_multiply_karatsuba_optimisation() {
    mpz_t random_Value_a, random_Value_b;
    mpz_inits(random_Value_a, random_Value_b, NULL);

    // Seed the random state with current time
    gmp_randstate_t state;
    gmp_randinit_default(state);
    gmp_randseed_ui(state, time(NULL));
    int n = pow(2, 16);

    int min_naive, max_naive;
    int best_naive_switch;
    double lowest_time;
    int average_naive = 0;
    int iterations = 1000;
    for (int i = 0; i < iterations; i++){
        // Generate a random number with n bits
        mpz_urandomb(random_Value_a, state, n);
        mpz_urandomb(random_Value_b, state, n);

        // Check for negative numbers

        int padded_a[n], padded_b[n], karatsuba_result[n];

        memset(padded_a, 0, n * sizeof(int));
        memset(padded_b, 0, n * sizeof(int));
        memset(karatsuba_result, 0, n * sizeof(int));

        int length_input1 = mpz_to_int_array(random_Value_a, padded_a); // Assume correct implementation
        int length_input2 = mpz_to_int_array(random_Value_b, padded_b);

        min_naive = 1;
        max_naive = 1000;
        best_naive_switch = min_naive;
        lowest_time = 1000.0;
            
        while (min_naive <= max_naive) {
            int mid_naive = min_naive + (max_naive - min_naive) / 2;
            
            double current_time = measure_karatsuba_time(padded_a, padded_b, mid_naive, length_input1, length_input2, karatsuba_result);
            // Check for lowest time
            if (current_time < lowest_time) {
                lowest_time = current_time;
                best_naive_switch = mid_naive;
            }

            // Adjust search range
            if (measure_karatsuba_time(padded_a, padded_b, mid_naive - 1, length_input1, length_input2, karatsuba_result) < current_time) {
                max_naive = mid_naive - 1;
            } else if (measure_karatsuba_time(padded_a, padded_b, mid_naive + 1, length_input1, length_input2, karatsuba_result) < current_time) {
                min_naive = mid_naive + 1;
            } else {
                break; // Optimal value found
            }
        }
        average_naive += best_naive_switch;
        Loading_Screen(iterations, i);
    }

    printf("Best naive switch: %d\n", average_naive/iterations);
    printf("Lowest time: %f seconds\n", lowest_time);

    return;
}
