#ifndef MECANUM_DRIVE_ODOMETRY_H
#define MECANUM_DRIVE_ODOMETRY_H

class MecanumDriveOdometry
{
public:
    // Creates an odometry object for a mecanum drive robot.
    // wheelRadius: The radius of the wheels in meters.
    // wheelBase: The distance between the front and back wheels in meters.
    // trackWidth: The distance between the left and right wheels in meters.
    MecanumDriveOdometry(double wheelRadius, double wheelBase, double trackWidth);
    // Update the odometry values using the equations from
    void update(double dThetaFL, double dThetaFR, double dThetaRL, double dThetaRR);
    double getX() const;
    double getY() const;
    double getTheta() const;

private:
    double wheelRadius_;
    double wheelBase_;
    double trackWidth_;
    double x_, y_, theta_;
};

#endif // MECANUM_DRIVE_ODOMETRY_H