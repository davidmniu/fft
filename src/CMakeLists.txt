add_executable(run_benchmark ./benchmark.cpp ./fft.hpp ./timer.hpp)

target_link_libraries(run_benchmark fftw3)
