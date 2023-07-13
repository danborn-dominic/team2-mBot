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
MeNewRGBLed rgbled_67(67,4);
MeNewRGBLed rgbled_68(68,4);
MeSingleLineFollower linefollower_63(63);
MeSingleLineFollower linefollower_64(64);
MeBarrierSensor barrier_60(60);
MeBarrierSensor barrier_61(61);
MeBarrierSensor barrier_62(62);
MeMegaPiDCMotor motor_1(1);
MeMegaPiDCMotor motor_2(2);
MeMegaPiDCMotor motor_9(9);
MeMegaPiDCMotor motor_10(10);
MeMegaPiDCMotor motor_3(3);
MeMegaPiDCMotor motor_11(11);
MeMegaPiDCMotor motor_4(4);
MeMegaPiDCMotor motor_12(12);

double angle_rad = PI/180.0;
double angle_deg = 180.0/PI;

float RGB = 0;
float light_num = 0;

//delay
void _delay(float seconds) {
  if(seconds < 0.0){
    seconds = 0.0;
  }
  long endTime = millis() + seconds * 1000;
  while(millis() < endTime) _loop();
}

// setup
void setup() {
  rgbled_67.fillPixelsBak(0, 2, 1);
  rgbled_68.fillPixelsBak(0, 2, 1);
  TCCR1A = _BV(WGM10);
  TCCR1B = _BV(CS11) | _BV(WGM12);
  TCCR2A = _BV(WGM21) | _BV(WGM20);
  TCCR2B = _BV(CS21);
  light_num = 4;

  rgbled_67.setColor(0, 0, 0, 0);
  rgbled_67.show();

  rgbled_68.setColor(0, 0, 0, 0);
  rgbled_68.show();
}

// Important stuff here
void loop() {

  // change percent speed (default is 50%)
  float speed = 60;

  // if object seen
  if(barrier_60.isBarried() || barrier_61.isBarried() || barrier_62.isBarried()){

    rgbled_67.setColor(0, 175, 0, 255); // purple
    rgbled_67.show();
    rgbled_68.setColor(0, 175, 0, 255); // purple
    rgbled_68.show();

    // right strafe
    motor_1.run(-speed / 100.0 * 255);
    motor_2.run(speed / 100.0 * 255);
    motor_9.run(speed / 100.0 * 255);
    motor_10.run(-speed / 100.0 * 255);

    _delay(0.8);

    // forward
    motor_1.run(-speed / 100.0 * 255);
    motor_2.run(speed / 100.0 * 255);
    motor_9.run(-speed / 100.0 * 255);
    motor_10.run(speed / 100.0 * 255);

    _delay(0.7);

    // left strafe
    motor_1.run(speed / 100.0 * 255);
    motor_2.run(-speed / 100.0 * 255);
    motor_9.run(-speed / 100.0 * 255);
    motor_10.run(speed / 100.0 * 255);

    _delay(0.8);
  }
  //if no object seen
  else{
    //senses white --> spin counter-clockwise until line is found
    if(((linefollower_63.readSensor() == 0))  &&  ((linefollower_64.readSensor() == 0))){

        rgbled_67.setColor(0, 0, 255, 0); // green
        rgbled_67.show();
        rgbled_68.setColor(0, 0, 255, 0); // green
        rgbled_68.show();

        // turn left
        motor_1.run(speed / 100.0 * 255);
        motor_2.run(speed / 100.0 * 255);
        motor_9.run(speed / 100.0 * 255);
        motor_10.run(speed / 100.0 * 255);
        

    }
    // left black, right white --> turn left
    if(((linefollower_63.readSensor() == 1))  &&  ((linefollower_64.readSensor() == 0))){

        rgbled_67.setColor(0, 0, 0, 255); // blue
        rgbled_67.show();
        rgbled_68.setColor(0, 0, 0, 255); // blue
        rgbled_68.show();

        // turn left
        motor_1.run(speed / 100.0 * 255);
        motor_2.run(speed / 100.0 * 255);
        motor_9.run(speed / 100.0 * 255);
        motor_10.run(speed / 100.0 * 255);

    }
    // left white, right black --> turn right
    if(((linefollower_63.readSensor() == 0))  &&  ((linefollower_64.readSensor() == 1))){

        rgbled_67.setColor(0, 255, 200, 0); // yellow
        rgbled_67.show();
        rgbled_68.setColor(0, 255, 200, 0); // yellow
        rgbled_68.show();

        // turn right
        motor_1.run(-speed / 100.0 * 255);
        motor_2.run(-speed / 100.0 * 255);
        motor_9.run(-speed / 100.0 * 255);
        motor_10.run(-speed / 100.0 * 255);

    }
    // left black, right black --> go straight
    if(((linefollower_63.readSensor() == 1))  &&  ((linefollower_64.readSensor() == 1))){

        rgbled_67.setColor(0, 255, 0, 0); // red
        rgbled_67.show();
        rgbled_68.setColor(0, 255, 0, 0); // red
        rgbled_68.show();

        // forward
        motor_1.run(-speed / 100.0 * 255);
        motor_2.run(speed / 100.0 * 255);
        motor_9.run(-speed / 100.0 * 255);
        motor_10.run(speed / 100.0 * 255);

    }
  }
  _loop();
}
