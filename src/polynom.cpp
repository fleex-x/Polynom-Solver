#include "polynom.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <optional>
#include <functional>

namespace fleex_x_math {

std::istream& operator>>(std::istream& is, Polynom &polynom) {
	std::size_t degree;
	is >> degree;
	assert(!is.fail());
	polynom.coefficients.resize(degree + 1);
	for (std::size_t i = degree; i != std::size_t(-1); --i) {
		is >> polynom.coefficients[i];
		assert(!is.fail());
	}
	return is;
}

std::ostream& operator<<(std::ostream& os, const Polynom &polynom) {
	os << polynom.degree() << '\n';
	for (std::size_t i = polynom.coefficients.size() - 1; i != std::size_t(-1); --i) {
		if (i != polynom.coefficients.size() - 1) {
			os << ' ';
		}
		os << polynom.coefficients[i];
	}
	return os;
}

std::size_t Polynom::degree() const {
	return std::max(std::size_t(1), coefficients.size()) - 1;
}

double Polynom::value(double x) const {
	double result = 0, x_pow = 1;
	for (auto coefficient : coefficients) {
		result += coefficient * x_pow;
		x_pow *= x;
	}
	return result;
}

bool Polynom::is_positive_value(double x) const {
	return value(x) > 0.0;
}

bool Polynom::is_negative_value(double x) const {
	return value(x) < 0.0;
}

bool Polynom::is_root(double x) const {
	return std::fabs(value(x)) < EPS;
}

Polynom Polynom::get_derivative() const {
	Polynom derivative;
	if (degree() == 0) {
		derivative.coefficients.resize(1, 0.0);
		return derivative;
	}
	derivative.coefficients.resize(degree());
	for (std::size_t i = 0; i <= derivative.degree(); ++i) {
		derivative.coefficients[i] = coefficients[i + 1] * static_cast<double>(i + 1);
	}
	return derivative;
}

std::optional<double> Polynom::find_root(double left_bound, double right_bound,
                				bool is_increasing_on_segment) const { 
	if (is_root(left_bound)) {
		return left_bound;
	}

	if (is_root(right_bound)) {
		return right_bound;
	}

	if (is_positive_value(left_bound) && is_positive_value(right_bound)) {
		return {};
	}
	if (is_negative_value(left_bound) && is_negative_value(right_bound)) {
		return {};
	}
	auto binary_search = [](double left_bound, double right_bound,
	                        std::function<bool(double)> is_root_before) {
		for (int i = 0; i < 80; ++i) {
			double middle = (right_bound + left_bound) / 2.0;
			if (is_root_before(middle)) {
				left_bound = middle;
			} else {
				right_bound = middle;
			}
		}
		return left_bound;
	};
	if (is_increasing_on_segment) {
		return binary_search(left_bound, right_bound, [this](double x){
			return is_negative_value(x);
		});
	} else {
		return binary_search(left_bound, right_bound, [this](double x){
			return is_positive_value(x);
		});
	}
}

std::vector<double> Polynom::get_roots() const {
	assert(degree() > 0);
	std::vector <double> roots;
	if (degree() == 1) {
		roots = {-coefficients[0] / coefficients[1]};
		return roots;
	}
	Polynom derivative = get_derivative();
	std::vector<double> roots_of_derivative = derivative.get_roots();

	auto add_root = [this, &roots, &derivative](double left_bound, double right_bound) {
		double middle = (left_bound + right_bound) / 2.0;
		std::optional<double> root = find_root(left_bound, right_bound, derivative.is_positive_value(middle));
		if (root.has_value() && (roots.empty() || std::fabs(root.value() - roots.back())) > EPS) {
			roots.push_back(root.value());
		}
	};

	double left_bound = 0.0;
	double right_bound = L;

	for (double extremum : roots_of_derivative) {
		left_bound = right_bound;
		right_bound = extremum;
		add_root(left_bound, right_bound);
	}

	left_bound = right_bound;
	right_bound = R;

	add_root(left_bound, right_bound);
	return roots;
}

} // namespace fleex_x_math