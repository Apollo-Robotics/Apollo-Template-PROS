#pragma once
#include "apollo/units/QDirection.hpp"
#include "pros/misc.h"
#include "pros/motors.h"
using namespace pros;
namespace apollo {
class Chassis {
 public:
  enum chassisType {
    tank_drive = 1,
    x_drive = 2,
    asterisk_drive = 3,
    mechanum_drive = 4,
    h_drive = 5
  };
  enum trackerType {
    tracker_motor_integrated = 1,
    tracker_encoder_wheel = 2,
    tracker_rotation_wheel = 3
  };
  virtual void resetSensors() = 0;
  virtual void setBrakeMode(motor_brake_mode_e_t mode) = 0;
  virtual void setGearing(double gearing) = 0;
  virtual void setEncoderUnits(double units) = 0;
  virtual void setMaxVelocity(double velocity) = 0;
  virtual void setMaxVoltage(double voltage) = 0;
  virtual void setDrivePID(double targetDistance, double targetVelocity) = 0;
  virtual void setTurnPID(double targetAngle, double targetVelocity) = 0;
  virtual void setSwingPID(direction targetDirection, double targetAngle,
                           double targetVelocity) = 0;
  virtual void setTank(controller_analog_e_t leftAxis,
                       controller_analog_e_t rightAxis,
                       controller_analog_e_t* strafeAxis) = 0;
  virtual void setArcade(controller_analog_e_t leftAxis,
                         controller_analog_e_t rightAxis,
                         controller_analog_e_t* strafeAxis) = 0;
  virtual motor_gearset_e_t getBrakeMode() const = 0;
  virtual double getGearing() const = 0;
  virtual double getEncoderUnits() const = 0;
  virtual double getMaxVelocity() const = 0;
  virtual double getMaxVoltage() const = 0;
};
}  // namespace apollo