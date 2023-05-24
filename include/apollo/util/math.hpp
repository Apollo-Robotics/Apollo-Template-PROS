#pragma once
#include <cstdint>
#include <math.h>
namespace apollo {
static constexpr double mm_in_in = 25.4;
static constexpr double in_in_mm = 0.0393700787;
static constexpr std::int32_t v5_red_gearset_ticks = 1800;
static constexpr std::int32_t v5_green_gearset_ticks = 900;
static constexpr std::int32_t v5_blue_gearset_ticks = 300;
static constexpr double v5_motor_max_voltage = 12000;
static constexpr std::int8_t v5_motor_update_rate = 10;
static constexpr std::int32_t adi_quad_encoder_ticks = 360;
static constexpr std::int8_t adi_update_rate = 10;
constexpr double in_to_mm(double inches) { return inches * mm_in_in; };
constexpr double mm_to_in(double millimeters) { return millimeters / mm_in_in; }
constexpr double degrees_to_radians(double degrees) {
  return (M_PI / 180) * degrees;
}
constexpr double radians_to_degrees(double radians) {
  return (180 / M_PI) * radians;
}
constexpr std::int8_t conver_adi_port(const std::int8_t adi_port) {
  if (adi_port >= 'a' && adi_port <= 'h') {
    return adi_port - ('a' - 1);
  } else if (adi_port >= 'A' && adi_port <= 'H') {
    return adi_port - ('A' - 1);
  } else {
    return adi_port;
  }
}
} // namespace apollo