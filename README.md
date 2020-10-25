# NostalgiaIO

Tools and notes on using a Nostalgia control panel, for official cabinets and home setups

## Native mode

The piano is an ACIO device, which means it uses RS232 protocol to communicate with the computer.

Therfore in order to use it you need to use an RS232 to USB adapter (I'm using a Sabrent DB-9 RS-232 USB 2.0 adapter). Beware not to take a simple "USB to TTL" as this won't work (you can use such adapter if you also add a RS232 to TTL converter, see more details in the Arduino firmware section).

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

You also need to configure a KFCA and ICCA device on a second acio device on COM2.

## Enhanced mode (Arduino firmware)

The arduino can communicate with an acio device on the serial interface, but in order to do so **it needs RS232 to TTL conversion**.

## Pinout 

There's one 8 pin connector coming out of the keyboard unit. We will use only 5 of the pins from that connector

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
