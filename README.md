# 🚀 L298N-XCR

Advanced Arduino library for the L298N motor driver with servo-like interface, dual motor sumo mode, and manual control.

![motor](https://64.media.tumblr.com/af8fc629ae1ea93d72453efa404fbca2/tumblr_inline_orwqhlcveQ1rx3jxn_1280.gif) 



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



| Function                                 | Purpose                                                                                                                 |
| ---------------------------------------- | ----------------------------------------------------------------------------------------------------------------------- |
| `attach(pwmPin, in1Pin, in2Pin, name)`   | Initialize and attach the motor to the given pins. The `name` parameter is a label shown in debug messages.             |
| `setSpeed(speed)`                        | Set motor speed and direction. Range: -255 (full reverse) to +255 (full forward).                                       |
| `stop()`                                 | Immediately stop the motor (PWM = 0).                                                                                   |
| `enableSumoMode(leftMotor, rightMotor)`  | Link this motor with another to control both together (dual motor sumo or differential drive).                          |
| `sumoControl(leftSpeed, rightSpeed)`     | Move both motors simultaneously by setting individual speeds. Useful for forward, backward, and turning.                |
| `manualControl(in1, in2, pwm, duration)` | Manually set IN1/IN2 pin states (1/0), PWM value (0–255), and duration in milliseconds. Gives low-level manual control. |
| `debugOn()` / `debugOff()`               | Enable or disable debug messages over Serial for troubleshooting.                                                       |

📦 License

Open source under the MIT License.

![motor](https://cdn.prod.website-files.com/651d5c0b8a3eba9da6348b1d/65707f8fa6e7cc154cb74554_the-third-3-second.gif)

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
