#ifndef POSITION_CONTROLLER_H
#define POSITION_CONTROLLER_H

class PositionController {
public:
    // kP, kI, and kD are the PID constants for the controller
    PositionController(double kP, double kI, double kD);
    // Set the target position for the controller
    void setTargetPosition(double x, double y, double theta);
    /*
    * Update the position controller.
    * Arguments:
    * x: The current x position of the robot.
    * y: The current y position of the robot.
    * theta: The current angle of the robot.
    * Returns:
    * forwardSpeed: The forward speed of the robot.
    * strafeSpeed: The strafe speed of the robot.
    * rotationalSpeed: The rotational speed of the robot.
    */
    void update(double x, double y, double theta, double *forwardSpeed, double *strafeSpeed, double *rotationalSpeed);
    // Returns true if the robot is at the target position
    bool isAtTargetPosition(double x, double y, double theta) const;

private:
    double kP_, kI_, kD_;
    double targetX_, targetY_, targetTheta_;
    double integralErrorX_, integralErrorY_, integralErrorTheta_;
    double prevErrorX_, prevErrorY_, prevErrorTheta_;
};

#endif // POSITION_CONTROLLER_H
