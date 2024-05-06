#include "Recursive_fft.h"
#include "iterative_fft.h"
#include "dft.h"
#include "karatsuba.h"
#include "Naive_Polynomial_multiplication.h"
#include "test/WhiteBox_test.h"
#include "test/Runtime_test.h"
#include "Helper_Functions.h"

int main() {
    printf("Welcome to Polynomial test, these tests include, Naive, DFT, Karatsuba and FFT recursive and iterative\n");
    
    int input_number = 0;
    int n, m, iterations;
    while (1){
        printf("What do you want to test, write 1 for runtime test or 2 for unit test or 3 to exit\n");
        scanf("%d", &input_number);

        switch (input_number){
        case 1:
            printf("What size m do you want to test on, n = 2^m?\n");
            scanf("%d", &m);
            n = pow(2, m);
            printf("How many iterations?\n");
            scanf("%d", &iterations);
            Runtime_test(n, iterations);
            break;
        case 2:
            Test_Setup();
            break;
        case 3:
            exit(0);
            break;
        default:
            break;
        }
    }
    return 0;
}