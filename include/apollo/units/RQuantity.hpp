/*
 * This code is a modified version of Benjamin Jurke's work in 2015. You can
 * read his blog post here:
 * https://benjaminjurke.com/content/articles/2015/compile-time-numerical-unit-dimension-checking/
 */

#pragma once
#include <cmath>
#include <ratio>

// The "RQuantity" class is the prototype template container class, that just
// holds a double value. The class SHOULD NOT BE INSTANTIATED directly by
// itself, rather use the quantity types defined below.
namespace apollo {
template <typename MassDim, typename LengthDim, typename TimeDim,
          typename AngleDim>
class RQuantity {
private:
  double value;

public:
  constexpr RQuantity() : value(0.0) {}
  constexpr RQuantity(double val) : value(val) {}
  constexpr RQuantity(long double val) : value(static_cast<double>(val)) {}
  // Addition
  constexpr RQuantity const &operator+=(const RQuantity &rhs) {
    value += rhs.value;
    return *this;
  }
  // Subtraction
  constexpr RQuantity const &operator-=(const RQuantity &rhs) {
    value -= rhs.value;
    return *this;
  }

  // Negative
  constexpr RQuantity operator-() { return RQuantity(value * -1); }

  // Multiplication
  constexpr RQuantity const &operator*=(const double rhs) {
    value *= rhs;
    return *this;
  }

  // Division
  constexpr RQuantity const &operator/=(const double rhs) {
    value /= rhs;
    return *this;
  }

  // Absolute Value
  constexpr RQuantity<MassDim, LengthDim, TimeDim, AngleDim> abs() const {
    return RQuantity<MassDim, LengthDim, TimeDim, AngleDim>(std::fabs(value));
  }

  // Square Root
  constexpr RQuantity<std::ratio_divide<MassDim, std::ratio<2>>,
                      std::ratio_divide<LengthDim, std::ratio<2>>,
                      std::ratio_divide<TimeDim, std::ratio<2>>,
                      std::ratio_divide<AngleDim, std::ratio<2>>>
  sqrt() const {
    return RQuantity<std::ratio_divide<MassDim, std::ratio<2>>,
                     std::ratio_divide<LengthDim, std::ratio<2>>,
                     std::ratio_divide<TimeDim, std::ratio<2>>,
                     std::ratio_divide<AngleDim, std::ratio<2>>>(
        std::sqrt(value));
  }

  // Returns the value of the quantity in multiples of the specified unit
  constexpr double convert(const RQuantity &rhs) const {
    return value / rhs.value;
  }

