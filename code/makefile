CC=gcc
CFLAGS=-Wall -pedantic -std=gnu11 -O2
PROGRAM=program
RECURSIVE_FFT = Recursive_fft
ITERATIVE_FFT = iterative_fft
DFT = dft
karatsuba = karatsuba

OBJS=$(DFT).o $(RECURSIVE_FFT).o $(karatsuba).o $(ITERATIVE_FFT).o

all: $(PROGRAM)
	@./$(PROGRAM)

$(PROGRAM): $(PROGRAM).c $(OBJS)
	$(CC) $(CFLAGS) $(PROGRAM).c $(OBJS) -o $(PROGRAM) -lm

$(DFT).o: $(DFT).c $(DFT).h
	$(CC) $(CFLAGS) -c $(DFT).c

$(karatsuba).o: $(karatsuba).c $(karatsuba).h
	$(CC) $(CFLAGS) -c $(karatsuba).c

$(RECURSIVE_FFT).o: $(RECURSIVE_FFT).c $(RECURSIVE_FFT).h
	$(CC) $(CFLAGS) -c $(RECURSIVE_FFT).c

$(ITERATIVE_FFT).o: $(ITERATIVE_FFT).c $(ITERATIVE_FFT).h
	$(CC) $(CFLAGS) -c $(ITERATIVE_FFT).c

clean:
	rm -f $(PROGRAM) $(OBJS)
