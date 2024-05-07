#include "Helper_Functions.h"


void mpz_to_complex_array(mpz_t input_int, complex double *output_array) {
    // Convert mpz_t to a string
    char *int_str = mpz_get_str(NULL, 10, input_int); // Base 10 representation
    int len = strlen(int_str);

    // Store digits in reverse order
    for (int i = 0; i < len; i++) {
        // Convert character to integer (digit)
        int digit = int_str[len - 1 - i] - '0'; // Reverse the index to store in reverse order
        output_array[i] = digit + 0.0 * I; // Store as complex double, imaginary part is 0
    }

    // Free the allocated string
    free(int_str);
}

int mpz_to_int_array(mpz_t input_int, int *output_array) {
    // Convert mpz_t to a string
    char *int_str = mpz_get_str(NULL, 10, input_int); // Base 10 representation
    int len = strlen(int_str);
    int i;
    // Store digits in reverse order
    for (i = 0; i < len; i++) {
        // Convert character to integer (digit)
        int digit = int_str[len - 1 - i] - '0'; // Reverse the index to store in reverse order
        output_array[i] = digit; // Store as complex double, imaginary part is 0
    }

    // Free the allocated string
    free(int_str);
    return i;
}


void Int_to_Array(long long input_int, complex double *output_array){
    int i = 0;
    while (input_int > 0) {
        output_array[i++] = input_int % 10; // Store the last digit in the array
        input_int /= 10;             // Remove the last digit from n
    }
}



void Loading_Screen(int iteration, int current_Iteration) {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);  // Get terminal window size
    // Check for division with 0
    if (current_Iteration > 0) {
        double iteration_percent = (double)current_Iteration /
                                    (double)iteration * 100;
        if (iteration_percent == floor(iteration_percent)) {
            int window_Left = w.ws_col -iteration_percent + 30; // Get the remaining window size

            // Ensure buffer size does not exceed terminal width
            int buffer_size = iteration_percent + 1;
            if (buffer_size > window_Left ) {  
                buffer_size = window_Left;
            }

            // Setting up the + buffer for smooth writing
            char buffer[buffer_size];
            memset(buffer, '+', buffer_size - 1);
            buffer[buffer_size - 1] = '\0';

            // Write to terminal and overwrite previous with \r
            printf("\rIterations completed: %d%%: ", (int)iteration_percent);  
            fwrite(buffer, sizeof(char), strlen(buffer), stdout);
            fflush(stdout);
        }
    }
    return;
}


// Check to see if results are identical
bool Correctness_Check(mpz_t result1, mpz_t result2) {
    if (mpz_cmp(result1, result2)){
        return false;
    }
    return true; 
}

// Utility function for reversing the bits
// of given index x
unsigned int Bit_Reverse(unsigned int x, int log2n) {
    int n = 0;
    for (int i = 0; i < log2n; i++) {
        n <<= 1; // Shift n one left (n *= 2)
        // (x & 1) finds the least signifcation bit of x, if that bit is 1, then it evaluates to 1
        // else 0.
        // n |= sets n to 1 if (x & 1) returns 1. 1 = true and 0 = false, in logic
        // false or true = true, the rest of the outcomes won't affect it:
        // t | t = t, t | f = t, f | t = t, f | f = f
        n |= (x & 1); 
        x >>= 1; // shift x one right (x /= 2)
    }
    return n;
}

int get_half_length(mpz_t num) {
    char num_str[mpz_sizeinbase(num, 10) + 2];  // Ensure enough space for '\0'
    mpz_get_str(num_str, 10, num);  // Convert number to string base 10
    return strlen(num_str) / 2;  // Half the length of the number in digits
}

// Helper functions
void Array_Addition(int *a, int *b, int length, int *result) {
    for (int i = 0; i < length; i++) {
        result[i] = a[i] + b[i];
    }
}

void Array_Subtraction(int *a, int *b, int length, int *result) {
    for (int i = 0; i < length; i++) {
        result[i] = a[i] - b[i];
    }
}

void Array_Multiplication(int *input1, int *input2, int length_input1,
                            int length_input2, int *result) {
    memset(result, 0, (length_input1 + length_input2 - 1) * sizeof(int)); // Clearing result buffer
    for (int i = 0; i < length_input1; i++) {
        for (int j = 0; j < length_input2; j++) {
            result[i + j] += input1[i] * input2[j];
        }
    }
}