# ATI Task

> this project is an ATI Task.

## Table of Contents

- [ATI Task](#ati-task)
  - [Table of Contents](#table-of-contents)
  - [General Information](#general-information)
  - [Technologies Used](#technologies-used)
  - [Features](#features)
  - [Screenshots](#screenshots)
  - [Setup](#setup)
  - [Room for Improvement](#room-for-improvement)
  - [Acknowledgements](#acknowledgements)
  - [Contact](#contact)

## General Information

- Developed with CubeIDE
- the code is flashed on STM32F103C8T6 microcontroller (BlueBill)
- here we used FreeRTOS as 3rd party package for **OS**
- coded on Ubuntu Machine

## Technologies Used

- CubeIDE - version 1.0
- Ubuntu 21.10 - version 3.0

## Features

- Receive stream of data Over Uart
- function contains checks for string existence inside a tring to just exact match

## Screenshots

![Schmatic](Circuit%20schematic.png)

## Setup

Just install CubeIDE and any Serial Port Viewer Ide to See Uart messages, Here we used **Energia Serial Port** Window along with **Tiva-C**.

## Room for Improvement

- we can enhance an EXTI signal with adding a capacitor over this pin.
- if we would have more time, we can refactor RockBlock module for more speed and less code.

## Acknowledgements

- Many thanks to **ST community** and awesmoe and clear **Data sheet** of st micro electronics

## Contact

Created by [@hazemkhaled](https://www.linkedin.com/in/hazem-khaled-90898315a/)

also the project is save to my github [@hazem3443](https://github.com/hazem3443)
