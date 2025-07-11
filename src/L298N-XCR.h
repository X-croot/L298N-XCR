#ifndef L298N_XCR_H
#define L298N_XCR_H

#include "Arduino.h"

class L298N_XCR {
public:
    L298N_XCR();

    void attach(int enPin, int in1Pin, int in2Pin, const char* name = "");
    void write(int speed);
    void stop();
    void brake();
    int read();
    void invert(bool inv = true);
    void setMaxSpeed(int maxSpeed);
    void setMinSpeed(int minSpeed);
    void disable();
    void enable();
    void debugOn();
    void debugOff();
    void manual(uint8_t in1State, uint8_t in2State, uint8_t pwm, unsigned long duration);
    void enableSumoMode(L298N_XCR* leftMotor, L298N_XCR* rightMotor);
    void disableSumoMode();
    void sumoControl(int leftSpeed, int rightSpeed);

private:
    int _enPin, _in1Pin, _in2Pin;
    bool _attached;
    bool _inverted;
    bool _enabled;
    int _currentSpeed;
    int _maxSpeed;
    int _minSpeed;
    const char* _name;
    bool _debug;
    bool _sumoMode;
    L298N_XCR* _leftMotor;
    L298N_XCR* _rightMotor;

    void drive(int speed);
};

#endif
