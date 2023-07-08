#include "PositionController.h"
#include <cmath>

// Learn about PID Control 
// https://file.tavsys.net/control/controls-engineering-in-frc.pdf
PositionController::PositionController(double kP, double kI, double kD)
    : kP_(kP), kI_(kI), kD_(kD), 
    targetX_(0), targetY_(0), targetTheta_(0), integralErrorX_(0), integralErrorY_(0), integralErrorTheta_(0), 
    prevErrorX_(0), prevErrorY_(0), prevErrorTheta_(0) {}

void PositionController::setTargetPosition(double x, double y, double theta) {
    targetX_ = x;
    targetY_ = y;
    targetTheta_ = theta;
}

// Learn more about PID Control
// https://docs.wpilib.org/en/stable/docs/software/advanced-controls/introduction/introduction-to-pid.html
// TODO: Update values based using the latest timestep since arduino doesn't have fixed timestep
// https://www.teachmemicro.com/arduino-pid-control-tutorial/
void PositionController::update(double x, double y, double theta, double *forwardSpeed, double *strafeSpeed, double *rotationalSpeed) {
    double errorX = targetX_ - x;
    double errorY = targetY_ - y;
    double errorTheta = targetTheta_ - theta;

    // Calculates the integral of the error
    integralErrorX_ += errorX;
    integralErrorY_ += errorY;
    integralErrorTheta_ += errorTheta;

    // Calculates the derivative of the error
    double derivativeErrorX = errorX - prevErrorX_;
    double derivativeErrorY = errorY - prevErrorY_;
    double derivativeErrorTheta = errorTheta - prevErrorTheta_;

    // Calculates the output of the PID controller
    *forwardSpeed = kP_ * errorX + kI_ * integralErrorX_ + kD_ * derivativeErrorX;
    *strafeSpeed = kP_ * errorY + kI_ * integralErrorY_ + kD_ * derivativeErrorY;
    *rotationalSpeed = kP_ * errorTheta + kI_ * integralErrorTheta_ + kD_ * derivativeErrorTheta;

    prevErrorX_ = errorX;
    prevErrorY_ = errorY;
    prevErrorTheta_ = errorTheta;
}

bool PositionController::isAtTargetPosition(double x, double y, double theta) const {
    double errorX = targetX_ - x;
    double errorY = targetY_ - y;
    double errorTheta = targetTheta_ - theta;

    return std::abs(errorX) < 0.01 && std::abs(errorY) < 0.01 && std::abs(errorTheta) < 0.01;
}