#define EIGEN_FFTW_DEFAULT

#include <iostream>
#include <algorithm>
#include <ctime>
#include "fft.hpp"
#include "timer.hpp"
#include <fftw3.h>
// #include "../lib/eigen-3.4.0/unsupported/Eigen/FFT"
// #include "Eigen3/unsupported/Eigen/FFT"
// #include <unsupported/Eigen/FFT>


#define NUM_POINTS 1000

#include <stdio.h>
#include <math.h>

#define REAL 0
#define IMAG 1

void acquire_from_somewhere(fftw_complex* signal) {
    /* Generate two sine waves of different frequencies and
     * amplitudes.
     */

    int i;
    for (i = 0; i < NUM_POINTS; ++i) {
        double theta = (double)i / (double)NUM_POINTS * M_PI;

        signal[i][REAL] = 1.0 * cos(10.0 * theta) +
                          0.5 * cos(25.0 * theta);

        signal[i][IMAG] = 1.0 * sin(10.0 * theta) +
                          0.5 * sin(25.0 * theta);
    }
}

void do_something_with(fftw_complex* result) {
    int i;
    for (i = 0; i < NUM_POINTS; ++i) {
        double mag = sqrt(result[i][REAL] * result[i][REAL] +
                          result[i][IMAG] * result[i][IMAG]);

        printf("%g\n", mag);
    }
}


int main() {
	Timer t;

	FFT<float> naive_fft;
	
	std::srand(unsigned(std::time(nullptr)));
	std::vector<float> a(1000);
	std::generate(a.begin(), a.end(), std::rand);

	// std::cout << "The first 10 elements of vector a are ";
	// for (int i = 0; i < 10; i++) std::cout << a[i] << ' ';
	// std::cout << std::endl;

	std::vector<std::complex<float>> b(1000);

	auto t1 = t.elapsed();
	naive_fft.naive_fwd(a, b);
	auto t2 = t.elapsed() - t1;
	std::cout << "time for naive dft is " << t2 << std::endl;

	// std::cout << "The first 10 elements of vector b are ";
	// for (int i = 0; i < 10; i++) std::cout << b[i] << ' ';
	// std::cout << std::endl;
	


	// t1 = t.elapsed();
	// fft.fwd(freqvec,a);
	// t2 = t.elapsed() - t1;
	// std::cout << "time for Eigen fft is " << t2 << std::endl;


	fftw_complex signal[NUM_POINTS];
    fftw_complex result[NUM_POINTS];

    fftw_plan plan = fftw_plan_dft_1d(NUM_POINTS,
                                      signal,
                                      result,
                                      FFTW_FORWARD,
                                      FFTW_ESTIMATE);

    acquire_from_somewhere(signal);

	t1 = t.elapsed();
    fftw_execute(plan);
	t2 = t.elapsed() - t1;
	std::cout << "time for fftw is " << t2 << std::endl;

    fftw_destroy_plan(plan);

	return 0;
}
