CC=gcc
CFLAGS=-Wall -pedantic -std=gnu11 -O2
LDFLAGS=-lm -lmpfr -lgmp -lcheck -lrt -lpthread -lsubunit # Add libraries here
PROGRAM=program
RECURSIVE_FFT=Recursive_fft
ITERATIVE_FFT=iterative_fft
DFT=dft
KARATSUBA=karatsuba
WHITEBOX=test/WhiteBox_test
HELPER_FUNCTIONS=Helper_Functions

OBJS=$(DFT).o $(RECURSIVE_FFT).o $(KARATSUBA).o $(ITERATIVE_FFT).o WhiteBox_test.o $(HELPER_FUNCTIONS).o

all: $(PROGRAM)
	@./$(PROGRAM)

$(PROGRAM): $(PROGRAM).c $(OBJS)
	$(CC) $(CFLAGS) $(PROGRAM).c $(OBJS) -o $(PROGRAM) $(LDFLAGS)

$(DFT).o: $(DFT).c $(DFT).h
	$(CC) $(CFLAGS) -c $(DFT).c

$(KARATSUBA).o: $(KARATSUBA).c $(KARATSUBA).h
	$(CC) $(CFLAGS) -c $(KARATSUBA).c

$(RECURSIVE_FFT).o: $(RECURSIVE_FFT).c $(RECURSIVE_FFT).h
	$(CC) $(CFLAGS) -c $(RECURSIVE_FFT).c

$(ITERATIVE_FFT).o: $(ITERATIVE_FFT).c $(ITERATIVE_FFT).h
	$(CC) $(CFLAGS) -c $(ITERATIVE_FFT).c

WhiteBox_test.o: $(WHITEBOX).c $(WHITEBOX).h
	$(CC) $(CFLAGS) -c $(WHITEBOX).c

$(HELPER_FUNCTIONS).o: $(HELPER_FUNCTIONS).c $(HELPER_FUNCTIONS).h
	$(CC) $(CFLAGS) -c $(HELPER_FUNCTIONS).c

clean:
	rm -f $(PROGRAM) $(OBJS)
