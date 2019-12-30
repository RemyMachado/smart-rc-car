# smart-rc-car :car::satellite:
_This project was handmade. No third party libraries were used._
![elegoo-car](https://user-images.githubusercontent.com/30229752/71579556-6d799b00-2afd-11ea-85a4-85f0cb44fc04.jpg)

This Arduino based RC car handles two different modes to move:

- Autopilot: This is the default mode starting when the car is powered up. The car avoid obstacles on its own, using a motorized rotative head and an ultrasonic sensor to measure distances.

- Remote control: The user control the car movement using a bluetooth remote controller made with a joystick.  

_The joystick, when pressed, allow to toggle between autopilot and remote control mode._

> Remote controller ![IMG_8006](https://user-images.githubusercontent.com/30229752/71580276-38227c80-2b00-11ea-823a-9850581aee71.jpg)
![remote-controller](https://user-images.githubusercontent.com/30229752/71580451-01993180-2b01-11ea-8168-2cb39d8b1d1b.jpg)


Technical specifications:
The core of the car was built with items of a car kit gathering two solid frames, a UNO R3 board, 4 DC motors, a L298N driver, a micro servo (9g), an ultrasonic sensor, resistors and a power supply. Furthermore, two bluetooth modules, a joystick, an ATMega2560 board and an additional power supply were bought separately.
