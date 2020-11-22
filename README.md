# NostalgiaIO

Arduino Leonardo firmware and tools for arcade Nostalgia control panel, for official cabinets and home setups

This Readme covers the arduino firmware only. Find out more about tools in the tools folder readme.

## Acknowledgments

Multitouch support is based on Eric Troebs' [Touchy.ino](https://gist.github.com/erictroebs/3e6ca8aa2b9ed06e0b5527fd38dd2c2f) (https://github.com/NicoHood/HID/issues/123)

## Demo

https://www.instagram.com/p/CH4IKxJl1pu/

## Features

It is recommended to use a latching switch for the MODE button.

### ACIO (native) mode (plug the device while MODE is on)

In this mode the arduino acts as a passthrough, so that the original data can interact with your device. It's useful if you modded your cab hardware and want to use the extended features for other games but still retain native compatibility with Nostalgia.

Note that you'll have to manually set the Arduino COM port to COM1 for it to work as the game will only look for the device there.

You also need to have one KFCA and one ICCC node on a second acio device on COM2 (you can either use another RS232 to USB adapter for your original hardware, or you might use [ACreal_IO](https://github.com/Nadeflore/ACreal_IO/) to simulate them)

### HID Gamepad mode (plug the device while MODE is off)

In this mode the panel is a 31 button, 31 RGB HID light gamepad. It allows use with tools or other games.

### Multitouch mode (set MODE button to on after booting in HID mode)

In this mode the panel acts like virtual touchpresses along the bottomedge of the screen, this was mainly developped for use with "Deemo", but might work for other android games too (**note**: this is untested on IOS).

### Light modes

Once again there are a lot of lightmodes available. 

#### Reactive

#### HID only

#### Combined

#### Interlace

#### Rainbow

#### Chase

#### Breath

## Pinout

The arduino can communicate with an acio device on the Serial1 (pins 0 and 1) interface, but in order to do so **it needs RS232 to TTL conversion**. I use a HW-027 rs232 to TTL adapter which is based around the MAX3232 chip and is very cheap and easy to find (amazon, aliexpress, etc..)

**BEWARE**: Please use the arduino 3.3V pin to power the HW-027 adapter, as most often than not, powering the chip with 5V will cause it to overheat and stop working

There's one 8 pin connector coming out of the keyboard unit. We will use only 5 of the pins from that connector (2 of them to power the keyboard directly from the arduino, and the other 3 of them through the RS232 adapter). You can use 2.8mm female QD (same as those used for small arcade buttons) to connect on the pins from that connector

![pinout](https://github.com/CrazyRedMachine/NostalgiaIO/blob/main/nostalgia-pinout.png?raw=true)

Color | Pin | Keyboard | RS232 | TTL | Arduino
--- | --- | --- | --- | --- | ---
Black | 1 | GND |  | | GND
Red | 2 | +5V | | | +5V
Green  | 3 | RXDA0 | <- (TX) | <- (RX) | 1 
. | 4 |  | | |
Blue  | 5 | TXDA0 | -> (RX) | -> (TX) | 0  
. | 6 |  | |
Black | 7 | GND | - (GND) | - (GND) | GND 
. | 8 |  | |
.| | | | + (3.3V) | +3.3V

**Note:** Make sure to wire the keyboard to the RS232 side of the adapter, and the arduino to the TTL side. Use the 3.3v pin to power the MAX3232 chip **from the TTL side**.

## Usage

TODO

## TODO

- Write a forwarder binary to keypresses so that real cab can play Op3 PC version as well.
