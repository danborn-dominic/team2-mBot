#ifndef Button_h
#define Button_h
#include <Arduino.h>
#include "MeCollisionSensor.h"

class Button {
public:
    Button(uint8_t port, unsigned int debounceDelay = 50);
    bool isPressed();
private:
    MeCollisionSensor _collisionSensor;
    const unsigned long _debounceDelay;
    int _state;
    int _lastState;
    unsigned long _lastDebounceTime;
};
#endif
