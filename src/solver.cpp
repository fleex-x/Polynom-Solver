#include <iostream>
#include <vector>
#include "polynom.h"

using namespace fleex_x_math;

int main() {
	Polynom polynom;
	std::cin >> polynom;
	std::vector<double> roots = polynom.get_roots();
	for (double root : roots) {
		std::cout << root << std::endl;
	}
}