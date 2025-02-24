#include "recursive_fft.h"
#include "iterative_fft.h"
#include "dft.h"
#include "karatsuba.h"
#include "Naive_Polynomial_multiplication.h"
#include "../test/WhiteBox_test.h"
#include "../test/Runtime_test.h"
#include "../test/karatsuba_optimisation.h"
#include "../test/Runtime_test_systematic.h"
#include "Helper_Functions.h"


int main() {
    printf("Welcome to Polynomial test, these tests include, Naive, DFT, Karatsuba and FFT recursive and iterative\n");
    
    int input_number, n, m, iterations;
    while (1){
        printf("What do you want to test, write 1 for runtime test or 2 for unit test or 3 to compare times, 4 to test optimal karatsuba value, 5 to exit\n");
        
        if (scanf("%d", &input_number) != 1) {
            fprintf(stderr, "Error reading input for input_number\n");
            return 1;
        }

        switch (input_number){
        case 1:
            printf("What size m do you want to test on, n = 2^m?\n");

            if (scanf("%d", &m) != 1) {
                fprintf(stderr, "Error reading input for m\n");
                return 1;  
            }

            if (m > 16){
                printf("Choose a number smaller than 17");
            }
            n = pow(2, m);
            printf("n has been set to:\t %d\n", n);
            printf("How many iterations?\n");

            if (scanf("%d", &iterations) != 1) {
                fprintf(stderr, "Error reading input for iterations\n");
                return 1; 
            }

            Runtime_test(n, iterations);
            break;
        case 2:
            Test_Setup();
            break;
        case 3:
            Runtime_test_systematic();
            break;
        case 4:
            polynomial_multiply_karatsuba_optimisation();
            break;
        case 5:
            exit(0);
        default:
            break;
        }
    }

    return 0;
}