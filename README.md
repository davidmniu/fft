# FFT

Man I really need a better name for this project.

## About

FFT is a library which implements the Fast Fourier Transform. The floor is floor. Water is wet.

## Installation

### Windows / Linux
If you're on Windows, please install WSL before proceeding; you need a Linux environment before you can run this. Otherwise, proceed to clone the repository and install the necessary dependencies:

```
git clone git@github.com:davidmniu/fft.git
sudo apt install g++ cmake libfftw3-3
```

To benchmark the routines, you'll need google benchmark installed as well; please refer to their [documentation](https://github.com/google/benchmark#installation). Make sure to install the library globally. To build the project, do this:

```
cd fft
mkdir build
cd build
cmake -G "Unix Makefiles" ..
cmake --build .
```

Thus far, I've implemented a brute force DFT and a recursive radix-2 DIT Cooley-Tukey FFT, as well as an iterative in-place version which uses bit-reversal. To benchmark these routines against FFTW, make sure you're in the build directory, and then run the following commands:

```
cd src
./run_benchmark
```

### MacOS

Sorry Peter, I'm not rich.
