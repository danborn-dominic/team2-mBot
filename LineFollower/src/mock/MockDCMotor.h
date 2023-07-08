#pragma once

class MockDCMotor {
public:
    MockDCMotor();

    void setSpeed(int speed);
    int getSpeed() const;

    void setDirection(int direction);
    int getDirection() const;

    void stop();
private:
    int speed;
    int direction;
};
