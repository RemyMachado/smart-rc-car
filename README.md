# smart-rc-car :car::satellite:
_This project was handmade. No third party libraries were used._
![elegoo-car](https://user-images.githubusercontent.com/30229752/200054391-4df97e44-1ab0-4eb7-ad9f-a0ad7b96e68e.jpg)

This Arduino based RC car handles two different modes to move:

- Autopilot: This is the default mode starting when the car is powered up. The car avoid obstacles on its own, using a motorized rotative head and an ultrasonic sensor to measure distances.

- Remote control: The user control the car movement using a bluetooth remote controller made with a joystick.  

_The joystick, when pressed, allow to toggle between autopilot and remote control mode._

> Remote controller ![remote-controller-open](https://user-images.githubusercontent.com/30229752/200054551-08b04c74-5d56-4f15-b309-154bd687dfcf.jpg)
![remote-controller-closed](https://user-images.githubusercontent.com/30229752/200054624-cb9b3ee6-cf35-4540-8963-4180449f47b8.jpg)


Technical specifications:
The core of the car was built with items of a car kit gathering two solid frames, a UNO R3 board, 4 DC motors, a L298N driver, a micro servo (9g), an ultrasonic sensor, resistors and a power supply. Furthermore, two bluetooth modules, a joystick, an ATMega2560 board and an additional power supply were bought separately.
