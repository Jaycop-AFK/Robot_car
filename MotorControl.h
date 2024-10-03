#ifndef MOTORCONTROL_H
#define MOTORCONTROL_H

// Define motor pins
#define MOTORBACKLEFT_FORWARD 13   
#define MOTORBACKLEFT_BACKWARD 12

#define MOTORFRONTLEFT_FORWARD 14
#define MOTORFRONTLEFT_BACKWARD 27
  
#define MOTORBACKRIGHT_FORWARD 26
#define MOTORBACKRIGHT_BACKWARD 25

#define MOTORFRONTRIGHT_FORWARD 33
#define MOTORFRONTRIGHT_BACKWARD 32

class MotorControl {
public:
    MotorControl();    // Constructor
    void moveForward(int speed);    // Move forward with a given speed
    void moveBackward(int speed);   // Move backward with a given speed
    void turnLeft(int speed);       // Turn left with a given speed
    void turnRight(int speed);      // Turn right with a given speed
    void stop();                    // Stop all motors
private:
    void initializePins();          // Initialize the motor pins
    int validateSpeed(int speed);   // Ensure speed is within the allowable range
};

#endif
