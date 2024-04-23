// #include "dft.h"

// void init_mpfr_array(mpfr_t *arr, int size, mp_prec_t prec) {
//     for (int i = 0; i < size; i++) {
//         mpfr_init2(arr[i], prec);
//     }
// }

// void clear_mpfr_array(mpfr_t *arr, int size) {
//     for (int i = 0; i < size; i++) {
//         mpfr_clear(arr[i]);
//     }
// }

// void DFT(mpfr_t *in_real, mpfr_t *in_imag, int n, mpfr_t *out_real, mpfr_t *out_imag) {
//     mpfr_t c, s, temp_real, temp_imag, angle;
//     mpfr_inits(c, s, temp_real, temp_imag, angle, NULL);

//     for (int i = 0; i < n; i++) {
//         mpfr_set_ui(out_real[i], 0, MPFR_RNDN);
//         mpfr_set_ui(out_imag[i], 0, MPFR_RNDN);
//         for (int t = 0; t < n; t++) {
//             mpfr_set_d(angle, -TAU * t * i / n, MPFR_RNDN);
//             mpfr_cos(c, angle, MPFR_RNDN);
//             mpfr_sin(s, angle, MPFR_RNDN);

//             mpfr_mul(temp_real, in_real[t], c, MPFR_RNDN);
//             mpfr_mul(temp_imag, in_imag[t], s, MPFR_RNDN);
//             mpfr_sub(temp_real, temp_real, temp_imag, MPFR_RNDN);
//             mpfr_add(out_real[i], out_real[i], temp_real, MPFR_RNDN);

//             mpfr_mul(temp_real, in_real[t], s, MPFR_RNDN);
//             mpfr_mul(temp_imag, in_imag[t], c, MPFR_RNDN);
//             mpfr_add(temp_real, temp_real, temp_imag, MPFR_RNDN);
//             mpfr_add(out_imag[i], out_imag[i], temp_real, MPFR_RNDN);
//         }
//     }

//     mpfr_clears(c, s, temp_real, temp_imag, angle, NULL);
// }

// void IDFT(mpfr_t *in_real, mpfr_t *in_imag, int n, mpfr_t *out_real, mpfr_t *out_imag) {
//     mpfr_t c, s, temp_real, temp_imag, angle;
//     mpfr_inits(c, s, temp_real, temp_imag, angle, NULL);

//     for (int i = 0; i < n; i++) {
//         mpfr_set_ui(out_real[i], 0, MPFR_RNDN);
//         mpfr_set_ui(out_imag[i], 0, MPFR_RNDN);
//         for (int t = 0; t < n; t++) {
//             mpfr_set_d(angle, TAU * t * i / n, MPFR_RNDN);
//             mpfr_cos(c, angle, MPFR_RNDN);
//             mpfr_sin(s, angle, MPFR_RNDN);

//             mpfr_mul(temp_real, in_real[t], c, MPFR_RNDN);
//             mpfr_mul(temp_imag, in_imag[t], s, MPFR_RNDN);
//             mpfr_add(temp_real, temp_real, temp_imag, MPFR_RNDN);
//             mpfr_add(out_real[i], out_real[i], temp_real, MPFR_RNDN);

//             mpfr_mul(temp_real, in_real[t], s, MPFR_RNDN);
//             mpfr_mul(temp_imag, in_imag[t], c, MPFR_RNDN);
//             mpfr_sub(temp_real, temp_real, temp_imag, MPFR_RNDN);
//             mpfr_add(out_imag[i], out_imag[i], temp_real, MPFR_RNDN);
//         }
//         mpfr_div_ui(out_real[i], out_real[i], n, MPFR_RNDN);  // Normalize the output
//         mpfr_div_ui(out_imag[i], out_imag[i], n, MPFR_RNDN);  // Normalize the output
//     }

//     mpfr_clears(c, s, temp_real, temp_imag, angle, NULL);
// }