  // Returns the raw value of the quantity (Should not be used)
  constexpr double getValue() const { return value; }
};

/*
QUANTITY_TYPE(1, 0, 0, 0, QMass);
QUANTITY_TYPE(0, 1, 0, 0, QLength);
QUANTITY_TYPE(0, 2, 0, 0, QArea);
QUANTITY_TYPE(0, 3, 0, 0, QVolume);
QUANTITY_TYPE(0, 0, 1, 0, QTime);
QUANTITY_TYPE(0, 1, -1, 0, QSpeed);
QUANTITY_TYPE(0, 1, -2, 0, QAcceleration);
QUANTITY_TYPE(0, 1, -3, 0, QJerk);
QUANTITY_TYPE(0, 0, -1, 0, QFrequency);
QUANTITY_TYPE(1, 1, -2, 0, QForce);
QUANTITY_TYPE(1, -1, -2, 0, QPressure);
QUANTITY_TYPE(0, 0, 0, 1, Angle);
*/

// Predefined (physical unit) quantity types:
// ------------------------------------------
#define QUANTITY_TYPE(_Mdim, _Ldim, _Tdim, _Adim, name)                        \
  typedef RQuantity<std::ratio<_Mdim>, std::ratio<_Ldim>, std::ratio<_Tdim>,   \
                    std::ratio<_Adim>>                                         \
      name;

// Unitless
QUANTITY_TYPE(0, 0, 0, 0, Number)
constexpr Number number(1.0);

// Standard arithmetic operators:
// ------------------------------

// Addition
template <typename M, typename L, typename T, typename A>
constexpr RQuantity<M, L, T, A> operator+(const RQuantity<M, L, T, A> &lhs,
                                          const RQuantity<M, L, T, A> &rhs) {
  return RQuantity<M, L, T, A>(lhs.getValue() + rhs.getValue());
}
// Subtraction
template <typename M, typename L, typename T, typename A>
constexpr RQuantity<M, L, T, A> operator-(const RQuantity<M, L, T, A> &lhs,
                                          const RQuantity<M, L, T, A> &rhs) {
  return RQuantity<M, L, T, A>(lhs.getValue() - rhs.getValue());
}
// Multiplication
template <typename M1, typename L1, typename T1, typename A1, typename M2,
          typename L2, typename T2, typename A2>
constexpr RQuantity<std::ratio_add<M1, M2>, std::ratio_add<L1, L2>,
                    std::ratio_add<T1, T2>, std::ratio_add<A1, A2>>
operator*(const RQuantity<M1, L1, T1, A1> &lhs,
          const RQuantity<M2, L2, T2, A2> &rhs) {
  return RQuantity<std::ratio_add<M1, M2>, std::ratio_add<L1, L2>,
                   std::ratio_add<T1, T2>, std::ratio_add<A1, A2>>(
      lhs.getValue() * rhs.getValue());
}
template <typename M, typename L, typename T, typename A>
constexpr RQuantity<M, L, T, A> operator*(const double &lhs,
                                          const RQuantity<M, L, T, A> &rhs) {
  return RQuantity<M, L, T, A>(lhs * rhs.getValue());
}
template <typename M, typename L, typename T, typename A>
constexpr RQuantity<M, L, T, A> operator*(const RQuantity<M, L, T, A> &lhs,
                                          const double &rhs) {
  return RQuantity<M, L, T, A>(lhs.getValue() * rhs);
}
// Division
template <typename M1, typename L1, typename T1, typename A1, typename M2,
          typename L2, typename T2, typename A2>
constexpr RQuantity<std::ratio_subtract<M1, M2>, std::ratio_subtract<L1, L2>,
                    std::ratio_subtract<T1, T2>, std::ratio_subtract<A1, A2>>
operator/(const RQuantity<M1, L1, T1, A1> &lhs,
          const RQuantity<M2, L2, T2, A2> &rhs) {
  return RQuantity<std::ratio_subtract<M1, M2>, std::ratio_subtract<L1, L2>,
                   std::ratio_subtract<T1, T2>, std::ratio_subtract<A1, A2>>(
      lhs.getValue() / rhs.getValue());
}
template <typename M, typename L, typename T, typename A>
constexpr RQuantity<std::ratio_subtract<std::ratio<0>, M>,
                    std::ratio_subtract<std::ratio<0>, L>,
                    std::ratio_subtract<std::ratio<0>, T>,
                    std::ratio_subtract<std::ratio<0>, A>>
operator/(const double &x, const RQuantity<M, L, T, A> &rhs) {
  return RQuantity<std::ratio_subtract<std::ratio<0>, M>,
                   std::ratio_subtract<std::ratio<0>, L>,
                   std::ratio_subtract<std::ratio<0>, T>,
                   std::ratio_subtract<std::ratio<0>, A>>(x / rhs.getValue());
}
template <typename M, typename L, typename T, typename A>
constexpr RQuantity<M, L, T, A> operator/(const RQuantity<M, L, T, A> &rhs,
                                          const double &x) {
  return RQuantity<M, L, T, A>(rhs.getValue() / x);
}

// Comparison operators for quantities:
// ------------------------------------

// Equal To
template <typename M, typename L, typename T, typename A>
constexpr bool operator==(const RQuantity<M, L, T, A> &lhs,
                          const RQuantity<M, L, T, A> &rhs) {
  return (lhs.getValue() == rhs.getValue());
}
// Not Equal To
template <typename M, typename L, typename T, typename A>
constexpr bool operator!=(const RQuantity<M, L, T, A> &lhs,
                          const RQuantity<M, L, T, A> &rhs) {
  return (lhs.getValue() != rhs.getValue());
}
// Less Than or Equal To
template <typename M, typename L, typename T, typename A>
constexpr bool operator<=(const RQuantity<M, L, T, A> &lhs,
                          const RQuantity<M, L, T, A> &rhs) {
  return (lhs.getValue() <= rhs.getValue());
}
// Greater Than or Equal To
template <typename M, typename L, typename T, typename A>
constexpr bool operator>=(const RQuantity<M, L, T, A> &lhs,
                          const RQuantity<M, L, T, A> &rhs) {
  return (lhs.getValue() >= rhs.getValue());
}
// Less Than
template <typename M, typename L, typename T, typename A>
constexpr bool operator<(const RQuantity<M, L, T, A> &lhs,
                         const RQuantity<M, L, T, A> &rhs) {
  return (lhs.getValue() < rhs.getValue());
}
// Greater Than
template <typename M, typename L, typename T, typename A>
constexpr bool operator>(const RQuantity<M, L, T, A> &lhs,
                         const RQuantity<M, L, T, A> &rhs) {
  return (lhs.getValue() > rhs.getValue());
}
template <typename M, typename L, typename T, typename A>
constexpr RQuantity<M, L, T, A> abs(const RQuantity<M, L, T, A> &rhs) {
  return RQuantity<M, L, T, A>(std::abs(rhs.getValue()));
}

template <typename R, typename M, typename L, typename T, typename A>
constexpr RQuantity<std::ratio_multiply<M, R>, std::ratio_multiply<L, R>,
                    std::ratio_multiply<T, R>, std::ratio_multiply<A, R>>
pow(const RQuantity<M, L, T, A> &lhs) {
  return RQuantity<std::ratio_multiply<M, R>, std::ratio_multiply<L, R>,
                   std::ratio_multiply<T, R>, std::ratio_multiply<A, R>>(
      std::pow(lhs.getValue(), double(R::num) / R::den));
}

template <int R, typename M, typename L, typename T, typename A>
constexpr RQuantity<std::ratio_multiply<M, std::ratio<R>>,
                    std::ratio_multiply<L, std::ratio<R>>,
                    std::ratio_multiply<T, std::ratio<R>>,
                    std::ratio_multiply<A, std::ratio<R>>>
pow(const RQuantity<M, L, T, A> &lhs) {
  return RQuantity<std::ratio_multiply<M, std::ratio<R>>,
                   std::ratio_multiply<L, std::ratio<R>>,
                   std::ratio_multiply<T, std::ratio<R>>,
                   std::ratio_multiply<A, std::ratio<R>>>(
      std::pow(lhs.getValue(), R));
}

template <int R, typename M, typename L, typename T, typename A>
constexpr RQuantity<
    std::ratio_divide<M, std::ratio<R>>, std::ratio_divide<L, std::ratio<R>>,
    std::ratio_divide<T, std::ratio<R>>, std::ratio_divide<A, std::ratio<R>>>
root(const RQuantity<M, L, T, A> &lhs) {
  return RQuantity<
      std::ratio_divide<M, std::ratio<R>>, std::ratio_divide<L, std::ratio<R>>,
      std::ratio_divide<T, std::ratio<R>>, std::ratio_divide<A, std::ratio<R>>>(
      std::pow(lhs.getValue(), 1.0 / R));
}

template <typename M, typename L, typename T, typename A>
constexpr RQuantity<
    std::ratio_divide<M, std::ratio<2>>, std::ratio_divide<L, std::ratio<2>>,
    std::ratio_divide<T, std::ratio<2>>, std::ratio_divide<A, std::ratio<2>>>
sqrt(const RQuantity<M, L, T, A> &rhs) {
  return RQuantity<
      std::ratio_divide<M, std::ratio<2>>, std::ratio_divide<L, std::ratio<2>>,
      std::ratio_divide<T, std::ratio<2>>, std::ratio_divide<A, std::ratio<2>>>(
      std::sqrt(rhs.getValue()));
}

template <typename M, typename L, typename T, typename A>
constexpr RQuantity<
    std::ratio_divide<M, std::ratio<3>>, std::ratio_divide<L, std::ratio<3>>,
    std::ratio_divide<T, std::ratio<3>>, std::ratio_divide<A, std::ratio<3>>>
cbrt(const RQuantity<M, L, T, A> &rhs) {
  return RQuantity<
      std::ratio_divide<M, std::ratio<3>>, std::ratio_divide<L, std::ratio<3>>,
      std::ratio_divide<T, std::ratio<3>>, std::ratio_divide<A, std::ratio<3>>>(
      std::cbrt(rhs.getValue()));
}

template <typename M, typename L, typename T, typename A>
constexpr RQuantity<std::ratio_multiply<M, std::ratio<2>>,
                    std::ratio_multiply<L, std::ratio<2>>,
                    std::ratio_multiply<T, std::ratio<2>>,
                    std::ratio_multiply<A, std::ratio<2>>>
square(const RQuantity<M, L, T, A> &rhs) {
  return RQuantity<std::ratio_multiply<M, std::ratio<2>>,
                   std::ratio_multiply<L, std::ratio<2>>,
                   std::ratio_multiply<T, std::ratio<2>>,
                   std::ratio_multiply<A, std::ratio<2>>>(
      std::pow(rhs.getValue(), 2));
}

template <typename M, typename L, typename T, typename A>
constexpr RQuantity<std::ratio_multiply<M, std::ratio<3>>,
                    std::ratio_multiply<L, std::ratio<3>>,
                    std::ratio_multiply<T, std::ratio<3>>,
                    std::ratio_multiply<A, std::ratio<3>>>
cube(const RQuantity<M, L, T, A> &rhs) {
  return RQuantity<std::ratio_multiply<M, std::ratio<3>>,
                   std::ratio_multiply<L, std::ratio<3>>,
                   std::ratio_multiply<T, std::ratio<3>>,
                   std::ratio_multiply<A, std::ratio<3>>>(
      std::pow(rhs.getValue(), 3));
}

template <typename M, typename L, typename T, typename A>
constexpr RQuantity<M, L, T, A> hypot(const RQuantity<M, L, T, A> &lhs,
                                      const RQuantity<M, L, T, A> &rhs) {
  return RQuantity<M, L, T, A>(std::hypot(lhs.getValue(), rhs.getValue()));
}

template <typename M, typename L, typename T, typename A>
constexpr RQuantity<M, L, T, A> mod(const RQuantity<M, L, T, A> &lhs,
                                    const RQuantity<M, L, T, A> &rhs) {
  return RQuantity<M, L, T, A>(std::fmod(lhs.getValue(), rhs.getValue()));
}

template <typename M1, typename L1, typename T1, typename A1, typename M2,
          typename L2, typename T2, typename A2>
constexpr RQuantity<M1, L1, T1, A1>
copysign(const RQuantity<M1, L1, T1, A1> &lhs,
         const RQuantity<M2, L2, T2, A2> &rhs) {
  return RQuantity<M1, L1, T1, A1>(
      std::copysign(lhs.getValue(), rhs.getValue()));
}

template <typename M, typename L, typename T, typename A>
constexpr RQuantity<M, L, T, A> ceil(const RQuantity<M, L, T, A> &lhs,
                                     const RQuantity<M, L, T, A> &rhs) {
  return RQuantity<M, L, T, A>(std::ceil(lhs.getValue() / rhs.getValue()) *
                               rhs.getValue());
}

template <typename M, typename L, typename T, typename A>
constexpr RQuantity<M, L, T, A> floor(const RQuantity<M, L, T, A> &lhs,
                                      const RQuantity<M, L, T, A> &rhs) {
  return RQuantity<M, L, T, A>(std::floor(lhs.getValue() / rhs.getValue()) *
                               rhs.getValue());
}

template <typename M, typename L, typename T, typename A>
constexpr RQuantity<M, L, T, A> trunc(const RQuantity<M, L, T, A> &lhs,
                                      const RQuantity<M, L, T, A> &rhs) {
  return RQuantity<M, L, T, A>(std::trunc(lhs.getValue() / rhs.getValue()) *
                               rhs.getValue());
}

template <typename M, typename L, typename T, typename A>
constexpr RQuantity<M, L, T, A> round(const RQuantity<M, L, T, A> &lhs,
                                      const RQuantity<M, L, T, A> &rhs) {
  return RQuantity<M, L, T, A>(std::round(lhs.getValue() / rhs.getValue()) *
                               rhs.getValue());
}

// Common trig functions:
// ------------------------------

constexpr Number sin(const RQuantity<std::ratio<0>, std::ratio<0>,
                                     std::ratio<0>, std::ratio<1>> &rhs) {
  return Number(std::sin(rhs.getValue()));
}

constexpr Number cos(const RQuantity<std::ratio<0>, std::ratio<0>,
                                     std::ratio<0>, std::ratio<1>> &rhs) {
  return Number(std::cos(rhs.getValue()));
}

constexpr Number tan(const RQuantity<std::ratio<0>, std::ratio<0>,
                                     std::ratio<0>, std::ratio<1>> &rhs) {
  return Number(std::tan(rhs.getValue()));
}

constexpr RQuantity<std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<1>>
asin(const Number &rhs) {
  return RQuantity<std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<1>>(
      std::asin(rhs.getValue()));
}

constexpr RQuantity<std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<1>>
acos(const Number &rhs) {
  return RQuantity<std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<1>>(
      std::acos(rhs.getValue()));
}

constexpr RQuantity<std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<1>>
atan(const Number &rhs) {
  return RQuantity<std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<1>>(
      std::atan(rhs.getValue()));
}

constexpr Number sinh(const RQuantity<std::ratio<0>, std::ratio<0>,
                                      std::ratio<0>, std::ratio<1>> &rhs) {
  return Number(std::sinh(rhs.getValue()));
}

constexpr Number cosh(const RQuantity<std::ratio<0>, std::ratio<0>,
                                      std::ratio<0>, std::ratio<1>> &rhs) {
  return Number(std::cosh(rhs.getValue()));
}

constexpr Number tanh(const RQuantity<std::ratio<0>, std::ratio<0>,
                                      std::ratio<0>, std::ratio<1>> &rhs) {
  return Number(std::tanh(rhs.getValue()));
}

constexpr RQuantity<std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<1>>
asinh(const Number &rhs) {
  return RQuantity<std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<1>>(
      std::asinh(rhs.getValue()));
}

constexpr RQuantity<std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<1>>
acosh(const Number &rhs) {
  return RQuantity<std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<1>>(
      std::acosh(rhs.getValue()));
}

constexpr RQuantity<std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<1>>
atanh(const Number &rhs) {
  return RQuantity<std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<1>>(
      std::atanh(rhs.getValue()));
}

template <typename M, typename L, typename T, typename A>
constexpr RQuantity<std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<1>>
atan2(const RQuantity<M, L, T, A> &lhs, const RQuantity<M, L, T, A> &rhs) {
  return RQuantity<std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<1>>(
      std::atan2(lhs.getValue(), rhs.getValue()));
}

inline namespace literals {
constexpr long double operator"" _pi(long double x) {
  return static_cast<double>(x) * 3.1415926535897932384626433832795;
}
constexpr long double operator"" _pi(unsigned long long int x) {
  return static_cast<double>(x) * 3.1415926535897932384626433832795;
}
} // namespace literals
} // namespace apollo

// Conversion macro, which utilizes the string literals
#define ConvertTo(_x, _y) (_x).Convert(1.0_##_y)