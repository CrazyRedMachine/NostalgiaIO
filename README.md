# NostalgiaIO

Notes on using a Nostalgia control panel on PC

## Materials

You can use any USB to TTL converter (for example an Arduino Uno with the RESET pin shorted to GND)

## Pinout (Arduino)

There's one 8 pin connector coming out of the keyboard unit.

**Note:** Piano RX goes to RX and TX to TX, this is not a mistake (with an Arduino used this way, RX and TX have to be swapped as they are from the atmega chip POV rather than the onboard USB to TTL chip)

Color | Pin | Piano | Arduino
--- | --- | --- | ---
Black | 1 | GND | GND | 
Red | 2 | +5V | +5V
Green  | 3 | RXDA0 | RX
. | 4 |  | 
Blue  | 5 | TXDA0 | TX
. | 6 |  |
Black | 7 | GND | GND
. | 8 |  |

You also have to connect Arduino **RST** pin to **GND**
