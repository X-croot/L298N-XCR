#include <L298N-XCR.h>

L298N_XCR motorLeft;
L298N_XCR motorRight;

const int distanceSensorPin = A0;
const int lineSensorLeftPin = A1;
const int lineSensorRightPin = A2;

const int distanceThreshold = 250;
const int lineThreshold = 600;

void setup() {
    Serial.begin(9600);
    motorLeft.attach(5, 2, 3, "Left Motor");
    motorRight.attach(6, 4, 7, "Right Motor");
    motorLeft.debugOn();
    motorRight.debugOn();
    motorLeft.enableSumoMode(&motorLeft, &motorRight);
}

void loop() {
    int distance = analogRead(distanceSensorPin);
    int lineLeft = analogRead(lineSensorLeftPin);
    int lineRight = analogRead(lineSensorRightPin);

    Serial.print("Distance: "); Serial.print(distance);
    Serial.print(" | Line Left: "); Serial.print(lineLeft);
    Serial.print(" | Line Right: "); Serial.println(lineRight);

    if (lineLeft > lineThreshold || lineRight > lineThreshold) {
        motorLeft.sumoControl(-150, -150);
        delay(300);
        if (lineLeft > lineThreshold) {
            motorLeft.sumoControl(-150, 150);
        } else {
            motorLeft.sumoControl(150, -150);
        }
        delay(400);
    }
    else if (distance < distanceThreshold) {
        motorLeft.sumoControl(200, 200);
    }
    else {
        motorLeft.sumoControl(100, -100);
    }

    delay(50);
}
