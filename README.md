# NostalgiaIO

Tools and notes on using a Nostalgia control panel, for official cabinets and home setups

## Firmware

No need for any firmware for now, you can use any USB to TTL converter (for example an Arduino Uno with the RESET pin shorted to GND)

## Pinout 

There's one 8 pin connector coming out of the keyboard unit. We will use only 5 of the pins from that connector

### Using an USB to TTL

Color | Pin | Piano | USB to TTL
--- | --- | --- | ---
Black | 1 | GND | GND | 
Red | 2 | +5V | +5V
Green  | 3 | RXDA0 | TX
. | 4 |  | 
Blue  | 5 | TXDA0 | RX
. | 6 |  |
Black | 7 | GND | GND
. | 8 |  |

### Using an Arduino

**Notes:** 
- Piano RX goes to RX and TX to TX, this is not a mistake (with an Arduino used this way, RX and TX have to be swapped as they are from the atmega chip POV rather than the onboard USB to TTL chip POV)
- No need to flash any firmware on the arduino, just keeping reset shorted to gnd will hold the arduino into USB to TTL mode

Color | Pin | Piano | Arduino
--- | --- | --- | ---
Black | 1 | GND | GND | 
Red | 2 | +5V | +5V
Green  | 3 | RXDA0 | 0 (RX)
. | 4 |  | 
Blue  | 5 | TXDA0 | 1 (TX)
. | 6 |  |
Black | 7 | GND | GND
. | 8 |  |

You also have to connect Arduino **RST** pin to **GND**

## Usage

Set your USB serial device to COM1 and run the game

## TODO

- Write a leonardo firmware so one can modeswitch between midi keyboard, pc keyboard, hid multitouch (and with light effects) to play on PC version and android games as well.

- Write a forwarder binary to keypresses so that real cab can play Op3 PC version as well.
