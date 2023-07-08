#include <cmath>
#include "MecanumDriveOdometry.h"

MecanumDriveOdometry::MecanumDriveOdometry(double wheelRadius, double wheelBase, double trackWidth)
    : wheelRadius_(wheelRadius), wheelBase_(wheelBase), trackWidth_(trackWidth), x_(0), y_(0), theta_(0) {}

// Update the odometry values using the equations from
// https://ecam-eurobot.github.io/Tutorials/mechanical/mecanum.html
// TODO: Update values based using the latest timestep since arduino doesn't have fixed timestep
// 
void MecanumDriveOdometry::update(double dThetaFL, double dThetaFR, double dThetaRL, double dThetaRR)
{
    double dX = (dThetaFL + dThetaFR + dThetaRL + dThetaRR) * wheelRadius_ / 4.0;
    double dY = (-dThetaFL + dThetaFR + dThetaRL - dThetaRR) * wheelRadius_ / 4.0;
    double dTheta = (-dThetaFL + dThetaFR - dThetaRL + dThetaRR) * wheelRadius_ / (4.0 * (wheelBase_ + trackWidth_));

    // Convert the robot's movement in the robot's frame of reference to the world frame of reference.
    x_ += dX * cos(theta_) - dY * sin(theta_);
    y_ += dX * sin(theta_) + dY * cos(theta_);
    theta_ += dTheta;
}

double MecanumDriveOdometry::getX() const {
    return x_;
}

double MecanumDriveOdometry::getY() const {
    return y_;
}

double MecanumDriveOdometry::getTheta() const {
    return theta_;
}