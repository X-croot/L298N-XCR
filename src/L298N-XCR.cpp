#include "Arduino.h"
#include "L298N-XCR.h"

L298N_XCR::L298N_XCR() {
    _attached = false;
    _inverted = false;
    _enabled = true;
    _currentSpeed = 0;
    _maxSpeed = 255;
    _minSpeed = 0;
    _name = "";
    _debug = false;
    _sumoMode = false;
    _leftMotor = nullptr;
    _rightMotor = nullptr;
}

void L298N_XCR::attach(int enPin, int in1Pin, int in2Pin, const char* name) {
    _enPin = enPin;
    _in1Pin = in1Pin;
    _in2Pin = in2Pin;
    _name = name;
    _attached = true;
    pinMode(_enPin, OUTPUT);
    pinMode(_in1Pin, OUTPUT);
    pinMode(_in2Pin, OUTPUT);
    if (_debug) {
        Serial.print("["); Serial.print(_name); Serial.println("] Attached");
    }
}

void L298N_XCR::write(int speed) {
    if (!_attached || !_enabled) return;
    speed = constrain(speed, -_maxSpeed, _maxSpeed);
    if (_inverted) speed = -speed;
    if (speed != 0 && abs(speed) < _minSpeed) {
        speed = (speed > 0) ? _minSpeed : -_minSpeed;
    }
    _currentSpeed = speed;
    drive(speed);
    if (_debug) {
        Serial.print("["); Serial.print(_name); Serial.print("] write: ");
        Serial.println(speed);
    }
}

void L298N_XCR::drive(int speed) {
    if (speed > 0) {
        digitalWrite(_in1Pin, HIGH);
        digitalWrite(_in2Pin, LOW);
        analogWrite(_enPin, speed);
    } else if (speed < 0) {
        digitalWrite(_in1Pin, LOW);
        digitalWrite(_in2Pin, HIGH);
        analogWrite(_enPin, -speed);
    } else {
        digitalWrite(_in1Pin, LOW);
        digitalWrite(_in2Pin, LOW);
        analogWrite(_enPin, 0);
    }
}

void L298N_XCR::stop() {
    _currentSpeed = 0;
    drive(0);
    if (_debug) {
        Serial.print("["); Serial.print(_name); Serial.println("] stop");
    }
}

void L298N_XCR::brake() {
    digitalWrite(_in1Pin, HIGH);
    digitalWrite(_in2Pin, HIGH);
    analogWrite(_enPin, 0);
    _currentSpeed = 0;
    if (_debug) {
        Serial.print("["); Serial.print(_name); Serial.println("] brake");
    }
}

int L298N_XCR::read() {
    return _currentSpeed;
}

void L298N_XCR::invert(bool inv) {
    _inverted = inv;
    if (_debug) {
        Serial.print("["); Serial.print(_name); Serial.print("] invert: ");
        Serial.println(_inverted ? "true" : "false");
    }
}

void L298N_XCR::setMaxSpeed(int maxSpeed) {
    _maxSpeed = constrain(maxSpeed, 0, 255);
    if (_debug) {
        Serial.print("["); Serial.print(_name); Serial.print("] maxSpeed: ");
        Serial.println(_maxSpeed);
    }
}

void L298N_XCR::setMinSpeed(int minSpeed) {
    _minSpeed = constrain(minSpeed, 0, 255);
    if (_debug) {
        Serial.print("["); Serial.print(_name); Serial.print("] minSpeed: ");
        Serial.println(_minSpeed);
    }
}

void L298N_XCR::disable() {
    _enabled = false;
    stop();
    if (_debug) {
        Serial.print("["); Serial.print(_name); Serial.println("] disabled");
    }
}

void L298N_XCR::enable() {
    _enabled = true;
    if (_debug) {
        Serial.print("["); Serial.print(_name); Serial.println("] enabled");
    }
}

void L298N_XCR::debugOn() {
    _debug = true;
}

void L298N_XCR::debugOff() {
    _debug = false;
}

void L298N_XCR::manual(uint8_t in1State, uint8_t in2State, uint8_t pwm, unsigned long duration) {
    if (!_attached || !_enabled) return;
    digitalWrite(_in1Pin, in1State ? HIGH : LOW);
    digitalWrite(_in2Pin, in2State ? HIGH : LOW);
    analogWrite(_enPin, pwm);
    if (_debug) {
        Serial.print("["); Serial.print(_name); Serial.print("] manual: IN1=");
        Serial.print(in1State); Serial.print(", IN2=");
        Serial.print(in2State); Serial.print(", PWM=");
        Serial.print(pwm); Serial.print(", duration=");
        Serial.println(duration);
    }
    delay(duration);
    digitalWrite(_in1Pin, LOW);
    digitalWrite(_in2Pin, LOW);
    analogWrite(_enPin, 0);
}

void L298N_XCR::enableSumoMode(L298N_XCR* leftMotor, L298N_XCR* rightMotor) {
    _leftMotor = leftMotor;
    _rightMotor = rightMotor;
    _sumoMode = true;
    if (_debug) Serial.println("[SumoMode] Enabled");
}

void L298N_XCR::disableSumoMode() {
    _sumoMode = false;
    _leftMotor = nullptr;
    _rightMotor = nullptr;
    if (_debug) Serial.println("[SumoMode] Disabled");
}

void L298N_XCR::sumoControl(int leftSpeed, int rightSpeed) {
    if (_sumoMode && _leftMotor && _rightMotor) {
        _leftMotor->write(leftSpeed);
        _rightMotor->write(rightSpeed);
        if (_debug) {
            Serial.print("[SumoMode] leftSpeed=");
            Serial.print(leftSpeed); Serial.print(", rightSpeed=");
            Serial.println(rightSpeed);
        }
    }
}
