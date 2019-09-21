#include <Servo.h>

Servo servo;  

const int servoPin = 7;
const int ledPin = 8; // SIG1
const int buttonPin = 9; // SIG2

int ledState = LOW; // current state of output pin
int buttonState; // current reading from input pin
int lastButtonState = HIGH; // previous reading from input pin, defaults to HIGH at initialisation

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

bool cycle = false;
const int period = 1000 * 2;
unsigned long lastMovementTime;
unsigned long currentTime;
bool airconSwitch = false;

const int servoAngleForOn = 30;
const int servoAngleForOff = 150;

void setup()
{
  Serial.begin(9600);
  servo.attach(servoPin);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  digitalWrite(ledPin, ledState);
  servo.write(servoAngleForOff);
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
        servo.write(servoAngleForOn);
        airconSwitch = true;
      } else {
        servo.write(servoAngleForOff);
        airconSwitch = false;
      }
      delay(200);
    }
  }

  // set the LED
  digitalWrite(ledPin, ledState);

  // set the servo
  if (cycle) {
    currentTime = millis();
    if (currentTime - lastMovementTime > period) {
      if (airconSwitch) {
        servo.write(servoAngleForOff);
      } else {
        servo.write(servoAngleForOn);
      }
      airconSwitch = !airconSwitch;
      lastMovementTime = currentTime;
    }
  }

  lastButtonState = reading;
}
