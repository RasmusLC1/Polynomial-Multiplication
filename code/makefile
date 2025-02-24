CC=gcc
CFLAGS=-Wall -pedantic -std=gnu11 -O2
LDFLAGS=-lm -lmpfr -lgmp -lcheck -lrt -lpthread -lsubunit # Add libraries here
PROGRAM=src/program
RECURSIVE_FFT=src/Recursive_fft
ITERATIVE_FFT=src/iterative_fft
DFT=src/dft
KARATSUBA=src/karatsuba
WHITEBOX=test/WhiteBox_test
RUNTIME=test/Runtime_test
RUNTIME_SYSTEMATIC = test/Runtime_test_systematic
HELPER_FUNCTIONS=src/Helper_Functions
KARATSUBA_OPTIMSATION = test/karatsuba_optimisation
STANDARD = src/Naive_Polynomial_multiplication

OBJS=src/dft.o src/Recursive_fft.o src/karatsuba.o src/iterative_fft.o test/WhiteBox_test.o test/Runtime_test.o test/Runtime_test_systematic.o test/karatsuba_optimisation.o src/Helper_Functions.o src/Naive_Polynomial_multiplication.o

all: $(PROGRAM)
	@./$(PROGRAM)

$(PROGRAM): $(PROGRAM).c $(OBJS)
	$(CC) $(CFLAGS) $(PROGRAM).c $(OBJS) -o $(PROGRAM) $(LDFLAGS)

src/dft.o: src/dft.c src/dft.h
	$(CC) $(CFLAGS) -c src/dft.c -o src/dft.o

src/karatsuba.o: src/karatsuba.c src/karatsuba.h
	$(CC) $(CFLAGS) -c src/karatsuba.c -o src/karatsuba.o

src/Recursive_fft.o: src/Recursive_fft.c src/Recursive_fft.h
	$(CC) $(CFLAGS) -c src/Recursive_fft.c -o src/Recursive_fft.o

src/iterative_fft.o: src/iterative_fft.c src/iterative_fft.h
	$(CC) $(CFLAGS) -c src/iterative_fft.c -o src/iterative_fft.o

test/WhiteBox_test.o: test/WhiteBox_test.c test/WhiteBox_test.h
	$(CC) $(CFLAGS) -c test/WhiteBox_test.c -o test/WhiteBox_test.o

test/Runtime_test.o: test/Runtime_test.c test/Runtime_test.h
	$(CC) $(CFLAGS) -c test/Runtime_test.c -o test/Runtime_test.o

test/Runtime_test_systematic.o: test/Runtime_test_systematic.c test/Runtime_test_systematic.h
	$(CC) $(CFLAGS) -c test/Runtime_test_systematic.c -o test/Runtime_test_systematic.o

src/Helper_Functions.o: src/Helper_Functions.c src/Helper_Functions.h
	$(CC) $(CFLAGS) -c src/Helper_Functions.c -o src/Helper_Functions.o

src/Naive_Polynomial_multiplication.o: src/Naive_Polynomial_multiplication.c src/Naive_Polynomial_multiplication.h
	$(CC) $(CFLAGS) -c src/Naive_Polynomial_multiplication.c -o src/Naive_Polynomial_multiplication.o

test/karatsuba_optimisation.o: test/karatsuba_optimisation.c test/karatsuba_optimisation.h
	$(CC) $(CFLAGS) -c test/karatsuba_optimisation.c -o test/karatsuba_optimisation.o

clean:
	rm -f $(PROGRAM) $(OBJS)
