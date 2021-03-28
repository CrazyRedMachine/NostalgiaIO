# NostalgiaIO

Arduino Leonardo firmware and tools for arcade Nostalgia control panel, for official cabinets and home setups

This Readme covers the Arduino firmware only. Find out more about tools in the tools folder readme.

## Acknowledgments

ACIO layer code based on Bemanitools 5.

Multitouch support is based on Eric Troebs' [Touchy.ino](https://gist.github.com/erictroebs/3e6ca8aa2b9ed06e0b5527fd38dd2c2f) (https://github.com/NicoHood/HID/issues/123)

MIDI support is based on Gary Grewal's [MIDIUSB Library](https://github.com/arduino-libraries/MIDIUSB)

## Demo

https://www.instagram.com/p/CH4IKxJl1pu/

## Features

It is recommended to use a latching switch for the MODE button.

### ACIO (native) mode (plug the device while MODE is on)

In this mode the arduino is pretty much disabled and acts as a passthrough, so that the original data can interact with your device. It's useful if you modded your cab hardware and want to use the extended features for other games but still retain native compatibility with Nostalgia.

Note that you'll have to manually set the Arduino COM port to COM1 for it to work as the game will only look for the device there and will spawn a KEYBOARD ERROR if not found.

Also note that the Test/Coin/Service buttons from the arduino cannot work in this mode, as in the native mode the game will look for them on the KFCA board :

You need to have one KFCA and one ICCC node on a second acio device on COM2 (you can either use another RS232 to USB adapter for your original hardware, or you might use [ACreal_IO](https://github.com/CrazyRedMachine/ACreal_IO) to simulate them with an arduino MEGA)

### MIDI mode (plug the device while MODE is switched off)

In this mode the panel is a MIDI keyboard (with only white keys). This was mainly developped for use with the PC version of Nostalgia, or as a way to remap the inputs in original data if you want to play with the enhanced light modes. 

The midi keyboard will work with Synthesia or any midi-enabled music software, but the missing black keys will ruin your experience in most cases.

### Multitouch mode (switch MODE to on after booting in MIDI mode)

In this mode the panel acts like virtual touchpresses along the bottom edge of the screen. This was mainly developped for use with "Pianista", but might work for other android games too (**note**: this is untested on IOS).

- Presses go along the bottom edge of the screen (10% from bottom edge).

And to facilitate menu navigation in some games :

- While holding TEST button, presses go along the center line (50%)
- While holding COIN button, presses go along the top edge (10% from top edge)

### HID Lights

All panel lights can be controlled with HID messages. Lightmodes and palette can be selected with HID messages as well.
The HID lights are accessible in MIDI and Multitouch mode but cannot be accessed while in native mode.

#### Light modes and palettes

There are a lot of cool lightmodes available. 
You can set the mode either by sending a HID message (see `NostModeSwitch` executable/script), or by holding service and pressing the leftmost piano key.

All modes (except rainbow modes) also have several color palettes available which can be switched either by `NostModeSwitch` or by holding service and pressing the 2nd leftmost piano key.

Manual mode and palette switch (ie. using service + piano key button) are automatically saved to the Arduino EEPROM.

Most modes also support HID messages and will keep lighting keys (it is disabled in Rainbow mode due to performance).

##### HID (with reactive fallback)

Light behavior is dictated only by HID messages. After several seconds without any received HID message, the panel falls back into "reactive mode" (ie. illuminate on key press). It switches back to HID as soon as HID messages come back.

##### Combined

HID messages OR Pressed keys light them up.

##### Invert

Panel is always lit, pressing a key turns that key lighting off.

##### Interlace

Pressed keys illuminate in 3 different colors.

##### Rainbow

A rainbow wave runs on the panel while pressed keys turn off.

##### Wave

A single-color wave runs on the panel, while a different color illuminates the pressed keys.

##### Breath

The panel periodically illuminates in a fade in fade out effect, while a different color illuminates the pressed keys.

##### Fade out

Keys light up as you press them then slowly fade out once they are released.

##### Velocity Fade out

This is like fade out except the color is determined by how hard you press the key.

##### Rainbow fade out

This is like fade out except it draws rainbows (and holding keys makes a great color shifting effect).

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

### Additional buttons

Button | Arduino
--- | --- 
MODE | A3
SERVICE | 5
TEST (touch center) | 6
COIN (touch upper) | 7

Unlike the rest of this pinout, these SERVICE/TEST/COIN/MODE buttons can be freely moved to other GPIO by editing the `#define PIN_*` at the beginning of `NostalgiaIO.ino`, as well as `#define UPPER_PIN` and `#define CENTER_PIN` at the beginning of `NOSTHID.cpp`

## WIP Features

- [Misc.] ~~Write a forwarder binary to keypresses so that real cab can play Op3 PC version as well without having to use an arduino.~~
(Op3 PC version cannot run on Win7 Embedded, so there's no real incentive to do this for now.)