// long polynomial_multiply_DFT(complex double *a, complex double *b, int o){
//     int n = 4;  // Set size of DFT
//     mpfr_t in_real_1[n], in_imag_1[n], in_real_2[n], in_imag_2[n], out_real[n], out_imag[n], product_real[n], product_imag[n];

//     init_mpfr_array(in_real_1, n, 256);
//     init_mpfr_array(in_imag_1, n, 256);
//     init_mpfr_array(in_real_2, n, 256);
//     init_mpfr_array(in_imag_2, n, 256);
//     init_mpfr_array(out_real, n, 256);
//     init_mpfr_array(out_imag, n, 256);
//     init_mpfr_array(product_real, n, 256);
//     init_mpfr_array(product_imag, n, 256);

//     mpfr_set_ui(in_real_1[0], 4, MPFR_RNDN); mpfr_set_ui(in_imag_1[0], 0, MPFR_RNDN);
//     mpfr_set_ui(in_real_1[1], 7, MPFR_RNDN); mpfr_set_ui(in_imag_1[1], 0, MPFR_RNDN);
//     mpfr_set_ui(in_real_1[2], 0, MPFR_RNDN); mpfr_set_ui(in_imag_1[2], 0, MPFR_RNDN);
//     mpfr_set_ui(in_real_1[3], 0, MPFR_RNDN); mpfr_set_ui(in_imag_1[3], 0, MPFR_RNDN);

//     mpfr_set_ui(in_real_2[0], 4, MPFR_RNDN); mpfr_set_ui(in_imag_2[0], 0, MPFR_RNDN);
//     mpfr_set_ui(in_real_2[1], 3, MPFR_RNDN); mpfr_set_ui(in_imag_2[1], 0, MPFR_RNDN);
//     mpfr_set_ui(in_real_2[2], 0, MPFR_RNDN); mpfr_set_ui(in_imag_2[2], 0, MPFR_RNDN);
//     mpfr_set_ui(in_real_2[3], 0, MPFR_RNDN); mpfr_set_ui(in_imag_2[3], 0, MPFR_RNDN);

//     DFT(in_real_1, in_imag_1, n, product_real, product_imag);
//     DFT(in_real_2, in_imag_2, n, out_real, out_imag);

//     mpfr_t ac, bd, ad, bc;
//     mpfr_inits(ac, bd, ad, bc, NULL);
//     for (int i = 0; i < n; i++) {
//         mpfr_mul(ac, product_real[i], out_real[i], MPFR_RNDN);
//         mpfr_mul(bd, product_imag[i], out_imag[i], MPFR_RNDN);
//         mpfr_sub(product_real[i], ac, bd, MPFR_RNDN);

//         mpfr_mul(ad, product_real[i], out_imag[i], MPFR_RNDN);
//         mpfr_mul(bc, product_imag[i], out_real[i], MPFR_RNDN);
//         mpfr_add(product_imag[i], ad, bc, MPFR_RNDN);
//     }
//     mpfr_clears(ac, bd, ad, bc, NULL);

//     IDFT(product_real, product_imag, n, out_real, out_imag);

//     int digits[n];
//     for (int i = 0; i < n; i++) {
//         digits[i] = mpfr_get_d(out_real[i], MPFR_RNDN);
//     }

//     for (int i = n - 1; i > 0; i--) {
//         if (digits[i] >= 10) {
//             int carry = digits[i] / 10;
//             digits[i] %= 10;
//             digits[i - 1] += carry;
//         }
//     }

//     printf("Final result of multiplication: ");
//     for (int i = 0; i < n; i++) {
//         printf("%d", digits[i]);
//     }
//     printf("\n");

//     clear_mpfr_array(in_real_1, n);
//     clear_mpfr_array(in_imag_1, n);
//     clear_mpfr_array(in_real_2, n);
//     clear_mpfr_array(in_imag_2, n);
//     clear_mpfr_array(out_real, n);
//     clear_mpfr_array(out_imag, n);
//     clear_mpfr_array(product_real, n);
//     clear_mpfr_array(product_imag, n);

//     return 5;
// }