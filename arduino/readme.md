# Arduino Programs

### Pre-requisites
Install the Arduino IDE from the [official website](https://www.arduino.cc/en/main/software).

### Hardware Specifications
As of this writing, the modules used are:
- [Arduino Uno](https://store.arduino.cc/usa/arduino-uno-rev3)
- [Tower Pro MicroServo Digital 9g SG90](http://wiki.seeedstudio.com/Grove-LED_Button/)
- [Grove LED Button (Blue)](http://www.towerpro.com.tw/product/sg90-7/)

All of these were obtained at [WECL](https://www.google.com/maps/place/WECL/@22.330139,114.1596443,17z/data=!3m1!4b1!4m5!3m4!1s0x340400b48210ecb9:0x230f477445c8bed5!8m2!3d22.330139!4d114.161833), Sham Shui Po, Hong Kong.

### To run
Clone this repo, and cd into the `arduino` folder.
```
git clone https://github.com/rcltech/wyvern.git
cd wyvern/arduino
```

Open the main program using the Arduino IDE. If you are using Linux / macOS:
```
arduino main/main.ino
```

Connect your arduino to one of your USB ports, and upload the program. If you cannot make this work, refer to this [guide](https://www.arduino.cc/en/main/howto).

### COnfigurations
#### To change period of each cycle
Change the value of `const int period` in terms of milliseconds.
For example: `const int period = 1000 * 60 * 10` represents a cycle period of 10 minutes.

### Pin Specifications
All pins used are digital. You are welcomed to change the pins to your preference.

Pin for servo: `servoPin = 7`

Pin for LED: `ledPin = 8`

Pin for button: `buttonPin = 9`
