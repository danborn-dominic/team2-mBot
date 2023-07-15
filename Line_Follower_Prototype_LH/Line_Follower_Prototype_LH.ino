// Prototype code for LM Intern project team 2
// Luke Henderson
#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include "src/MeSingleLineFollower.h"
#include "src/MeCollisionSensor.h"
#include "src/MeBarrierSensor.h"
#include "src/MeNewRGBLed.h"
#include <MeMegaPi.h>

// Initialize
MeNewRGBLed rgbled_67(67, 4);
MeNewRGBLed rgbled_68(68, 4);
MeSingleLineFollower linefollower_63(63);
MeSingleLineFollower linefollower_64(64);
MeBarrierSensor barrier_60(60);
MeBarrierSensor barrier_61(61);
MeBarrierSensor barrier_62(62);
MeMegaPiDCMotor motor_1(1);
MeMegaPiDCMotor motor_2(2);
MeMegaPiDCMotor motor_9(9);
MeMegaPiDCMotor motor_10(10);
MeCollisionSensor leftCollision(65);
MeCollisionSensor rightCollision(66);

double angle_rad = PI / 180.0;
double angle_deg = 180.0 / PI;

enum Direction {
  FORWARD,
  BACKWARD,
  CLOCKWISE,
  COUNTERCLOCKWISE,
  LEFT,
  RIGHT,
  STOP
};

enum sensorState {
  SENSORWHITE,
  SENSORBLACK
};

struct MotorData {
  int8_t timestamp;
  Direction direction;
};

// Change motor percent speed
float speed = 60;
float RGB = 0;
// Memorization values
bool start_motors = false;
bool start_recording = false;
const int max_data = 2000;
MotorData motor_data[max_data];
int data_num = 0;
Direction last_direction = STOP;
bool last_left_collision = false;
bool last_right_collision = false;

void setMotors(Direction direction) {
  switch (direction) {
    case FORWARD:
      motor_1.run(-speed / 100.0 * 255);
      motor_2.run(speed / 100.0 * 255);
      motor_9.run(-speed / 100.0 * 255);
      motor_10.run(speed / 100.0 * 255);
      break;
    case BACKWARD:
      motor_1.run(speed / 100.0 * 255);
      motor_2.run(-speed / 100.0 * 255);
      motor_9.run(speed / 100.0 * 255);
      motor_10.run(-speed / 100.0 * 255);
      break;
    case COUNTERCLOCKWISE:
      motor_1.run(speed / 100.0 * 255);
      motor_2.run(speed / 100.0 * 255);
      motor_9.run(speed / 100.0 * 255);
      motor_10.run(speed / 100.0 * 255);
      break;
    case CLOCKWISE:
      motor_1.run(-speed / 100.0 * 255);
      motor_2.run(-speed / 100.0 * 255);
      motor_9.run(-speed / 100.0 * 255);
      motor_10.run(-speed / 100.0 * 255);
      break;
    case RIGHT:
      motor_1.run(-speed / 100.0 * 255);
      motor_2.run(speed / 100.0 * 255);
      motor_9.run(speed / 100.0 * 255);
      motor_10.run(-speed / 100.0 * 255);
      break;
    case LEFT:
      motor_1.run(speed / 100.0 * 255);
      motor_2.run(-speed / 100.0 * 255);
      motor_9.run(-speed / 100.0 * 255);
      motor_10.run(speed / 100.0 * 255);
      break;
    case STOP:
      motor_1.stop();
      motor_2.stop();
      motor_9.stop();
      motor_10.stop();
      break;
  }
}

void setup() {
  Serial.begin(115200);
  rgbled_67.fillPixelsBak(0, 2, 1);
  rgbled_68.fillPixelsBak(0, 2, 1);
  TCCR1A = _BV(WGM10);
  TCCR1B = _BV(CS11) | _BV(WGM12);
  TCCR2A = _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(CS21);

  rgbled_67.setColor(0, 0, 0, 0);  // nothing
  rgbled_67.show();
  rgbled_68.setColor(0, 0, 0, 0);  // nothing
  rgbled_68.show();
}

