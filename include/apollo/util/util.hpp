#pragma once
#include <cstdint>

#include "pros/misc.h"
#include "pros/misc.hpp"

const pros::Controller master(pros::E_CONTROLLER_MASTER);
const pros::Controller partner(pros::E_CONTROLLER_PARTNER);
namespace apollo::util {
constexpr int sign(double inputValue) {
  if (inputValue > 0) {
    return 1;
  } else if (inputValue < 0) {
    return -1;
  }
  return 0;
}
constexpr bool isNegative(double inputValue) {
  if (inputValue > 0) {
    return false;
  } else if (inputValue < 0) {
    return true;
  }
  return false;
}
constexpr std::int8_t convert_adi_port(const std::int8_t adi_port) {
  if (adi_port >= 'a' && adi_port <= 'h') {
    return adi_port - ('a' - 1);
  } else if (adi_port >= 'A' && adi_port <= 'H') {
    return adi_port - ('A' - 1);
  } else {
    return adi_port;
  }
}
}  // namespace apollo::util