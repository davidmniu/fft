#include <vector>

template <typename T>
class matrix {
	private:
		int x, y;
		std::vector<std::vector<T>> m;
	public:
		matrix(int a, int b);
		T get(int a, int b);
};
