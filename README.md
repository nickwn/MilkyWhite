# MilkyWhite

The code that currently runs on Milky White

### What is Milky White?
Milky White started off as an animatronic cow made by
[Westview Robotics](http://westviewrobotics.com) for the school's theatre
production of Into the Woods. It featured moving eyelids, ears, and a tail.
The next year, the Research and Development track modified the cow by putting
it on an FRC Chassis and making it remote controlled through an android phone
app.

Since then, the cow has been displayed in countless outreach activities.

### How does it work?
 * The phone and the Arduino on the cow communicate through bluetooth. The
 Arduino uses an HC-05 bluetooth module to communicate with the phone.
 * The android app was written using
 [MIT App Inventor](http://appinventor.mit.edu/explore/)

### Dependencies
 * We used the
 [Adafruit PWM Servo Shield](https://www.adafruit.com/product/1411) to 
 control all of the servos in the cow. Make sure to download the library for it
 [here](https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library).
