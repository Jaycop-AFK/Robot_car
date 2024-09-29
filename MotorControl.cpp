#include "MotorControl.h"
#include <Arduino.h>

MotorControl::MotorControl() {
    initializePins();  // Initialize motor pins on object creation
}

void MotorControl::initializePins() {
    // Set motor pins as output
    pinMode(MOTORBACKLEFT_FORWARD, OUTPUT);
    pinMode(MOTORBACKLEFT_BACKWARD, OUTPUT);
    pinMode(MOTORFRONTLEFT_FORWARD, OUTPUT);
    pinMode(MOTORFRONTLEFT_BACKWARD, OUTPUT);
    pinMode(MOTORBACKRIGHT_FORWARD, OUTPUT);
    pinMode(MOTORBACKRIGHT_BACKWARD, OUTPUT);
    pinMode(MOTORFRONTRIGHT_FORWARD, OUTPUT);
    pinMode(MOTORFRONTRIGHT_BACKWARD, OUTPUT);
}

// Utility function to validate the speed and ensure it's in the correct range (0-255)
int MotorControl::validateSpeed(int speed) {
    return constrain(speed, 0, 255);  // Ensure speed is between 0 and 255
}

void MotorControl::moveForward(int speed) {
    speed = validateSpeed(speed);
    analogWrite(MOTORBACKLEFT_FORWARD, speed);
    analogWrite(MOTORFRONTLEFT_FORWARD, speed);
    analogWrite(MOTORBACKRIGHT_FORWARD, speed);
    analogWrite(MOTORFRONTRIGHT_FORWARD, speed);

    // Ensure backward pins are off
    analogWrite(MOTORBACKLEFT_BACKWARD, 0);
    analogWrite(MOTORFRONTLEFT_BACKWARD, 0);
    analogWrite(MOTORBACKRIGHT_BACKWARD, 0);
    analogWrite(MOTORFRONTRIGHT_BACKWARD, 0);
}

void MotorControl::moveBackward(int speed) {
    speed = validateSpeed(speed);
    analogWrite(MOTORBACKLEFT_BACKWARD, speed);
    analogWrite(MOTORFRONTLEFT_BACKWARD, speed);
    analogWrite(MOTORBACKRIGHT_BACKWARD, speed);
    analogWrite(MOTORFRONTRIGHT_BACKWARD, speed);

    // Ensure forward pins are off
    analogWrite(MOTORBACKLEFT_FORWARD, 0);
    analogWrite(MOTORFRONTLEFT_FORWARD, 0);
    analogWrite(MOTORBACKRIGHT_FORWARD, 0);
    analogWrite(MOTORFRONTRIGHT_FORWARD, 0);
}

void MotorControl::turnLeft(int speed) {
    speed = validateSpeed(speed);
    analogWrite(MOTORBACKLEFT_BACKWARD, speed);
    analogWrite(MOTORFRONTLEFT_BACKWARD, speed);
    analogWrite(MOTORBACKRIGHT_FORWARD, speed);
    analogWrite(MOTORFRONTRIGHT_FORWARD, speed);

    // Ensure other pins are off
    analogWrite(MOTORBACKLEFT_FORWARD, 0);
    analogWrite(MOTORFRONTLEFT_FORWARD, 0);
    analogWrite(MOTORBACKRIGHT_BACKWARD, 0);
    analogWrite(MOTORFRONTRIGHT_BACKWARD, 0);
}

void MotorControl::turnRight(int speed) {
    speed = validateSpeed(speed);
    analogWrite(MOTORBACKLEFT_FORWARD, speed);
    analogWrite(MOTORFRONTLEFT_FORWARD, speed);
    analogWrite(MOTORBACKRIGHT_BACKWARD, speed);
    analogWrite(MOTORFRONTRIGHT_BACKWARD, speed);

    // Ensure other pins are off
    analogWrite(MOTORBACKLEFT_BACKWARD, 0);
    analogWrite(MOTORFRONTLEFT_BACKWARD, 0);
    analogWrite(MOTORBACKRIGHT_FORWARD, 0);
    analogWrite(MOTORFRONTRIGHT_FORWARD, 0);
}

void MotorControl::stop() {
    // Turn off all motor pins
    analogWrite(MOTORBACKLEFT_FORWARD, 0);
    analogWrite(MOTORFRONTLEFT_FORWARD, 0);
    analogWrite(MOTORBACKRIGHT_FORWARD, 0);
    analogWrite(MOTORFRONTRIGHT_FORWARD, 0);
    analogWrite(MOTORBACKLEFT_BACKWARD, 0);
    analogWrite(MOTORFRONTLEFT_BACKWARD, 0);
    analogWrite(MOTORBACKRIGHT_BACKWARD, 0);
    analogWrite(MOTORFRONTRIGHT_BACKWARD, 0);
}
