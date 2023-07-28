#include "Button.h"

Button::Button(uint8_t port, unsigned int debounceDelay) 
: _collisionSensor(port), _debounceDelay(debounceDelay), _state(HIGH), _lastState(HIGH), _lastDebounceTime(0) {}

bool Button::isPressed() {
    int reading = _collisionSensor.readSensor();

    if (reading != _lastState) {
      _lastDebounceTime = millis();
    }

    if ((millis() - _lastDebounceTime) > _debounceDelay) {
      if (reading != _state) {
        _state = reading;

        if (_state == LOW) {
          return true;  // Button is pressed
        }
      }
    }

    _lastState = reading;
    return false;  // Button is not pressed
}


