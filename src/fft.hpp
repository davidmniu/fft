#include <complex>
#include <vector>

using namespace std::complex_literals;

template <typename T>
class FFT {
	public:
		// FFT();
		bool naive_fwd(std::vector<T>& a, std::vector<std::complex<T>>& b) {
			if (a.size() != b.size()) return false;
			int N = a.size();
			for (int k = 0; k < N; k++) {
				b[k] = 0;
				std::complex<T> blah = ((std::complex<T>) ((T) -2 * (T) M_PI / (T) N)) * (std::complex<T>) 1i;
				for (int n = 0; n < N; n++) {
					b[k] +=	a[n] * std::exp(blah * (T) N * (T) k);
				}
			}
			return true;
		}
		void naive_inv(std::vector<T> a, std::vector<T> b);
};
