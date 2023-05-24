/*
 * This code is a modified version of Benjamin Jurke's work in 2015. You can read his blog post
 * here:
 * https://benjaminjurke.com/content/articles/2015/compile-time-numerical-unit-dimension-checking/
 */
#pragma once

#include "apollo/units/QLength.hpp"
#include "apollo/units/QTime.hpp"
#include "apollo/units/RQuantity.hpp"

namespace apollo {
QUANTITY_TYPE(0, 1, -1, 0, QSpeed)

constexpr QSpeed mps = meter / second;
constexpr QSpeed miph = mile / hour;
constexpr QSpeed kmph = kilometer / hour;

inline namespace literals {
constexpr QSpeed operator"" _mps(long double x) {
  return static_cast<double>(x) * mps;
}
constexpr QSpeed operator"" _miph(long double x) {
  return static_cast<double>(x) * mile / hour;
}
constexpr QSpeed operator"" _kmph(long double x) {
  return static_cast<double>(x) * kilometer / hour;
}
constexpr QSpeed operator"" _mps(unsigned long long int x) {
  return static_cast<double>(x) * mps;
}
constexpr QSpeed operator"" _miph(unsigned long long int x) {
  return static_cast<double>(x) * mile / hour;
}
constexpr QSpeed operator"" _kmph(unsigned long long int x) {
  return static_cast<double>(x) * kilometer / hour;
}
}  // namespace literals
}  // namespace apollo