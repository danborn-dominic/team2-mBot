// MecanumDrive.h

#ifndef MECANUM_DRIVE_H
#define MECANUM_DRIVE_H

#include <MeMegaPiDCMotor.h>

class MecanumDrive {
public:
    MecanumDrive(MeMegaPiDCMotor& motorFL, MeMegaPiDCMotor& motorFR, MeMegaPiDCMotor& motorRL, MeMegaPiDCMotor& motorRR);
    // Takes in forward, strafe, and rotational speeds from -1 to 1
    void drive(double forwardSpeed, double strafeSpeed, double rotationalSpeed);
    // Takes in motor speeds from -1 to 1
    void drive(double flMotorSpeed, double frMotorSpeed, double rlMotorSpeed, double rrMotorSpeed);
    // Stops all motors
    void stop();

private:
    // Changes speed to be a value from -1 to 1
    void setSpeed(double speed);
    MeMegaPiDCMotor& motorFL_;
    MeMegaPiDCMotor& motorFR_;
    MeMegaPiDCMotor& motorRL_;
    MeMegaPiDCMotor& motorRR_;
};

#endif // MECANUM_DRIVE_H