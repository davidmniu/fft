#include <iostream>
#include "fft.hpp"
#include <fftw3.h>

#define NUM_POINTS 8

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
	FFT<double> fft;

	fftw_complex signal[NUM_POINTS];
    fftw_complex result[NUM_POINTS];

	fftw_plan plan = fftw_plan_dft_1d(NUM_POINTS,
                                      signal,
                                      result,
                                      FFTW_FORWARD,
                                      FFTW_ESTIMATE);
    acquire_from_somewhere(signal);

	// copy a from signal
	std::vector<std::complex<double>> a(NUM_POINTS);
	for (int i = 0; i < NUM_POINTS; i++) {
		a[i] = {signal[i][0], signal[i][1]};	
	}
	 
	std::cout << "The first 10 elements of vector a are:" << std::endl;
	for (int i = 0; i < 8; i++) std::cout << a[i] << std::endl;

	// naive dft
	std::vector<std::complex<double>> b(NUM_POINTS);
	fft.iter_ditfft2_fwd(a, b);
	std::cout << "The first 10 elements of vector b are:" << std::endl;
	for (int i = 0; i < 8; i++) std::cout << b[i] << std::endl;

	// the gold standard, fftw
	fftw_execute(plan);
	std::cout << "The first 10 elements of array result are:" << std::endl;
	for (int i = 0; i < 8; i++) std::cout << result[i][0] << ", " << result[i][1] << std::endl;
    fftw_destroy_plan(plan);

	return 0;
}
