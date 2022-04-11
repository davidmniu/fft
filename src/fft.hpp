#ifndef FFT_H
#define FFT_H

#include <complex>
#include <vector>
#include <iostream>

using namespace std::complex_literals;

template <typename T>
using cvec = std::vector<std::complex<T>>;

template <typename T>
class FFT {
	public:
		bool naive_fwd(const cvec<T>& a, cvec<T>& b) {
			if (a.size() != b.size()) return false;
			int N = a.size();
			for (int k = 0; k < N; k++) {
				b[k] = 0;
				std::complex<T> blah = ((std::complex<T>) ((T) -2 * (T) M_PI / (T) N)) * (std::complex<T>) 1i;
				for (int n = 0; n < N; n++) {
					b[k] +=	a[n] * std::exp(blah * (T) n * (T) k);
				}
			}
			return true;
		}
		void naive_inv(const std::vector<T> a, std::vector<T> b);

		bool ditfft2_fwd(const cvec<T>& a, cvec<T>& b) {
			int N = a.size();
			if (N & (N - 1)) return false;
			b = ditfft2(a, 0, N, 1);
			return true;
		}

		bool iter_ditfft2_fwd(const cvec<T>& a, cvec<T>& b) {
			int N = a.size(); int n = N;
			if (N & (N - 1)) return false;
			b = bit_rev_copy(a);
			int lgn = 0; while (n >>= 1) lgn++;
			std::complex<T> t,u;
			for (int s = 1; s <= lgn; s++) {
				int m = 1 << s;
				std::complex<T> omega_m = std::exp((T)2 * M_PI * 1i / (T)m);
				for (int k = 0; k < N; k += m) {
					std::complex<T> omega = 1;
					for (int j = 0; j < m/2; j++) {
						t = omega * b[k+j+m/2];
						u = b[k+j];
						b[k+j] = u+t;
						b[k+j+m/2] = u-t;
						omega *= omega_m;
					}
				}
			}
			return true;
		}
	private:
		cvec<T> ditfft2(const cvec<T>& a, int x, int N, int s) {
			if (N == 1) {
				return {a[x]};
			} else {
				cvec<T> output = ditfft2(a, x, N/2, 2*s);
				cvec<T> other = ditfft2(a, x+s, N/2, 2*s);
				std::complex<T> p, q;
				std::complex<T> blah = ((std::complex<T>) ((T) -2 * (T) M_PI / (T) N)) * (std::complex<T>) 1i;
				for (int k = 0; k < N/2; k++) {
					p = output[k];
					q = other[k] * std::exp(blah * (T) k);
					output[k] = p + q;
					other[k] = p - q;
				}
				output.insert(output.end(), std::begin(other), std::end(other));
				return output;
			}
		}

		cvec<T> bit_rev_copy(const cvec<T>& a) {
			int n = a.size(); int k = 0;
			cvec<T> output(n);
			while (n >>= 1) k++;
			for (int i = 0; i < a.size(); i++) {
				output[rev(i, k)] = a[i];
			}
			return output;
		}

		int rev(int a, int k) {
			int ans = 0;
			for (int i = 0; i < k; i++) {
				ans += (1 << (k-1-i))*(a & 1);
				a >>= 1;
			}
			return ans;
		}
};

#endif
