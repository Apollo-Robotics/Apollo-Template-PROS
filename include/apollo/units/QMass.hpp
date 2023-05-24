/*
 * This code is a modified version of Benjamin Jurke's work in 2015. You can read his blog post
 * here:
 * https://benjaminjurke.com/content/articles/2015/compile-time-numerical-unit-dimension-checking/
 */
#pragma once

#include "apollo/units/RQuantity.hpp"

namespace apollo {
QUANTITY_TYPE(1, 0, 0, 0, QMass)

constexpr QMass kg(1.0);  // SI base unit
constexpr QMass gramme = 0.001 * kg;
constexpr QMass tonne = 1000 * kg;
constexpr QMass ounce = 0.028349523125 * kg;
constexpr QMass pound = 16 * ounce;
constexpr QMass stone = 14 * pound;

inline namespace literals {
constexpr QMass operator"" _kg(long double x) {
  return QMass(x);
}
constexpr QMass operator"" _g(long double x) {
  return static_cast<double>(x) * gramme;
}
constexpr QMass operator"" _t(long double x) {
  return static_cast<double>(x) * tonne;
}
constexpr QMass operator"" _oz(long double x) {
  return static_cast<double>(x) * ounce;
}
constexpr QMass operator"" _lb(long double x) {
  return static_cast<double>(x) * pound;
}
constexpr QMass operator"" _st(long double x) {
  return static_cast<double>(x) * stone;
}
constexpr QMass operator"" _kg(unsigned long long int x) {
  return QMass(static_cast<double>(x));
}
constexpr QMass operator"" _g(unsigned long long int x) {
  return static_cast<double>(x) * gramme;
}
constexpr QMass operator"" _t(unsigned long long int x) {
  return static_cast<double>(x) * tonne;
}
constexpr QMass operator"" _oz(unsigned long long int x) {
  return static_cast<double>(x) * ounce;
}
constexpr QMass operator"" _lb(unsigned long long int x) {
  return static_cast<double>(x) * pound;
}
constexpr QMass operator"" _st(unsigned long long int x) {
  return static_cast<double>(x) * stone;
}
}  // namespace literals
}  // namespace apollo