/*
 * This code is a modified version of Benjamin Jurke's work in 2015. You can read his blog post
 * here:
 * https://benjaminjurke.com/content/articles/2015/compile-time-numerical-unit-dimension-checking/
 */
#pragma once

#include "apollo/units/RQuantity.hpp"

namespace apollo {
QUANTITY_TYPE(0, 0, -1, 0, QFrequency)

constexpr QFrequency Hz(1.0);

inline namespace literals {
constexpr QFrequency operator"" _Hz(long double x) {
  return QFrequency(x);
}
constexpr QFrequency operator"" _Hz(unsigned long long int x) {
  return QFrequency(static_cast<long double>(x));
}
}  // namespace literals
}  // namespace apollo