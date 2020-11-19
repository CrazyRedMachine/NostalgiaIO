# NostalgiaIO

Arduino Leonardo firmware for arcade Nostalgia control panel, for official cabinets and home setups

## Arduino firmware

The arduino can communicate with an acio device on the serial interface, but in order to do so **it needs RS232 to TTL conversion**. I use a HW-027 rs232 to TTL adapter which is based around the MAX3232 chip.

## Pinout 

There's one 8 pin connector coming out of the keyboard unit. We will use only 5 of the pins from that connector

### MAX3232 RS232 to TTL converter

### Using an Arduino

**TODO** Faire un diagramme de connection Piano <-> MAX3232 <-> Arduino

## Usage

Set your USB serial device to COM1 and run the game


## APPENDIX : Simple mode

The piano is an ACIO device, which means it uses RS232 protocol to communicate with the computer.

Therefore in order to use it you need to use an RS232 to USB adapter. Beware not to take a simple "USB to TTL" as this won't work (you can use such adapter if you also add a RS232 to TTL converter, see more details in the Arduino firmware section).

### Pinout

Color | Pin | Piano | RS232 to USB
--- | --- | --- | ---
Black | 1 | GND | GND | 
Red | 2 | +5V | +5V
Green  | 3 | RXDA0 | TX
. | 4 |  | 
Blue  | 5 | TXDA0 | RX
. | 6 |  |
Black | 7 | GND | GND
. | 8 |  |

### Configuration

You need to configure the adapter so the piano is on COM1.

You also need to configure a KFCA and ICCC device on a second acio device on COM2 (you might use [ACreal_IO](https://github.com/Nadeflore/ACreal_IO/) for that)

## TODO

- Write a leonardo firmware so one can modeswitch between midi keyboard, pc keyboard, hid multitouch (and with light effects) to play on PC version and android games as well.

- Write a forwarder binary to keypresses so that real cab can play Op3 PC version as well.
