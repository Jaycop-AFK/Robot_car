#ifndef CONTROLLMOVE_H
#define CONTROLLMOVE_H

#include <Arduino.h>

class controllMoveMotor {
private:
  uint8_t _font_left_1_pin;
  uint8_t _font_left_2_pin;
  uint8_t _font_right_1_pin;
  uint8_t _font_right_2_pin;
  uint8_t _back_left_1_pin;
  uint8_t _back_left_2_pin;
  uint8_t _back_right_1_pin;
  uint8_t _back_right_2_pin;

public:
  controllMoveMotor(
    uint8_t font_left_1_pin,
    uint8_t font_left_2_pin,
    uint8_t font_right_1_pin,
    uint8_t font_right_2_pin,
    uint8_t back_left_1_pin,
    uint8_t back_left_2_pin,
    uint8_t back_right_1_pin,
    uint8_t back_right_2_pin);
  void forward(int speed);
  void moveLeft(int speed);
  void rotateLeft(int speed);
  void forwardLeftOblique(int speed);
  void moveRight(int speed);
  void rotateRight(int speed);
  void forwardRightOblique(int speed);
  void back(int speed);
  void stop();
};

#endif