#include <AFMotor.h>

AF_DCMotor motor1(1);
AF_DCMotor motor4(4);

void setup() {
  motor1.setSpeed(200);
  motor1.run(RELEASE);
  motor4.setSpeed(200);
  motor4.run(RELEASE);

  motor1.run(FORWARD);
  motor4.run(FORWARD);
  delay(3000);
    
  motor1.run(BACKWARD);
  motor4.run(BACKWARD);
  delay(3000);
    
  motor1.run(RELEASE);
  motor4.run(RELEASE);
}

void loop() {
      
}
