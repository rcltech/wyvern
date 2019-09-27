#include <Servo.h>

Servo servo1;
Servo servo2;  

const int servo1Pin = 6; // left
const int servo2Pin = 7; // right
const int ledPin = 8; // SIG1
const int buttonPin = 9; // SIG2

int ledState = LOW; // current state of output pin
int buttonState; // current reading from input pin
int lastButtonState = HIGH; // previous reading from input pin, defaults to HIGH at initialisation

unsigned long lastDebounceTime;
unsigned long debounceDelay = 50;

bool cycle = false;
const int period = 1000 * 2;
unsigned long lastMovementTime = 0;
unsigned long currentTime;
bool airconSwitch = false;

const int servoAngleForOn = 30;
const int servoAngleForOff = 150;

void moveServos(int startAngle, int endAngle) {
  if (endAngle > startAngle) {
    for (int i = startAngle + 1; i <= endAngle; i+=1) {
      servo1.write(180-i);
      servo2.write(i);
    }
  } else {
    for (int i = startAngle - 1; i >= endAngle; i-=1) {
      servo1.write(180-i);
      servo2.write(i);
    }
  }
}

void setup()
{
  Serial.begin(9600);
  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  digitalWrite(ledPin, ledState);
  delay(1000);
  moveServos(90, servoAngleForOff);//
}
 
void loop()
{
  int reading = digitalRead(buttonPin);

  // if the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    buttonState = reading;

    if (buttonState == LOW) { // when button is pressed
      cycle = !cycle;
      ledState = !ledState;
      lastMovementTime = millis();
      if (cycle) {
        moveServos(servoAngleForOff, servoAngleForOn);
        airconSwitch = true;
      } else {
        moveServos(servoAngleForOn, servoAngleForOff);
        airconSwitch = false;
      }
      delay(200);
    }
  }

  // set the LED
  digitalWrite(ledPin, ledState);

  // set the servos
  if (cycle) {
    currentTime = millis();
    if (currentTime - lastMovementTime > period) {
      if (airconSwitch) {
        moveServos(servoAngleForOn, servoAngleForOff);
      } else {
        moveServos(servoAngleForOff, servoAngleForOn);
      }
      airconSwitch = !airconSwitch;
      lastMovementTime = currentTime;
    }
    delay(25);
  }

  lastButtonState = reading;
}
