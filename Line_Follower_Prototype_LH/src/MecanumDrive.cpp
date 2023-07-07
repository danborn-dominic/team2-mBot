// MecanumDrive.cpp

#include "MecanumDrive.h"

MecanumDrive::MecanumDrive(uint8_t& motorFLPort, uint8_t motorFRPort, uint8_t motorRLPOort, MotorController& motorRR)
    : motorFL_(motorFL), motorFR_(motorFR), motorRL_(motorRL), motorRR_(motorRR) {}

void MecanumDrive::drive(double forwardSpeed, double strafeSpeed, double rotationalSpeed) {
    double flSpeed = forwardSpeed + strafeSpeed + rotationalSpeed;
    double frSpeed = forwardSpeed - strafeSpeed - rotationalSpeed;
    double rlSpeed = forwardSpeed - strafeSpeed + rotationalSpeed;
    double rrSpeed = forwardSpeed + strafeSpeed - rotationalSpeed;

    motorFL.setSpeed(flSpeed);
    motorFR.setSpeed(frSpeed);
    motorRL.setSpeed(rlSpeed);
    motorRR.setSpeed(rrSpeed);
}

void MecanumDrive::drive(double flMotorSpeed, double frMotorSpeed, double rlMotorSpeed, double rrMotorSpeed) {
    motorFL.setSpeed(flMotorSpeed);
    motorFR.setSpeed(frMotorSpeed);
    motorRL.setSpeed(rlMotorSpeed);
    motorRR.setSpeed(rrMotorSpeed);
}

void MecanumDrive::stop() {
    motorFL.stop();
    motorFR.stop();
    motorRL.stop();
    motorRR.stop();
}

void MecanumDrive::setSpeed(double speed) {
    int intSpeed = staticcast<int>(speed * 255);
    if (intSpeed > 255) 
        intSpeed = 255;
    else if (intSpeed < -255) 
        intSpeed = -255;

    motor.run(intSpeed);
}