#include "WhiteBox_test.h"

// Global variables
mpz_t global_a_value;
mpz_t global_b_value;
mpz_t global_expected_result;
int n;


START_TEST(DFT_test_basic_multiplication) {

    mpz_t result_dft;
    mpz_init(result_dft);
    polynomial_multiply_DFT(global_a_value, global_b_value, n, &result_dft); 
    if (!Correctness_Check(result_dft, global_expected_result)) {
        gmp_printf("DFT result was %Zd, expected %Zd\n", result_dft, global_expected_result);
        ck_abort_msg("DFT did not produce the expected result.");
    }
}
END_TEST

START_TEST(Karatsuba_test_basic_multiplication) {
    // Compute polynomial multiplication using DFT
    mpz_t result_karatsuba;
    mpz_init(result_karatsuba);
    polynomial_multiply_karatsuba(global_a_value, global_b_value, n, &result_karatsuba); 
    if (!Correctness_Check(result_karatsuba, global_expected_result)) {
        gmp_printf("Karatsuba result was %Zd, expected %Zd\n", result_karatsuba, global_expected_result);
        ck_abort_msg("Karatsuba did not produce the expected result.");
    }
}
END_TEST

START_TEST(Recursive_FFT_test_basic_multiplication) {
    

    mpz_t result_Recursive_FFT;
    mpz_init(result_Recursive_FFT);
    polynomial_multiply_Recursive_FFT(global_a_value, global_b_value, n, &result_Recursive_FFT); 
    if (!Correctness_Check(result_Recursive_FFT, global_expected_result)) {
        gmp_printf("Recursive FFT result was %Zd, expected %Zd\n", result_Recursive_FFT, global_expected_result);
        ck_abort_msg("Recursive FFT did not produce the expected result.");
    }
}
END_TEST

START_TEST(Iterative_FFT_test_basic_multiplication) {
    // Compute polynomial multiplication using DFT
    mpz_t result_Iterative_FFT;
    mpz_init(result_Iterative_FFT);
    polynomial_multiply_iterative_FFT(global_a_value, global_b_value, n, &result_Iterative_FFT); 
    if (!Correctness_Check(result_Iterative_FFT, global_expected_result)) {
        gmp_printf("Iterative FFT result was %Zd, expected %Zd\n", result_Iterative_FFT, global_expected_result);
        ck_abort_msg("Iterative FFT did not produce the expected result.");
    }
}
END_TEST

void Call_Test(TCase *Case){
    tcase_add_test(Case, DFT_test_basic_multiplication);
    tcase_add_test(Case, Karatsuba_test_basic_multiplication);
    tcase_add_test(Case, Recursive_FFT_test_basic_multiplication);
    tcase_add_test(Case, Iterative_FFT_test_basic_multiplication);
}


void add_basic_multiplication_tests(TCase *tc_basic) {
    // Basic multiplication tests except zero
    n = 8;
    char num_str_i[n];
    char num_str_j[n];
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            snprintf(num_str_i, sizeof(num_str_i), "%d", i);  
            snprintf(num_str_j, sizeof(num_str_j), "%d", j);
            mpz_set_str(global_a_value, num_str_i, 10);   
            mpz_set_str(global_b_value, num_str_j, 10); 
            mpz_mul(global_expected_result, global_a_value, global_b_value);  
            Call_Test(tc_basic);
        }
    }
}


Suite* basic_math_suite(void) {
    Suite *s = suite_create("BasicMathSuite");
    
    // Create test case for basic multiplication tests
    TCase *tc_basic = tcase_create("BasicMultiplication");
    add_basic_multiplication_tests(tc_basic);
    suite_add_tcase(s, tc_basic);
    return s;
}


void Basic_Math_Setup(){
    SRunner *sr = srunner_create(basic_math_suite());
    srunner_run_all(sr, CK_NORMAL);
    srunner_free(sr);
}

void zero_multiplication_tests(TCase *tc_zero) {
    // Zero handling tests
    mpz_set_str(global_a_value, "0", 10);
    mpz_set_str(global_b_value, "123", 10);
    mpz_mul(global_expected_result, global_a_value, global_b_value);
    Call_Test(tc_zero);
}


Suite* Zero_test_suite(void) {
    n = 8;

    Suite *s = suite_create("ZeroSuite");
    
   // Create test case for zero multiplication tests
    TCase *tc_zero = tcase_create("ZeroHandling");
    zero_multiplication_tests(tc_zero);
    suite_add_tcase(s, tc_zero);
    return s;
}


void Zero_Setup(){
    SRunner *sr = srunner_create(Zero_test_suite());
    srunner_run_all(sr, CK_NORMAL);
    srunner_free(sr);
}


void Large_Numbers_tests(TCase *tc_large) {

    // Seed the random state with current time
    gmp_randstate_t state;
    gmp_randinit_default(state);
    gmp_randseed_ui(state, time(NULL));
    n = 1024;
    
    
    for (int i = 0; i < 10; i++) {
        // Generate a random number with n bits
        mpz_urandomb(global_a_value, state, n);
        mpz_urandomb(global_b_value, state, n);
        mpz_mul(global_expected_result, global_a_value, global_b_value);
        Call_Test(tc_large);

        // Cleanup
        mpz_clears(global_a_value, global_b_value, global_expected_result, NULL);
        mpz_inits(global_a_value, global_b_value, global_expected_result, NULL);
        
    }
}


