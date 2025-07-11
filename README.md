# 🚀 L298N-XCR

Advanced Arduino library for the L298N motor driver with servo-like interface, dual motor sumo mode, and manual control.

<p align="center">
  <img src="https://64.media.tumblr.com/af8fc629ae1ea93d72453efa404fbca2/tumblr_inline_orwqhlcveQ1rx3jxn_1280.gif" alt="Mini Sumo Robot Demo" width="400" />
</p>

## ✨ Features
- Servo-style control (`attach` and `setSpeed`)
- Dual motor sumo mode
- Manual pin & PWM control
- Debug output (optional)
- Clean, object-oriented Arduino design

## 📦 What is L298N?
L298N is a popular dual H-bridge motor driver, ideal for controlling two DC motors with speed and direction in robotics projects.

<p align="center">
  <img src="https://arduinoyard.com/wp-content/uploads/2025/02/l298n_motordriver_pinout_bb.png" alt="L298N Pinout Diagram" width="500" />
</p>

## 🛠️ Example
```cpp
#include <L298N-XCR.h>

L298N_XCR motorLeft;
L298N_XCR motorRight;

void setup() {
  motorLeft.attach(5, 2, 3, "Left Motor");
  motorRight.attach(6, 4, 7, "Right Motor");
  motorLeft.enableSumoMode(&motorLeft, &motorRight);
}

void loop() {
  motorLeft.sumoControl(150, 150); // forward
  delay(1000);
  motorLeft.sumoControl(-150, -150); // backward
  delay(1000);
  motorLeft.sumoControl(150, -150); // turn left
  delay(700);
  motorLeft.sumoControl(-150, 150); // turn right
  delay(700);
  motorLeft.sumoControl(0, 0); // stop
  delay(500);
}

📚 Function Reference
Function	Purpose
attach(pwmPin, in1Pin, in2Pin, name)	Attach motor to pins
setSpeed(speed)	Control speed & direction (-255 to 255)
stop()	Stop motor
enableSumoMode(leftMotor, rightMotor)	Enable dual motor sumo control
sumoControl(leftSpeed, rightSpeed)	Move both motors together
manualControl(in1, in2, pwm, duration)	Manual pin & PWM control
debugOn() / debugOff()	Enable or disable debug messages
📦 License

Open source under the MIT License.
