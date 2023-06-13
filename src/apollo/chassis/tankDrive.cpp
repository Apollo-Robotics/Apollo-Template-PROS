#include "apollo/chassis/tankDrive.hpp"

#include "apollo/util/util.hpp"
#include "pros/motors.hpp"

namespace apollo {
Tank::Tank(std::vector<int> leftDriveMotorPorts,
           std::vector<int> rightDriveMotorPorts, int inertialSensorPort,
           double cartridgeRPM, double gearRatio, double wheelDiameter)
    : inertialSensor(inertialSensorPort) {
  for (auto i : leftDriveMotorPorts) {
    leftDriveMotors.push_back(pros::Motor(std::abs(i), util::isNegative(i)));
  }
  for (auto i : rightDriveMotorPorts) {
    rightDriveMotors.push_back(pros::Motor(std::abs(i), util::isNegative(i)));
  }
  trackerType = tracker_motor_integrated;
  chassisType = tank_drive;
  drivetrainCartridgeRPMS = cartridgeRPM;
  drivetrainGearRatio = gearRatio;
  drivetrainWheelDiameter = wheelDiameter;
  drivetrainWheelCircumference = drivetrainWheelCircumference * M_PI;
  trackerTickPerInch = 0;
  trackerTickPerRevolution = 0;
  trackerGearRatio = drivetrainGearRatio;
  trackerWheelDiameter = drivetrainWheelDiameter;
  trackerWheelCircumference = drivetrainWheelCircumference;
}
Tank::Tank(std::vector<int> leftDriveMotorPorts,
           std::vector<int> rightDriveMotorPorts, int inertialSensorPort,
           double cartridgeRPM, double gearRatio, double wheelDiameter,
           std::vector<int> leftEncoderTrackerPorts,
           std::vector<int> rightEncoderTrackerPorts);
Tank::Tank(std::vector<int> leftDriveMotorPorts,
           std::vector<int> rightDriveMotorPorts, int inertialSensorPort,
           double cartridgeRPM, double gearRatio, double wheelDiameter,
           std::vector<int> leftEncoderTrackerPorts,
           std::vector<int> rightEncoderTrackerPorts,
           std::vector<int> centerEncoderTrackerPorts);
Tank::Tank(std::vector<int> leftDriveMotorPorts,
           std::vector<int> rightDriveMotorPorts, int inertialSensorPort,
           double cartridgeRPM, int leftRotationTrackerPorts,
           int rightRotationTrackerPorts);
Tank::Tank(std::vector<int> leftDriveMotorPorts,
           std::vector<int> rightDriveMotorPorts, int inertialSensorPort,
           double cartridgeRPM, int leftRotationTrackerPorts,
           int rightRotationTrackerPorts, int centerRotationTrackerPorts);

}  // namespace apollo