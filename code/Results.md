The results when running the test:

n size: 16m      iterations: 100000
DFT multiplication time:        1.828125 seconds.
FFT multiplication time:        0.187500 seconds.
iterative_FFT multiplication time:      0.109375 seconds.
karatsuba multiplication time:  0.187500 seconds.

To find number of lines of code use

find /path/to/code -type f \( -name '*.c' -o -name '*.h' \) -exec wc -l {} +
