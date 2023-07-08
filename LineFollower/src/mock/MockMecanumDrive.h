#ifndef MECANUM_DRIVE_H
#define MECANUM_DRIVE_H

// As long as other library is installed it should work fine
#include "MockDCMotor.h"

class MockMecanumDrive {
public:
    MockMecanumDrive(MockDCMotor& motorFL, MockDCMotor& motorFR, MockDCMotor& motorRL, MockDCMotor& motorRR);
    // Takes in forward, strafe, and rotational speeds from -1 to 1
    void drive(double forwardSpeed, double strafeSpeed, double rotationalSpeed);
    // Takes in motor speeds from -1 to 1
    void drive(double flMotorSpeed, double frMotorSpeed, double rlMotorSpeed, double rrMotorSpeed);
    // Stops all motors
    void stop();

private:
    // Changes speed to be a value from -1 to 1
    int normalization(double speed);
    MockDCMotor& motorFL_;
    MockDCMotor& motorFR_;
    MockDCMotor& motorRL_;
    MockDCMotor& motorRR_;
};

#endif // MECANUM_DRIVE_H