#include <ESP32Servo.h>


Servo myservo;
Servo myservo1;
// 16 servo objects can be created on the ESP32

int pos = 0;
int servoPin=18;
int servoPin1=17;

void setup() {

 ESP32PWM::allocateTimer(0);
 ESP32PWM::allocateTimer(1);
 ESP32PWM::allocateTimer(2);
 ESP32PWM::allocateTimer(3);
 myservo.setPeriodHertz(50);
 myservo.attach(servoPin, 0, 2000); // attaches the servo on pin 18 to the servo object
 myservo1.setPeriodHertz(50);
 myservo1.attach(servoPin1, 0, 2000); // attaches the servo on pin 18 to the servo object

}

void loop() {

 for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
  myservo.write(pos);
  delay(15); 
 }
 for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
  myservo.write(pos);
  delay(15);
 }

  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
  myservo1.write(pos);
  delay(15); 
 }
 for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
  myservo1.write(pos);
  delay(15);
 }
}