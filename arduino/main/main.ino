#include <Servo.h>

Servo servo;  

const int servoPin = 7;
const int ledPin = 8; // SIG1
const int buttonPin = 9; // SIG2

int ledState = LOW; // current state of output pin
int buttonState; // current reading from input pin
int lastButtonState = HIGH; // previous reading from input pin, defaults to HIGH at initialisation
int servoAngle = 90;   // servo position in degrees, set to middle

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

void setup()
{
  Serial.begin(9600);
  servo.attach(servoPin);
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  digitalWrite(ledPin, ledState);
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

    if (buttonState == LOW) {
      ledState = !ledState;
      delay(200);
    }
  }

  // set the LED
  digitalWrite(ledPin, ledState);

  // set the servo
  if (ledState == HIGH) {
    servo.write(30);
  } else {
    servo.write(150);
  }

  lastButtonState = reading;
}