Suite* Large_Numbers_Tests_Suite(void) {
    Suite *s = suite_create("Large Numbers Suite");
    
   // Create test case for zero multiplication tests
    TCase *tc_large = tcase_create("LargeNumbersHandling");
    Large_Numbers_tests(tc_large);
    suite_add_tcase(s, tc_large);
    return s;
}


void Large_Numbers_test_Setup(){
    SRunner *sr = srunner_create(Large_Numbers_Tests_Suite());
    srunner_run_all(sr, CK_NORMAL);
    srunner_free(sr);
}

void Negative_Tests(TCase *tc_negative) {
    n = 8;
    mpz_set_str(global_a_value, "-5", 10);
    mpz_set_str(global_b_value, "5", 10);
    mpz_mul(global_expected_result, global_a_value, global_b_value);
    Call_Test(tc_negative);
}


Suite* Negative_Test_suite(void) {
    Suite *s = suite_create("NegativeSuite");
    
   // Create test case for zero multiplication tests
    TCase *tc_negative = tcase_create("NegativeHandling");
    Negative_Tests(tc_negative);
    suite_add_tcase(s, tc_negative);
    return s;
}


void Negative_Setup(){
    SRunner *sr = srunner_create(Negative_Test_suite());
    srunner_run_all(sr, CK_NORMAL);
    srunner_free(sr);
}


void Even_Polynomial_Test(TCase *tc_even) {
    n = 16;
    char num_str[n];
    int test_size = 40000;
    for (int i = test_size; i < test_size + 100; i++) {
        snprintf(num_str, sizeof(num_str), "%d", i);
        mpz_set_str(global_a_value, num_str, 10);
        mpz_set_str(global_b_value, num_str, 10); 
        mpz_mul(global_expected_result, global_a_value, global_b_value);
        Call_Test(tc_even);

        // Cleanup
        mpz_clears(global_a_value, global_b_value, global_expected_result, NULL);
        mpz_inits(global_a_value, global_b_value, global_expected_result, NULL);
        
    } 
}


Suite* Even_Polynomial_Test_suite(void) {
    Suite *s = suite_create("evenSuite");
    
   // Create test case for zero multiplication tests
    TCase *tc_even = tcase_create("EvenPolynomialHandling");
    Even_Polynomial_Test(tc_even);
    suite_add_tcase(s, tc_even);
    return s;
}


void Even_Polynomial_Setup(){
    SRunner *sr = srunner_create(Even_Polynomial_Test_suite());
    srunner_run_all(sr, CK_NORMAL);
    srunner_free(sr);
}


void Uneven_Polynomial_Test(TCase *tc_uneven) {
    n = 16;
    char num_str[n];
    int test_size = 40000;
    for (int i = test_size; i < test_size + 100; i++) {
        snprintf(num_str, sizeof(num_str), "%d", i);
        mpz_set_str(global_a_value, num_str, 10);
        mpz_set_str(global_b_value, num_str, 10); 
        mpz_mul(global_expected_result, global_a_value, global_b_value);
        Call_Test(tc_uneven);

        // Cleanup
        mpz_clears(global_a_value, global_b_value, global_expected_result, NULL);
        mpz_inits(global_a_value, global_b_value, global_expected_result, NULL);
    } 
}


Suite* Uneven_Polynomial_Test_suite(void) {
    Suite *s = suite_create("UnevenSuite");
    
   // Create test case for zero multiplication tests
    TCase *tc_uneven = tcase_create("UnevenPolynomialHandling");
    Uneven_Polynomial_Test(tc_uneven);
    suite_add_tcase(s, tc_uneven);
    return s;
}


void Uneven_Polynomial_Setup(){
    SRunner *sr = srunner_create(Uneven_Polynomial_Test_suite());
    srunner_run_all(sr, CK_NORMAL);
    srunner_free(sr);
}



void Test_Setup(){
    mpz_inits(global_a_value, global_b_value, global_expected_result, NULL);
    Basic_Math_Setup();
    mpz_clears(global_a_value, global_b_value, global_expected_result, NULL);
    mpz_inits(global_a_value, global_b_value, global_expected_result, NULL);
    Zero_Setup();
    mpz_clears(global_a_value, global_b_value, global_expected_result, NULL);
    mpz_inits(global_a_value, global_b_value, global_expected_result, NULL);
    Large_Numbers_test_Setup();
    mpz_clears(global_a_value, global_b_value, global_expected_result, NULL);
    mpz_inits(global_a_value, global_b_value, global_expected_result, NULL);
    Negative_Setup();
    mpz_clears(global_a_value, global_b_value, global_expected_result, NULL);
    mpz_inits(global_a_value, global_b_value, global_expected_result, NULL);
    Even_Polynomial_Setup();
    mpz_clears(global_a_value, global_b_value, global_expected_result, NULL);
    mpz_inits(global_a_value, global_b_value, global_expected_result, NULL);
    Uneven_Polynomial_Setup();
    mpz_clears(global_a_value, global_b_value, global_expected_result, NULL);


}