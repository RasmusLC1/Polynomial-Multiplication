#include "WhiteBox_test.h"

// Global variables
mpz_t global_a_value;
mpz_t global_b_value;
mpz_t global_expected_result;


START_TEST(DFT_test_basic_multiplication) {
    int n = 16; // test size needs to be power 2

    // Compute polynomial multiplication using DFT
    mpz_t result_dft;
    mpz_init(result_dft);
    polynomial_multiply_DFT(global_a_value, global_b_value, n, result_dft); 
    ck_assert_msg(Correctness_Check(result_dft, global_expected_result),
        "DFT result was %ld, expected %ld", result_dft, global_expected_result);
}
END_TEST

START_TEST(Karatsuba_test_basic_multiplication) {
    int n = 16; // test size needs to be power 2

    // Compute polynomial multiplication using DFT
    mpz_t result_karatsuba;
    mpz_init(result_karatsuba);
    polynomial_multiply_karatsuba(global_a_value, global_b_value, n, result_karatsuba); 
    ck_assert_msg(Correctness_Check(result_karatsuba, global_expected_result),
        "DFT result was %ld, expected %ld", result_karatsuba, global_expected_result);
}
END_TEST

START_TEST(Recursive_FFT_test_basic_multiplication) {
    int n = 16; // test size needs to be power 2

    // Compute polynomial multiplication using DFT
    mpz_t result_Recursive_FFT;
    mpz_init(result_Recursive_FFT);
    polynomial_multiply_Recursive_FFT(global_a_value, global_b_value, n, result_Recursive_FFT); 
    ck_assert_msg(Correctness_Check(result_Recursive_FFT, global_expected_result),
        "DFT result was %ld, expected %ld", result_Recursive_FFT, global_expected_result);
}
END_TEST

START_TEST(Iterative_FFT_test_basic_multiplication) {
    int n = 16; // test size needs to be power 2

    // Compute polynomial multiplication using DFT
    mpz_t result_Iterative_FFT;
    mpz_init(result_Iterative_FFT);
    polynomial_multiply_iterative_FFT(global_a_value, global_b_value, n, result_Iterative_FFT); 
    ck_assert_msg(Correctness_Check(result_Iterative_FFT, global_expected_result),
        "DFT result was %ld, expected %ld", result_Iterative_FFT, global_expected_result);
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
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            mpz_set_str(global_a_value, "i", 10);
            mpz_set_str(global_b_value, "j", 10);
            mpz_mul(global_expected_result, global_a_value, global_b_value);
            Call_Test(tc_basic);
        }
    }
}


Suite* basic_math_suite(void) {
    Suite *s = suite_create("MathSuite");
    
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
    int n = 256;
    
    
    for (int i = 0; i < 100; i++) {
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



void Test_Setup(){
    mpz_inits(global_a_value, global_b_value, global_expected_result, NULL);
    Basic_Math_Setup();
    mpz_clears(global_a_value, global_b_value, global_expected_result, NULL);
    mpz_inits(global_a_value, global_b_value, global_expected_result, NULL);
    Zero_Setup();
    mpz_clears(global_a_value, global_b_value, global_expected_result, NULL);
    mpz_inits(global_a_value, global_b_value, global_expected_result, NULL);
    // Large_Numbers_test_Setup();
    mpz_clears(global_a_value, global_b_value, global_expected_result, NULL);
    mpz_inits(global_a_value, global_b_value, global_expected_result, NULL);
    Negative_Setup();
    mpz_clears(global_a_value, global_b_value, global_expected_result, NULL);
    
}