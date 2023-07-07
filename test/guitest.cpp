#include <SFML/Graphics.hpp>
#include "MecanumDrive.h"
#include "Odometry.h"
#include "PositionController.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Mecanum Drive Simulator");
    sf::RectangleShape robot(sf::Vector2f(50, 50));

    // Initialize your mecanum drive, odometry, and position controller here
    MecanumDrive drive();
    Odometry odometry();
    PositionController controller(1, 0, 0);

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
        controller.update();
        odometry.update(drive.getWheelSpeeds(), dt);

        // Update robot's position and rotation in the window
        auto [x, y, theta] = odometry.getPosition();
        robot.setPosition(x, y);
        robot.setRotation(theta);

        window.clear();
        window.draw(robot);
        window.display();
    }

    return 0;
}