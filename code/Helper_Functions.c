#include "Helper_Functions.h"

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
        double iteration_percent = (double)current_Iteration / (double)iteration * 100;
        if (iteration_percent == floor(iteration_percent)) {
            int window_Left = w.ws_col -iteration_percent + 25; // Get the remaining window size

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
            printf("\riteration_percent: %f %%", iteration_percent);  
            fwrite(buffer, sizeof(char), strlen(buffer), stdout);
            fflush(stdout);
        }
    }
    return;
}


// Check to see if results are identical
bool Correctness_Check(long long result1, long long result2) {
    if (result1 != result2){
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

int get_half_length(long long value){
   int count = 0;
   while (value > 0) {
      count++;
      value /= 10;
   }
   return count;
}