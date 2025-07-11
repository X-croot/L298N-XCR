#include <L298N-XCR.h>

L298N_XCR motorLeft;
L298N_XCR motorRight;

const int lineSensorPin = A2;
const int lineThreshold = 500;

void setup() {
    motorLeft.attach(5, 2, 3, "Left Motor");
    motorRight.attach(6, 4, 7, "Right Motor");
    motorLeft.enableSumoMode(&motorLeft, &motorRight);
}

void loop() {
    int sensorValue = analogRead(lineSensorPin);

    if (sensorValue > lineThreshold + 50) {
        motorLeft.sumoControl(120, 60);
    }
    else if (sensorValue < lineThreshold - 50) {
        motorLeft.sumoControl(60, 120);
    }
    else {
        motorLeft.sumoControl(100, 100);
    }

    delay(50);
}
