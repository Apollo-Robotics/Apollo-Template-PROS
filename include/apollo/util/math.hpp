#pragma once
#include <math.h>
namespace apollo::math {
constexpr double degreesToRadians(double degrees) {
  return (M_PI / 180) * degrees;
}
constexpr double radiansToDegrees(double radians) {
  return (180 / M_PI) * radians;
}
constexpr double slew(double targetValue, double currentValue,
                      double maxChange) {
  double change = targetValue - currentValue;
  if (maxChange == 0) {
    return targetValue;
  } else if (change > maxChange) {
    change = maxChange;
  } else if (change < -maxChange) {
    change = -maxChange;
  }
  return currentValue + change;
}
constexpr double clipValues(double inputValue, double maxiumValue,
                            double minimumValue) {
  if (inputValue > maxiumValue) {
    return maxiumValue;
  } else if (inputValue < minimumValue) {
    return minimumValue;
  }
  return inputValue;
}
}  // namespace apollo::math