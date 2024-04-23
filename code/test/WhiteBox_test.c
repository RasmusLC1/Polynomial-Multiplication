#include "WhiteBox_test.h"




START_TEST(DFT_test_basic_multiplication) {
    int n = 16; // test size needs to be power 2

    // Compute polynomial multiplication using DFT
    long result_dft = polynomial_multiply_DFT(global_a_value, global_b_value, n); 
    ck_assert_msg(result_dft == global_expected_result,
        "DFT result was %ld, expected %ld", result_dft, global_expected_result);
}
END_TEST

START_TEST(Karatsuba_test_basic_multiplication) {
    int n = 16; // test size needs to be power 2

    // Compute polynomial multiplication using DFT
    long result_dft = polynomial_multiply_karatsuba(global_a_value, global_b_value, n); 
    ck_assert_msg(result_dft == global_expected_result,
        "DFT result was %ld, expected %ld", result_dft, global_expected_result);
}
END_TEST

START_TEST(Recursive_FFT_test_basic_multiplication) {
    int n = 16; // test size needs to be power 2

    // Compute polynomial multiplication using DFT
    long result_dft = polynomial_multiply_Recursive_FFT(global_a_value, global_b_value, n); 
    ck_assert_msg(result_dft == global_expected_result,
        "DFT result was %ld, expected %ld", result_dft, global_expected_result);
}
END_TEST

START_TEST(Iterative_FFT_test_basic_multiplication) {
    int n = 16; // test size needs to be power 2

    // Compute polynomial multiplication using DFT
    long result_dft = polynomial_multiply_iterative_FFT(global_a_value, global_b_value, n); 
    ck_assert_msg(result_dft == global_expected_result,
        "DFT result was %ld, expected %ld", result_dft, global_expected_result);
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
            global_a_value = i;
            global_b_value = j;
            global_expected_result = i * j;
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
    global_a_value = 0;
    global_b_value = 0;
    global_expected_result = global_a_value * global_b_value;
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

    // Seed randomiser with time
    srand(time(NULL));

    // Check if the seed works and we get true random variables
    assert(rand() != rand());
    
    
    for (int i = 0; i < 100; i++) {
        global_a_value = rand() % (long long)pow(10, 8);
        global_b_value = rand() % (long long)pow(10, 8);
        global_expected_result = global_a_value * global_b_value;
        Call_Test(tc_large);
        
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
    global_a_value = -5;
    global_b_value = 5;
    global_expected_result = global_a_value * global_b_value;
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
    // Basic_Math_Setup();
    // Large_Numbers_test_Setup();
    Zero_Setup();
    Negative_Setup();
}