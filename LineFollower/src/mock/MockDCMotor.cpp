#include "MockDCMotor.h"

MockDCMotor::MockDCMotor() : speed(0), direction(0) {}

void MockDCMotor::setSpeed(int speed) {
    // Set the speed
    this->speed = speed;
}

int MockDCMotor::getSpeed() const {
    // Return the speed
    return this->speed;
}

void MockDCMotor::setDirection(int direction) {
    // Set the direction
    this->direction = direction;
}

int MockDCMotor::getDirection() const {
    // Return the direction
    return this->direction;
}

void MockDCMotor::stop() {
    // Stop the motor
    this->speed = 0;
    this->direction = 0;
}