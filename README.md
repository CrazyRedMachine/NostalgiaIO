# NostalgiaIO

Arduino Leonardo firmware for arcade Nostalgia control panel, for official cabinets and home setups

## Features

### ACIO (native) mode

In this mode the arduino acts as a passthrough, so that the original data can interact with your device. It's useful if you modded your cab hardware and want to use the extended features for other games but still retain native compatibility with Nostalgia.

Note that you'll have to manually set the Arduino COM port to COM1 for it to work as the game will only look for the device there.

You also need to have one KFCA and one ICCC node on a second acio device on COM2 (you might use [ACreal_IO](https://github.com/Nadeflore/ACreal_IO/) for that)

### HID Gamepad mode

In this mode the panel is a 31 button, 31 RGB HID light gamepad. It allows use with tools or other games.

### Touchscreen mode

In this mode the panel acts like virtual touchpresses along the bottomedge of the screen, this was mainly developped for use with "Deemo", but might work for other android games too.

## Pinout

The arduino can communicate with an acio device on the Serial1 (pins 0 and 1) interface, but in order to do so **it needs RS232 to TTL conversion**. I use a HW-027 rs232 to TTL adapter which is based around the MAX3232 chip and is very cheap and easy to find (amazon, aliexpress, etc..)

**BEWARE**: Please use the arduino 3.3V pin to power the HW-027 adapter, as most often than not, powering the chip with 5V will cause it to overheat and stop working

There's one 8 pin connector coming out of the keyboard unit. We will use only 5 of the pins from that connector (2 of them to power the keyboard directly from the arduino, and the other 3 of them through the RS232 adapter) 

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

- Write a leonardo firmware so one can modeswitch between midi keyboard, pc keyboard, hid multitouch (and with light effects) to play on PC version and android games as well.

- Write a forwarder binary to keypresses so that real cab can play Op3 PC version as well.
