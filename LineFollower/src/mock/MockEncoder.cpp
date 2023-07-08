#include "MockEncoder.h"
#include <cmath>

MockEncoder::MockEncoder(MockDCMotor& motor, double gearRatio, int encoderCountsPerRevolution) :
    motor_(motor), gearRatio_(gearRatio), encoderCountsPerRevolution_(encoderCountsPerRevolution), currentCount_(0) {}

void MockEncoder::setCount(double count) {
    currentCount_ = count;
}

double MockEncoder::getCount() const {
    return currentCount_;
}

double MockEncoder::getAngularVelocity() const {
    double velocity = motor_.getSpeed();
    // Convert velocity to radians per second
    double angularVelocity = (velocity / encoderCountsPerRevolution_) * 2 * M_PI * gearRatio_;
    return angularVelocity;
}

void MockEncoder::update() {
    // Update the encoder count based on the motor's speed
    currentCount_ += motor_.getSpeed();
}