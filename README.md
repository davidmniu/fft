# FFT

Man I really need a better name for this project.

## About

FFT is a library which implements FFT. The floor is floor. Water is wet.

## Installation

### Windows / Linux
If you're on Windows, please install WSL before proceeding; you need a Linux environment before you can run this. Otherwise, proceed to clone the repository install the necessary dependencies:

```
git clone git@github.com:davidmniu/fft.git
sudo apt install g++ cmake libfftw3-3
```

To build the project, do this:

```
cd fft
mkdir build
cd build
cmake -G "Unix Makefiles" ..
cmake --build .
```

Thus far, I haven't actually implemented FFT, instead opting for a preliminary naive DFT. To run the benchmark of this DFT against the fftw3, make sure you're in the build directory, and then run the following commands:

```
cd src
./run_benchmark
```

### MacOS

Sorry Peter, I'm not rich.
