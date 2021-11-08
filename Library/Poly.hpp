#ifndef CS312OOP_LAB2_POLY_HPP
#define CS312OOP_LAB2_POLY_HPP

#include <iostream>
#include <vector>
#include <optional>

namespace math {
    /// Polynomial class
    class Poly {
    private:
        /// Poly max degree - 20
        static const size_t MX_DEGREE = 21;
        /// Newton's method parameter
        /// the higher number the more precision in Poly::zero()
        constexpr static const size_t NEWTON_LIMIT = 50;
        /// Polynomial coefficients
        std::vector<double> values;
    public:
        Poly() : values{0} {}

        explicit Poly(double c) : values{c} {}

        explicit Poly(size_t size) : values(size, 0) {}

        explicit Poly(std::vector<double> &v) {
            if (v.size() >= MX_DEGREE)
                throw std::out_of_range("Too high poly degree");
            values = std::move(v);
        }

        Poly(const Poly &p) = default;

        Poly(Poly &&p)  noexcept : values(std::move(p.values)) {}

        [[nodiscard]] size_t get_degree() const { return values.size(); }

        double &operator[](size_t i) { return values[i]; }

        const double &operator[](size_t i) const { return values[i]; }

        double &at(size_t i) { return values.at(i); }

        [[nodiscard]] const double &at(size_t i) const { return values.at(i); }


        Poly &operator=(const Poly &);

        Poly &operator=(Poly &&) noexcept ;

        /// Poly sum
        friend Poly operator+(const Poly &, const Poly &);

        /// Poly value in point
        double operator()(double) const;

        /// Poly derivative
        Poly derivative() const;

        /// Poly division (by (x-b)); result is a new poly and a remainder
        friend std::pair<Poly, double> operator/(const Poly &, double);

        /// Poly zero on segment - newtons method
        /// there may be no root in (a, b)
        [[nodiscard]] std::optional<double> zero(double, double) const;

        friend std::ostream &operator<<(std::ostream &, const Poly &);

        friend std::istream &operator>>(std::istream &, Poly &);
    };
}


#endif //CS312OOP_LAB2_POLY_HPP
