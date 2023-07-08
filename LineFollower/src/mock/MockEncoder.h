#pragma once
#include "MockDCMotor.h"

class MockEncoder {
private:
    MockDCMotor& motor_;
    double gearRatio_;
    int encoderCountsPerRevolution_;
    double currentCount_;

public:
    MockEncoder(MockDCMotor& motor, double gearRatio, int encoderCountsPerRevolution);

    void setCount(double count);
    double getCount() const;
    double getAngularVelocity() const;
    void update();
};