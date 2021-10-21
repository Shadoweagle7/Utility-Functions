// Utility Functions.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <concepts>
#include <stdexcept>
#include <string>
#include <type_traits>

template<std::integral I>
class clamp {
private:
	I m_low, m_high;
public:
	clamp(I low, I high) : m_low(low), m_high(high) {}

	I assign(I val) {
		if (val < this->m_low || val > this->m_high) {
			throw std::out_of_range("Value " + std::to_string(val) + " out of range");
		}

		return val;
	}
};

template<int LOW, int HIGH>
class constexpr_clamp {
private:
	int m_val;
public:
	constexpr constexpr_clamp(int val) {
		if (val < LOW || val > HIGH) {
			throw std::out_of_range("Value " + std::to_string(val) + " out of range");
		}

		this->m_val = val;
	}

	constexpr operator int &() {
		return this->m_val;
	}
};

constexpr int test(constexpr_clamp<0, 1> value) {
	int n = value;

	return n;
}

int main() {
	try {
		constexpr int a = test(0);
		constexpr int b = test(1);

		// Because the constructor of constexpr_clamp throws if a value is out of range,
		// this results in a compile time error (MSVC! C3615: Expression cannot be interpreted)
		// constexpr size_t c = test(2);
		// constexpr constexpr_clamp<0, 1> d = 27;
		constexpr constexpr_clamp<0, 1> e = 0;
	} catch (const std::exception &e) {
		std::cout << e.what() << std::endl;
	}

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
