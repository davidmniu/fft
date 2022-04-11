#include <iostream>
#include "fft.hpp"
#include <fftw3.h>

#define NUM_POINTS 1024

#include <stdio.h>
#include <math.h>

#define REAL 0
#define IMAG 1

#include <benchmark/benchmark.h>

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

static void BM_naive_dft(benchmark::State& state) {
	fftw_complex signal[NUM_POINTS];
	acquire_from_somewhere(signal);
	std::vector<std::complex<double>> a(NUM_POINTS);
	std::vector<std::complex<double>> b(NUM_POINTS);
	for (int i = 0; i < NUM_POINTS; i++) a[i] = {signal[i][0], signal[i][1]};	
	FFT<double> fft;
	for (auto _ : state) {
		fft.naive_fwd(a, b);
	}
}


static void BM_ditfft2_fwd(benchmark::State& state) {
	fftw_complex signal[NUM_POINTS];
	acquire_from_somewhere(signal);
	std::vector<std::complex<double>> a(NUM_POINTS);
	std::vector<std::complex<double>> b(NUM_POINTS);
	for (int i = 0; i < NUM_POINTS; i++) a[i] = {signal[i][0], signal[i][1]};	
	FFT<double> fft;
	for (auto _ : state) {
		fft.ditfft2_fwd(a, b);
	}
}

static void BM_iter_dit_fft2_fwd(benchmark::State& state) {
	fftw_complex signal[NUM_POINTS];
	acquire_from_somewhere(signal);
	std::vector<std::complex<double>> a(NUM_POINTS);
	std::vector<std::complex<double>> b(NUM_POINTS);
	for (int i = 0; i < NUM_POINTS; i++) a[i] = {signal[i][0], signal[i][1]};	
	FFT<double> fft;
	for (auto _ : state) {
		fft.iter_ditfft2_fwd(a, b);
	}
}

static void BM_fftw(benchmark::State& state) {
	fftw_complex signal[NUM_POINTS];
	fftw_complex result[NUM_POINTS];

	fftw_plan plan = fftw_plan_dft_1d(NUM_POINTS,
								   signal,
								   result,
								   FFTW_FORWARD,
								   FFTW_ESTIMATE);
	acquire_from_somewhere(signal);
	for (auto _ : state) {
		fftw_execute(plan);
	}
    fftw_destroy_plan(plan);
}

BENCHMARK(BM_naive_dft);
BENCHMARK(BM_ditfft2_fwd);
BENCHMARK(BM_iter_dit_fft2_fwd);
BENCHMARK(BM_fftw);

BENCHMARK_MAIN();
