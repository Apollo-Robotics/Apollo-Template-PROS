/*
 * This code is a modified version of Benjamin Jurke's work in 2015. You can read his blog post
 * here:
 * https://benjaminjurke.com/content/articles/2015/compile-time-numerical-unit-dimension-checking/
 */
#pragma once

#include "apollo/units/RQuantity.hpp"
namespace apollo {
enum direction { FORWARD = 0,
                 FWD = FORWARD,
                 REVERSE = 1,
                 REV = REVERSE,
                 LEFT = 2,
                 L = LEFT,
                 RIGHT = 3,
                 R = RIGHT };
}