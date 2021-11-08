#include "Poly.hpp"

namespace math {
    Poly &Poly::operator=(const Poly &p) {
        if (this != &p)
            this->values = p.values;
        return *this;
    }

    Poly &Poly::operator=(Poly &&p)  noexcept {
        if (this != &p)
            this->values = std::move(p.values);
        return *this;
    }

    Poly operator+(const Poly &right, const Poly &left) {
        const Poly &bigger = right.get_degree() > left.get_degree() ? right : left;
        const Poly &lesser = (&bigger == &right)  ? left : right;

        Poly res(bigger);

        for (size_t i = 0; i < lesser.get_degree(); ++i)
            res[i] += lesser[i];

        return res;
    }

    double Poly::operator()(double x) const {
        double res = 0, x_pow = 1;
        for (size_t i = 0; i < get_degree(); ++i) {
            res += values[i] * x_pow;
            x_pow *= x;
        }
        return res;
    }

    Poly Poly::derivative() const {
        if (get_degree() == 1)
            return {};
        Poly res(get_degree() - 1);
        for (size_t i = 1; i < get_degree(); ++i)
            res[i - 1] = values[i];
        return res;
    }

    std::pair<Poly, double> operator/(const Poly &p, double b) {
        if (p.get_degree() == 1)
            throw std::runtime_error("Can't divide constant polynomial");
        Poly res(p.get_degree() - 1);
        double remainder = p[p.get_degree() - 1];
        for (size_t i = p.get_degree() - 2; i > 0; --i) {
            res[i] = remainder;
            remainder = p[i] - remainder * b;
        }
        res[0] = remainder;
        remainder = p[0] - remainder * b;
        return {res, remainder};
    }

    std::optional<double> Poly::zero(double a, double b) const {
        if (a >= b)
            throw std::range_error("Wrong interval");
        double x = a + (b - a) / 2; // mid
        // check constant polynomial
        if (get_degree() == 1) {
            if (values[0] == 0)
                return x; // any x in (a, b) is a root
            return {};
        }
        Poly d = this->derivative();

        // Newton
        for (size_t i = 0; i < NEWTON_LIMIT; ++i)
            x -= (*this)(x) / d(x);

        // bound check
        if (x > a && x < b)
            return x;
        return {};
    }

    std::ostream &operator<<(std::ostream &out, const Poly &p) {
        // print with sign
        out << std::showpos;
        for (size_t i = p.get_degree() - 1; i > 0; --i)
            out << p[i] << "*x**" << i << " ";
        out << p[0];
        return out;
    }

    /// silent read; check in.good() for more info
    /// format - size_t degree then doubles
    std::istream &operator>>(std::istream &in, Poly &p) {
        size_t deg;
        in >> deg;
        if (!in.good())
            return in;
        if (deg >= Poly::MX_DEGREE) {
            in.setstate(std::ios_base::failbit);
            return in;
        }
        p.values.resize(deg);

        for (size_t i = 0; i < p.get_degree(); ++i) {
            in >> p[p.get_degree() - i - 1];
            if (!in.good())
                return in;
        }
        return in;
    }
}