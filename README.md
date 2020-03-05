# Charleslab's rocketery

Thrust vectoring is the ability of an aircraft, rocket, or other vehicle to manipulate the direction of the thrust from its motor in order to control the attitude (angle) of the vehicle. It is used in rocketry it is the primary means of attitude control, as aerodynamic control surfaces are ineffective outside the atmosphere.

This repository contains all resources for my model rocketery experiments. The content of each folder is described hereunder.

Everything is work in progress (currently working on the code and the gimbal).

## 3D models

This folder contains the 3D models for my rocket:
* The 2 axes thrust vectoring control (TVC) gimbal (SolidWorks),
* The gimbal test stand (OpenSCAD parametric design),
* The PCB holder (OpenSCAD parametric design),
* The nose cone (OpenSCAD parametric design).

TODO : add render of all models

The gimbal is a 3D-printable, parametric Solidworks model. There are two variables that should be adjusted to fit your needs: the diameter of the rocket motor and the diameter of the rocket body. The geometry adapts to these constraints. It should be 3D-printed with supports enabled.

TODO : add photo

The cone is a work-in-progress parametric openSCAD model.

## Electronics

The "Sagan" PCB is my rocket's onboard computer. It features:
* Arduino Mini (ATMega328P at 3.3v),
* BMP280 barometer,
* MPU6050 gyroscope and accelerometer,
* Micro SD Card reader to store in-flight telemetry,
* 3 servo outputs (X, Y and extra),
* 2 pyro channels (PYRO0 and PYRO1),
* LED and buzzer.

TODO : add picture

Designed in KiCad.

## Code

This folder contains the Arduino code for the "Sagan" PCB.

To tune and test the controller, I made a Java gimbaled rocket simulator: http://charleslabs.fr/en/project-Gimbaled+Model+Rocket+Simulator

## Flight data

This folder holds the data (telemetry) for each flight of the rocket.