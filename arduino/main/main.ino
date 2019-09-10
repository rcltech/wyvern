#include <Servo.h>
 
int servoPin = 7;
int ledPin = 8;
int buttonPin = 9;

Servo servo;  
 
int servoAngle = 0;   // servo position in degrees
int ledState = 0;


void setup()
{
  Serial.begin(9600);
  servo.attach(servoPin);
  pinMode(ledPin, OUTPUT);
}
 
 
void loop()
{
  servo.write(45);
  if (ledState == 0) {
    digitalWrite(ledPin, HIGH);
    ledState = 1;
  }
  delay(1000);
  
  servo.write(90);
  if (ledState == 1) {
    digitalWrite(ledPin, LOW);
    ledState = 0;
  }
  delay(1000);
}
