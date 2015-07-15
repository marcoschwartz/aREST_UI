# aREST_UI

Version 1.0.0

## Overview

aREST UI is an embedded UI for the aREST framework. Currently works with the Arduino Mega & Arduino Due with the CC3000 WiFi chip, the WiFi shield, and the Ethernet shield. It works as well with the WildFire v3 board.

It also works with the ESP8266 WiFi chip.

## Contents

- aREST_UI.h: the library file.
- examples: several examples using the aREST UI library

## Requirements

To use the library with Arduino boards you will need the latest version of the Arduino IDE:

- [Arduino IDE 1.6.5](http://arduino.cc/en/main/software)

You will also need the aREST library:

- [aREST](https://github.com/marcoschwartz/aREST)

### For WiFi using the CC3000 chip

- [Adafruit CC3000 Library](https://github.com/adafruit/Adafruit_CC3000_Library)
- [Adafruit MDNS Library](https://github.com/adafruit/CC3000_MDNS)
- MDNS support in your operating system:
  - For OS X it is supported through Bonjour, you don't have anything to install.
  - For Linux, you need to install [Avahi](http://avahi.org/).
  - For Windows, you need to install [Bonjour](http://www.apple.com/support/bonjour/).

## Setup

To install the library, simply clone this repository in the /libraries folder of your Arduino folder.

## Quick test (WiFi)

1. Connect a LED & resistor to pin number 6 of your Arduino Mega board
2. Open the WiFi_CC3000 example sketch and modify the WiFi SSID and password
3. Upload the sketch to the board
4. Go to a web browser and type `http://arduino.local`
5. Click on the 'On' button and the LED should turn on

## Quick test (WildFire)

1. Connect a LED & resistor to pin number 6 of your WildFire board
2. Open the WildFire example sketch and modify the WiFi SSID and password
3. Upload the sketch to the board
4. Go to a web browser and type `http://wildfire.local`
5. Click on the 'On' button and the LED should turn on

## API documentation

### Create aREST UI instance

You can simply create an instance of aREST UI with the following command:

`aREST_UI ui = aREST_UI();`

### Button

Buttons are used to control the state of a digital output pin. The command creates two button inside the interface, one 'On' button, and one 'Off' button. For example, the following command creates a pair of buttons to control pin number 6:

`ui.button(6)`

### Slider

The slider command creates a slider to control a pin via PWM. For example, it can be used to control the intensity of a LED connected to this pin. The following command creates a pair of buttons to control pin number 6:

`ui.slider(6)`;

### Label

Labels are used to display the value of variables inside the interface. Before you can use this command, you need to create the corresponding variable first. The following command declares a variable called temperature:

`ui.variable("temperature",&temperature);`

After that, you can use the following command to create the corresponding label inside the interface:

`ui.label("temperature")`;
