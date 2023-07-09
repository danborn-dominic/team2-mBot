#pragma once
#include "MockDCMotor.h"

class MockEncoder {
public:
MockEncoder(MockDCMotor& motor, double gearRatio=1, int encoderCountsPerRevolution=1);

    void setCount(double count);
    double getCount() const;
    double getAngularVelocity() const;
    void update();
private:
    MockDCMotor& motor_;
    double gearRatio_;
    int encoderCountsPerRevolution_;
    double currentCount_;
};