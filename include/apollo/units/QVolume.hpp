/*
 * This code is a modified version of Benjamin Jurke's work in 2015. You can read his blog post
 * here:
 * https://benjaminjurke.com/content/articles/2015/compile-time-numerical-unit-dimension-checking/
 */
#pragma once

#include "apollo/units/QArea.hpp"
#include "apollo/units/QLength.hpp"
#include "apollo/units/RQuantity.hpp"

namespace apollo {
QUANTITY_TYPE(0, 3, 0, 0, QVolume)

constexpr QVolume kilometer3 = kilometer2 * kilometer;
constexpr QVolume meter3 = meter2 * meter;
constexpr QVolume decimeter3 = decimeter2 * decimeter;
constexpr QVolume centimeter3 = centimeter2 * centimeter;
constexpr QVolume millimeter3 = millimeter2 * millimeter;
constexpr QVolume inch3 = inch2 * inch;
constexpr QVolume foot3 = foot2 * foot;
constexpr QVolume mile3 = mile2 * mile;
constexpr QVolume litre = decimeter3;
}  // namespace apollo