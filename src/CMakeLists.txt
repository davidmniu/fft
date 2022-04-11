find_package(benchmark REQUIRED)

add_executable(run_benchmark ./benchmark.cpp ./fft.hpp ./timer.hpp)
add_executable(debug ./debug.cpp ./fft.hpp ./timer.hpp)


target_link_libraries(run_benchmark fftw3)
target_link_libraries(run_benchmark benchmark::benchmark)

target_link_libraries(debug fftw3)
