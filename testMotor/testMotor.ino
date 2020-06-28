#include <SoftwareSerial.h>
#include "AFMotor.h"

AF_DCMotor motor1(1);
AF_DCMotor motor4(4);

void setup() {
  Serial.begin(9600);
}

// Right
void loop() {
    
    motor1.setSpeed(120);
    motor4.setSpeed(0);
    motor1.run(FORWARD);
    motor4.run(FORWARD);

    delay(460);

    motor4.setSpeed(0);
    motor1.run(BACKWARD);

    delay(50);
    
    motor1.run(RELEASE);
    motor4.run(RELEASE);

    delay(1000);
}
