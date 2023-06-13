#pragma once

#include "apollo/chassis/chassis.hpp"
#include "pros/adi.hpp"
#include "pros/imu.hpp"
#include "pros/motors.hpp"
#include "pros/rotation.hpp"

namespace apollo {
class Tank : public Chassis {
 public:
  Tank(std::vector<int> leftDriveMotorPorts,
       std::vector<int> rightDriveMotorPorts, int inertialSensorPort,
       double cartridgeRPM, double gearRatio, double wheelDiameter);
  Tank(std::vector<int> leftDriveMotorPorts,
       std::vector<int> rightDriveMotorPorts, int inertialSensorPort,
       double cartridgeRPM, double gearRatio, double wheelDiameter,
       std::vector<int> leftEncoderTrackerPorts,
       std::vector<int> rightEncoderTrackerPorts);
  Tank(std::vector<int> leftDriveMotorPorts,
       std::vector<int> rightDriveMotorPorts, int inertialSensorPort,
       double cartridgeRPM, double gearRatio, double wheelDiameter,
       std::vector<int> leftEncoderTrackerPorts,
       std::vector<int> rightEncoderTrackerPorts,
       std::vector<int> centerEncoderTrackerPorts);
  Tank(std::vector<int> leftDriveMotorPorts,
       std::vector<int> rightDriveMotorPorts, int inertialSensorPort,
       double cartridgeRPM, int leftRotationTrackerPorts,
       int rightRotationTrackerPorts);
  Tank(std::vector<int> leftDriveMotorPorts,
       std::vector<int> rightDriveMotorPorts, int inertialSensorPort,
       double cartridgeRPM, int leftRotationTrackerPorts,
       int rightRotationTrackerPorts, int centerRotationTrackerPorts);

 protected:
  std::vector<pros::Motor> leftDriveMotors;
  std::vector<pros::Motor> rightDriveMotors;
  pros::Imu inertialSensor;
  pros::ADIEncoder leftEncoderTracker = pros::ADIEncoder(-1, -1, -1);
  pros::ADIEncoder rightEncoderTracker = pros::ADIEncoder(-1, -1, -1);
  pros::ADIEncoder centerEncoderTracker = pros::ADIEncoder(-1, -1, -1);
  pros::Rotation leftRotationTracker = pros::Rotation(-1);
  pros::Rotation rightRotationTracker = pros::Rotation(-1);
  pros::Rotation centerRotationTracker = pros::Rotation(-1);
  int trackerType;
  int chassisType;
  double drivetrainCartridgeRPMS = 0;
  double drivetrainGearRatio = 0;
  double drivetrainWheelDiameter = 0;
  double drivetrainWheelCircumference = 0;
  double trackerTickPerInch = 0;
  double trackerTickPerRevolution = 0;
  double trackerGearRatio = 0;
  double trackerWheelDiameter = 0;
  double trackerWheelCircumference = 0;
};
}  // namespace apollo