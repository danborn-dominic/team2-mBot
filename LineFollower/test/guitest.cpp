#include <SFML/Graphics.hpp>
#include "../src/mock/MockDCMotor.h"
#include "../src/mock/MockEncoder.h"
#include "../src/mock/MockMecanumDrive.h"
#include "../src/MecanumDriveOdometry.h"
#include "../src/PositionController.h"

int main() {
    double length = 7.5, width = 6.4, height = 4;
    double wheelRaidus = 2.3622, wheelBase = 4.75, trackWidth = 5.25;
    sf::RenderWindow window(sf::VideoMode(800, 600), "Mecanum Drive Simulator");
    sf::RectangleShape robot(sf::Vector2f(200*length/(length+width), 200*width/(length+width)));

    // Initialize motors and encoders
    MockDCMotor motorFL;
    MockDCMotor motorFR;
    MockDCMotor motorRL;
    MockDCMotor motorRR;
    MockEncoder encoderFL(motorFL, 1, 1);
    MockEncoder encoderFR(motorFR, 1, 1);
    MockEncoder encoderRL(motorRL, 1, 1);
    MockEncoder encoderRR(motorRR, 1, 1);

    // Initialize mecanum drive, odometry, and position controller
    MockMecanumDrive drive(motorFL, motorFR, motorRL, motorRR);
    MecanumDriveOdometry odometry(wheelRaidus, wheelBase, trackWidth);
    PositionController controller(1, 0, 0);

    // Initialize robot's position and rotation in the window
    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Perform control update
        double dt = clock.restart().asSeconds();
        double forwardSpeed = 0, strafeSpeed = 0, rotationalSpeed = 0;
        // Update your odometry and position controller here
        controller.update(odometry.getX(), odometry.getY(), odometry.getTheta(), &forwardSpeed, &strafeSpeed, &rotationalSpeed);
        odometry.update(encoderFL.getAngularVelocity(), encoderFR.getAngularVelocity(), 
            encoderRL.getAngularVelocity(), encoderRR.getAngularVelocity());

        // Update your mecanum drive
        drive.drive(forwardSpeed, strafeSpeed, rotationalSpeed);

        // Update robot's position and rotation in the window
        double x = odometry.getX();
        double y = odometry.getY();
        double theta = odometry.getTheta();
        robot.setPosition(x, y);
        robot.setRotation(theta);

        window.clear();
        window.draw(robot);
        window.display();
    }

    return 0;
}