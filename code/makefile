CC=gcc
CFLAGS=-Wall -std=gnu11 -O2
PROGRAM=program
FFT = fft
ITERATIVE_FFT = iterative_fft
DFT = dft
KARASUBA = karasuba

OBJS=dft.o fft.o karasuba.o iterative_fft.o

all: $(PROGRAM)
	@./$(PROGRAM)

$(PROGRAM): $(PROGRAM).c $(OBJS)
	$(CC) $(CFLAGS) $(PROGRAM).c $(OBJS) -o $(PROGRAM) -lm

$(DFT).o: $(DFT).c $(DFT).h
	$(CC) $(CFLAGS) -c $(DFT).c

$(KARASUBA).o: $(KARASUBA).c $(KARASUBA).h
	$(CC) $(CFLAGS) -c $(KARASUBA).c

$(FFT).o: $(FFT).c $(FFT).h
	$(CC) $(CFLAGS) -c $(FFT).c

$(ITERATIVE_FFT).o: $(ITERATIVE_FFT).c $(ITERATIVE_FFT).h
	$(CC) $(CFLAGS) -c $(ITERATIVE_FFT).c

clean:
	rm -f $(PROGRAM) $(OBJS)
