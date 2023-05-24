#pragma once
#include "apollo/units/QSpeed.hpp"
#include "apollo/units/QTime.hpp"
#include "pros/motors.h"
namespace apollo {
class Chassis {
 public:
  explicit Chassis() = default;
  Chassis(const Chassis&) = delete;
  Chassis& operator=(const Chassis&) = delete;
  void setGearRatio(double ratio);
  void setDriveVelocity(double velocity, QSpeed units);
  void setTurnVelocity(double velocity, QSpeed units);
  void setTimeout(int32_t time, QTime units);
  void setActiveBrake(pros::motor_brake_mode_e_t mode);
  void setStoppingBrake(pros::motor_brake_mode_e_t mode);
  void resetRotation();
  void resetEncoders();
  void setRotation();
  void setEncoder();
  void spin( )
};
}  // namespace apollo