void loop() {
  // Only start/stop motors or recording when button is toggled
  if (leftCollision.isCollision() && !last_left_collision) {
    start_recording = !start_recording;
    Serial.println("Changed recording");
  }
  if (rightCollision.isCollision() && !last_right_collision) {
    start_motors = !start_motors;
    Serial.println("Changed motors");
  }
  last_left_collision = leftCollision.isCollision();
  last_right_collision = rightCollision.isCollision();
  // If motors aren't started or recording, do nothing
  if (!start_motors) {
    setMotors(STOP);
    rgbled_67.setColor(0, 0, 0, 0);  // nothing
    rgbled_67.show();
    rgbled_68.setColor(0, 0, 0, 0);  // nothing
    rgbled_68.show();
    return;
  }
  if (data_num == max_data) {
    Serial.println("max data reached");
    setMotors(STOP);
    return;
  }
  if (start_motors && data_num > 0) {
    // Play back data that was recorded in motor_data
    Serial.println("playback");
    for (int i = 1; i < data_num; i++) {
      switch (motor_data[i].direction) {
        case FORWARD:
          setMotors(FORWARD);
          break;
        case BACKWARD:
          setMotors(BACKWARD);
          break;
        case COUNTERCLOCKWISE:
          setMotors(COUNTERCLOCKWISE);
          break;
        case CLOCKWISE:
          setMotors(CLOCKWISE);
          break;
        case RIGHT:
          setMotors(RIGHT);
          break;
        case LEFT:
          setMotors(LEFT);
          break;
        case STOP:
          setMotors(STOP);
          break;
      }
      delay(motor_data[i].timestamp - motor_data[i - 1].timestamp);
    }
  }
  // if object seen and not recording
  if ((barrier_60.isBarried() || barrier_61.isBarried() || barrier_62.isBarried())) {
    rgbled_67.setColor(0, 175, 0, 255);  // purple
    rgbled_67.show();
    rgbled_68.setColor(0, 175, 0, 255);  // purple
    rgbled_68.show();

    // right strafe
    Direction rightStrafe = RIGHT;
    setMotors(rightStrafe);
    delay(800);

    // forward
    Direction forward = FORWARD;
    setMotors(forward);
    delay(700);

    // left strafe
    Direction leftStrafe = LEFT;
    setMotors(leftStrafe);
    delay(800);
  }
  //if no object seen
  else {
    //senses white --> spin counter-clockwise until line is found
    if (linefollower_63.readSensor() == SENSORWHITE && linefollower_64.readSensor() == SENSORWHITE) {
      rgbled_67.setColor(0, 0, 255, 0);  // green
      rgbled_67.show();
      rgbled_68.setColor(0, 0, 255, 0);  // green
      rgbled_68.show();

      // turn left
      Direction counterClockwise = COUNTERCLOCKWISE;
      setMotors(counterClockwise);
      if (start_recording && last_direction != counterClockwise) {
        motor_data[data_num].timestamp = millis();
        motor_data[data_num].direction = counterClockwise;
        data_num++;
      }
      last_direction = counterClockwise;
    }
    // left black, right white --> turn left
    if (linefollower_63.readSensor() == SENSORBLACK && linefollower_64.readSensor() == SENSORWHITE) {
      rgbled_67.setColor(0, 0, 0, 255);  // blue
      rgbled_67.show();
      rgbled_68.setColor(0, 0, 0, 255);  // blue
      rgbled_68.show();

      Direction counterClockwise = COUNTERCLOCKWISE;
      setMotors(counterClockwise);
      if (start_recording && last_direction != counterClockwise) {
        motor_data[data_num].timestamp = millis();
        motor_data[data_num].direction = counterClockwise;
        data_num++;
      }
      last_direction = counterClockwise;
    }
    // left white, right black --> turn right
    if (linefollower_63.readSensor() == SENSORWHITE && linefollower_64.readSensor() == SENSORBLACK) {
      rgbled_67.setColor(0, 255, 200, 0);  // yellow
      rgbled_67.show();
      rgbled_68.setColor(0, 255, 200, 0);  // yellow
      rgbled_68.show();

      Direction clockwise = CLOCKWISE;
      setMotors(clockwise);
      if (start_recording) {
        motor_data[data_num].timestamp = millis();
        motor_data[data_num].direction = clockwise;
        data_num++;
      }
      last_direction = clockwise;
    }
    // left black, right black --> go forward
    if (linefollower_63.readSensor() == SENSORBLACK && linefollower_64.readSensor() == SENSORBLACK) {
      rgbled_67.setColor(0, 255, 0, 0);  // red
      rgbled_67.show();
      rgbled_68.setColor(0, 255, 0, 0);  // red
      rgbled_68.show();

      Direction forward = FORWARD;
      setMotors(forward);
      if (start_recording && last_direction != forward) {
        motor_data[data_num].timestamp = millis();
        motor_data[data_num].direction = forward;
        data_num++;
      }
      last_direction = forward;
    }
  }
}
