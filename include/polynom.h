#ifndef POLYNOM_H_
#define POLYNOM_H_
#include <vector>
#include <iosfwd>
#include <optional>

namespace fleex_x_math {

class Polynom {
private:
	inline static const double EPS = 1e-4;
	inline static const double L = -1e12;
	inline static const double R = 1e12;
	std::vector <double> coefficients;
	std::optional<double> find_root(double, double, bool) const;
public:
	friend std::istream& operator>>(std::istream&, Polynom &);
	friend std::ostream& operator<<(std::ostream&, const Polynom &);

	std::size_t degree() const;
	double value(double) const;
	bool is_positive_value(double) const;
	bool is_negative_value(double) const;
	bool is_root(double) const;
	
	Polynom get_derivative() const;
	std::vector<double> get_roots() const;
};

} // fleex_x_math

#endif // POLYNOM_H_