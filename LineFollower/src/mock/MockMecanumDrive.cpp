#include "MockMecanumDrive.h"

MockMecanumDrive::MockMecanumDrive(MockDCMotor& motorFL, MockDCMotor& motorFR, MockDCMotor& motorRL, MockDCMotor& motorRR)
    : motorFL_(motorFL), motorFR_(motorFR), motorRL_(motorRL), motorRR_(motorRR) {}

void MockMecanumDrive::drive(double forwardSpeed, double strafeSpeed, double rotationalSpeed) {
    double flSpeed = forwardSpeed + strafeSpeed + rotationalSpeed;
    double frSpeed = forwardSpeed - strafeSpeed - rotationalSpeed;
    double rlSpeed = forwardSpeed - strafeSpeed + rotationalSpeed;
    double rrSpeed = forwardSpeed + strafeSpeed - rotationalSpeed;

    motorFL_.setSpeed(normalization(flSpeed));
    motorFR_.setSpeed(normalization(frSpeed));
    motorRL_.setSpeed(normalization(rlSpeed));
    motorRR_.setSpeed(normalization(rrSpeed));
}

void MockMecanumDrive::drive(double flMotorSpeed, double frMotorSpeed, double rlMotorSpeed, double rrMotorSpeed) {
    motorFL_.setSpeed(normalization(flMotorSpeed));
    motorFR_.setSpeed(normalization(frMotorSpeed));
    motorRL_.setSpeed(normalization(rlMotorSpeed));
    motorRR_.setSpeed(normalization(rrMotorSpeed));
}

void MockMecanumDrive::stop() {
    motorFL_.stop();
    motorFR_.stop();
    motorRL_.stop();
    motorRR_.stop();
}

int MockMecanumDrive::normalization(double speed) {
    int intSpeed = static_cast<int>(speed * 255);
    if (intSpeed > 255) 
        intSpeed = 255;
    else if (intSpeed < -255) 
        intSpeed = -255;
    return intSpeed;
}