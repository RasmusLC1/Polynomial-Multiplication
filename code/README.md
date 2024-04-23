# Multiplication of polynomials
This project is a C application that demonstrates different ways of calculating polynomials including
## DFT
## Karatsuba
## Recursive FFT
## Iterative FFT

## This code has been tested using WSL
### Prerequisites
Make sure you have a C compiler and the make utility installed on your system. For Unix-like systems, this typically involves installing the GCC compiler and related tools.
#### Linux:
      sudo apt-get update
      sudo apt-get install build-essential
      sudo apt-get install check
#### Mac:
      xcode-select --install
      brew install check
### To compile and run the code
      cd path/to/project
      make
This will produce an executable and run the code
### To clean
      make clean

### Dependencies
This program uses several standard libraries that are typically included with the C standard library, which is included with most C compilers.

The program also utilizes some POSIX-specific headers (<sys/ioctl.h> and <unistd.h>), which may not be available on non-POSIX systems like Windows by default. Windows users may need to install a POSIX compatibility layer or use a POSIX-compliant environment like Cygwin or the Windows Subsystem for Linux (WSL).
