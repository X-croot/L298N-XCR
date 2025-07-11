<h1 align="center">🚀 L298N-XCR</h1>
<p align="center">Advanced Arduino library for L298N motor driver with servo-like interface, dual motor mode, and manual control.</p>

<p align="center">
  <img src="https://64.media.tumblr.com/af8fc629ae1ea93d72453efa404fbca2/tumblr_inline_orwqhlcveQ1rx3jxn_1280.gif" alt="Mini Sumo Robot Demo" width="400"/>
</p>

<h2>✨ Features</h2>
<ul>
  <li>Servo-style control (<code>attach</code> and <code>setSpeed</code>)</li>
  <li>Dual motor sumo mode</li>
  <li>Manual pin & PWM control</li>
  <li>Debug output (optional)</li>
  <li>Clean, object-oriented Arduino design</li>
</ul>

<h2>📦 What is L298N?</h2>
<p>L298N is a popular dual H-bridge motor driver, ideal for controlling two DC motors with speed and direction.</p>

<p align="center">
  <img src="https://arduinoyard.com/wp-content/uploads/2025/02/l298n_motordriver_pinout_bb.png" alt="L298N Pinout Diagram" width="500"/>
</p>

<h2>🛠️ Example</h2>

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

<h2>📚 Functions</h2> <ul> <li><code>attach(pwmPin, in1Pin, in2Pin, name)</code> – Attach motor to pins</li> <li><code>setSpeed(speed)</code> – Control speed & direction (-255 to 255)</li> <li><code>stop()</code> – Stop motor</li> <li><code>enableSumoMode(leftMotor, rightMotor)</code> – Enable dual motor control</li> <li><code>sumoControl(leftSpeed, rightSpeed)</code> – Move both motors together</li> <li><code>manualControl(in1, in2, pwm, duration)</code> – Manual control mode</li> <li><code>debugOn()</code> / <code>debugOff()</code> – Debug serial output</li> </ul> <h2>📦 License</h2> <p>Open source under the <strong>MIT License</strong>.</p> <h2>✏️ Author</h2> <p>Created by <strong>Your Name</strong><br> GitHub: <a href="https://github.com/yourusername">yourusername</a></p> ```
