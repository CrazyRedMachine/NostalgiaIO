[![Donate](https://img.shields.io/badge/Donate-PayPal-green.svg)](https://www.paypal.com/donate?hosted_button_id=WT735CX4UMZ9U)

# NostalgiaIO

Arduino Leonardo firmware and tools for arcade Nostalgia control panel, for official cabinets and home setups

## Acknowledgments

ACIO layer code based on Bemanitools 5.

MIDI support is based on Gary Grewal's [MIDIUSB Library](https://github.com/arduino-libraries/MIDIUSB)

## Demo

### Impressive play by pro gamer EXP on Nostalgia Op 3 (PC)

https://www.youtube.com/watch?v=mbT5lQpTMFw

### Firmware running on a fullsize cab

https://www.instagram.com/p/COM2fmKIh7q/

### A couple light effects

https://www.instagram.com/p/CH4IKxJl1pu/

## Features

It is recommended to use a latching switch for the MODE button.

### MIDI mode (plug the device while MODE is switched off)

This is the firmware default mode (you can also access it by not wiring a mode switch at all if you are not interested in multitouch mode)

In this mode the panel is a MIDI keyboard (with only white keys). This was mainly developped for use with the PC version of Nostalgia, or as a way to remap the inputs in original data if you want to play with the enhanced light modes. 

The midi keyboard will work with Synthesia or any midi-enabled music software, but the missing black keys will ruin your experience in most cases.

### ACIO (native) mode (plug the device while holding SERVICE button)

In this mode the arduino is pretty much disabled and acts as a passthrough, so that the original data can interact with your device. It's useful if you modded your cab hardware and want to use the extended features for other games but still retain native compatibility with Nostalgia.

Note that you'll have to manually set the Arduino COM port to COM1 for it to work as the game will only look for the device there and will spawn a KEYBOARD ERROR if not found.

Also note that the Test/Coin/Service buttons from the arduino cannot work in this mode, as in the native mode the game will look for them on the KFCA board :

You need to have one KFCA and one ICCC node on a second acio device on COM2 (you can either use another RS232 to USB adapter for your original hardware, or you might use [ACreal_IO](https://github.com/CrazyRedMachine/ACreal_IO) to simulate them with an arduino MEGA)

### HID Lights

All panel lights can be controlled with HID messages. Lightmodes and palette can be selected with HID messages as well.
The HID lights are accessible in MIDI and Multitouch under win7 but cannot be accessed while in native mode, nor in multitouch under win10.
    
#### Light modes and palettes

There are a lot of cool lightmodes available. 
You can set the mode either by sending a HID message (see `NostModeSwitch` executable/script), or by **holding service and pressing the leftmost piano key**.

All modes also have several color palettes available which can be switched either by `NostModeSwitch` or by **holding service and pressing the 2nd leftmost piano key**.

Manual mode and palette switch (ie. using service + piano key button) are automatically saved to the Arduino EEPROM.

Most modes also support HID messages and will keep lighting keys.

##### HID (with reactive fallback)

Light behavior is dictated only by HID messages. After several seconds without any received HID message, the panel falls back into "reactive mode" (ie. illuminate on key press). It switches back to HID as soon as HID messages come back.

##### Combined

HID messages OR Pressed keys light them up.

##### Invert

Panel is always lit, pressing a key turns that key lighting off.

##### Fade out

Keys light up as you press them then slowly fade out once they are released.

##### Velocity Fade out

This is like fade out except the color is determined by how hard you press the key.

## Pinout

The arduino can communicate with an acio device on the Serial1 (pins 0 and 1) interface, but in order to do so **it needs RS232 to TTL conversion**. 

There's one big white 8 pin connector (JST YL**R**-08V) coming out of the keyboard unit. We will use only 5 of the pins from that connector (2 of them to power the keyboard directly from the arduino, and the other 3 of them through the RS232 adapter). 

You can buy the matching connector, JST YL**P**-08V, with SYF-01T-P0.5A crimps (SYF-41T-P0.5A will do to but theoretically is made for thicker wires so you might have trouble crimping them), that will plug into the piano connector.

Or you can use 2.8mm female QD (same as those used for small arcade buttons) to connect directly to the pins inside the YL**R**-08V, that should work well and QD are much more easily available.

![qd](https://github.com/CrazyRedMachine/NostalgiaIO/blob/main/nostalgia-qd.png?raw=true)

### HW-027

The HW-027 rs232 to TTL adapter which is based around the MAX3232 chip is very cheap and easy to find (amazon, aliexpress, etc..)

**BEWARE**: Please use the arduino 3.3V pin to power the HW-027 adapter, as most often than not, powering the chip with 5V will cause it to overheat and stop working.

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

### Keyestudio RS232 arduino shield

If you don't want to solder on a small chip, this rs232 adapter shield is also based around the max3232 chip and easy to find (amazon, aliexpress, etc..)

![pinout_shield](https://github.com/CrazyRedMachine/NostalgiaIO/blob/main/nostalgia-pinout-shield.png?raw=true)

### Additional buttons

Button | Arduino
--- | --- 
MODE | A3
SERVICE | 5
TEST | 6
COIN | 7

Unlike the rest of this pinout, these SERVICE/TEST/COIN/MODE buttons can be freely moved to other GPIO by editing the `#define PIN_*` at the beginning of `NostalgiaIO.ino`

## Appendix: spicetools config

To help speed up the mapping process under spicetools, rather than mapping everything by hand, edit `%appdata%\spicetools.xml` (**make a copy first in case anything goes wrong**), then find the line containing `<game name="Nostalgia">`, up until the next occurrence of `</game>`, and replace the whole thing by this block instead :
   
```
    <game name="Nostalgia">
        <buttons>
            <button name="Service" vkey="96" analogtype="0" devid=";MIDI;0;Arduino Leonardo;65535;65535"/>
            <button name="Test" vkey="97" analogtype="0" devid=";MIDI;0;Arduino Leonardo;65535;65535"/>
            <button name="Coin Mech" vkey="98" analogtype="0" devid=";MIDI;0;Arduino Leonardo;65535;65535"/>
            <button name="Key 1" vkey="48" analogtype="0" devid=";MIDI;0;Arduino Leonardo;65535;65535"/>
            <button name="Key 2" vkey="50" analogtype="0" devid=";MIDI;0;Arduino Leonardo;65535;65535"/>
            <button name="Key 3" vkey="52" analogtype="0" devid=";MIDI;0;Arduino Leonardo;65535;65535"/>
            <button name="Key 4" vkey="53" analogtype="0" devid=";MIDI;0;Arduino Leonardo;65535;65535"/>
            <button name="Key 5" vkey="55" analogtype="0" devid=";MIDI;0;Arduino Leonardo;65535;65535"/>
            <button name="Key 6" vkey="57" analogtype="0" devid=";MIDI;0;Arduino Leonardo;65535;65535"/>
            <button name="Key 7" vkey="59" analogtype="0" devid=";MIDI;0;Arduino Leonardo;65535;65535"/>
            <button name="Key 8" vkey="60" analogtype="0" devid=";MIDI;0;Arduino Leonardo;65535;65535"/>
            <button name="Key 9" vkey="62" analogtype="0" devid=";MIDI;0;Arduino Leonardo;65535;65535"/>
            <button name="Key 10" vkey="64" analogtype="0" devid=";MIDI;0;Arduino Leonardo;65535;65535"/>
            <button name="Key 11" vkey="65" analogtype="0" devid=";MIDI;0;Arduino Leonardo;65535;65535"/>
            <button name="Key 12" vkey="67" analogtype="0" devid=";MIDI;0;Arduino Leonardo;65535;65535"/>
            <button name="Key 13" vkey="69" analogtype="0" devid=";MIDI;0;Arduino Leonardo;65535;65535"/>
            <button name="Key 14" vkey="71" analogtype="0" devid=";MIDI;0;Arduino Leonardo;65535;65535"/>
            <button name="Key 15" vkey="72" analogtype="0" devid=";MIDI;0;Arduino Leonardo;65535;65535"/>
            <button name="Key 16" vkey="74" analogtype="0" devid=";MIDI;0;Arduino Leonardo;65535;65535"/>
            <button name="Key 17" vkey="76" analogtype="0" devid=";MIDI;0;Arduino Leonardo;65535;65535"/>
            <button name="Key 18" vkey="77" analogtype="0" devid=";MIDI;0;Arduino Leonardo;65535;65535"/>
            <button name="Key 19" vkey="79" analogtype="0" devid=";MIDI;0;Arduino Leonardo;65535;65535"/>
            <button name="Key 20" vkey="81" analogtype="0" devid=";MIDI;0;Arduino Leonardo;65535;65535"/>
            <button name="Key 21" vkey="83" analogtype="0" devid=";MIDI;0;Arduino Leonardo;65535;65535"/>
            <button name="Key 22" vkey="84" analogtype="0" devid=";MIDI;0;Arduino Leonardo;65535;65535"/>
            <button name="Key 23" vkey="86" analogtype="0" devid=";MIDI;0;Arduino Leonardo;65535;65535"/>
            <button name="Key 24" vkey="88" analogtype="0" devid=";MIDI;0;Arduino Leonardo;65535;65535"/>
            <button name="Key 25" vkey="89" analogtype="0" devid=";MIDI;0;Arduino Leonardo;65535;65535"/>
            <button name="Key 26" vkey="91" analogtype="0" devid=";MIDI;0;Arduino Leonardo;65535;65535"/>
            <button name="Key 27" vkey="93" analogtype="0" devid=";MIDI;0;Arduino Leonardo;65535;65535"/>
            <button name="Key 28" vkey="95" analogtype="0" devid=";MIDI;0;Arduino Leonardo;65535;65535"/>
        </buttons>
        <analogs>
            <analog name="Key 1" index="255" sensivity="1" devid="" invert="false" smoothing="false"/>
            <analog name="Key 2" index="255" sensivity="1" devid="" invert="false" smoothing="false"/>
            <analog name="Key 3" index="255" sensivity="1" devid="" invert="false" smoothing="false"/>
            <analog name="Key 4" index="255" sensivity="1" devid="" invert="false" smoothing="false"/>
            <analog name="Key 5" index="255" sensivity="1" devid="" invert="false" smoothing="false"/>
            <analog name="Key 6" index="255" sensivity="1" devid="" invert="false" smoothing="false"/>
            <analog name="Key 7" index="255" sensivity="1" devid="" invert="false" smoothing="false"/>
            <analog name="Key 8" index="255" sensivity="1" devid="" invert="false" smoothing="false"/>
            <analog name="Key 9" index="255" sensivity="1" devid="" invert="false" smoothing="false"/>
            <analog name="Key 10" index="255" sensivity="1" devid="" invert="false" smoothing="false"/>
            <analog name="Key 11" index="255" sensivity="1" devid="" invert="false" smoothing="false"/>
            <analog name="Key 12" index="255" sensivity="1" devid="" invert="false" smoothing="false"/>
            <analog name="Key 13" index="255" sensivity="1" devid="" invert="false" smoothing="false"/>
            <analog name="Key 14" index="255" sensivity="1" devid="" invert="false" smoothing="false"/>
            <analog name="Key 15" index="255" sensivity="1" devid="" invert="false" smoothing="false"/>
            <analog name="Key 16" index="255" sensivity="1" devid="" invert="false" smoothing="false"/>
            <analog name="Key 17" index="255" sensivity="1" devid="" invert="false" smoothing="false"/>
            <analog name="Key 18" index="255" sensivity="1" devid="" invert="false" smoothing="false"/>
            <analog name="Key 19" index="255" sensivity="1" devid="" invert="false" smoothing="false"/>
            <analog name="Key 20" index="255" sensivity="1" devid="" invert="false" smoothing="false"/>
            <analog name="Key 21" index="255" sensivity="1" devid="" invert="false" smoothing="false"/>
            <analog name="Key 22" index="255" sensivity="1" devid="" invert="false" smoothing="false"/>
            <analog name="Key 23" index="255" sensivity="1" devid="" invert="false" smoothing="false"/>
            <analog name="Key 24" index="255" sensivity="1" devid="" invert="false" smoothing="false"/>
            <analog name="Key 25" index="255" sensivity="1" devid="" invert="false" smoothing="false"/>
            <analog name="Key 26" index="255" sensivity="1" devid="" invert="false" smoothing="false"/>
            <analog name="Key 27" index="255" sensivity="1" devid="" invert="false" smoothing="false"/>
            <analog name="Key 28" index="255" sensivity="1" devid="" invert="false" smoothing="false"/>
        </analogs>
        <lights>
            <light name="Title R" index="0" devid=""/>
            <light name="Title G" index="0" devid=""/>
            <light name="Title B" index="0" devid=""/>
            <light name="Bottom R" index="0" devid=""/>
            <light name="Bottom G" index="0" devid=""/>
            <light name="Bottom B" index="0" devid=""/>
            <light name="Key 1 R" index="41" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 1 G" index="40" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 1 B" index="39" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 2 R" index="38" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 2 G" index="37" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 2 B" index="36" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 3 R" index="35" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 3 G" index="34" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 3 B" index="33" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 4 R" index="32" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 4 G" index="31" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 4 B" index="30" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 5 R" index="29" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 5 G" index="28" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 5 B" index="27" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 6 R" index="26" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 6 G" index="25" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 6 B" index="24" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 7 R" index="23" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 7 G" index="22" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 7 B" index="21" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 8 R" index="20" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 8 G" index="19" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 8 B" index="18" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 9 R" index="17" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 9 G" index="16" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 9 B" index="15" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 10 R" index="14" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 10 G" index="13" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 10 B" index="12" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 11 R" index="11" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 11 G" index="10" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 11 B" index="9" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 12 R" index="8" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 12 G" index="7" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 12 B" index="6" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 13 R" index="5" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 13 G" index="4" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 13 B" index="3" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 14 R" index="2" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 14 G" index="1" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 14 B" index="0" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 15 R" index="83" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 15 G" index="82" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 15 B" index="81" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 16 R" index="80" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 16 G" index="79" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 16 B" index="78" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 17 R" index="77" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 17 G" index="76" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 17 B" index="75" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 18 R" index="74" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 18 G" index="73" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 18 B" index="72" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 19 R" index="71" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 19 G" index="70" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 19 B" index="69" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 20 R" index="68" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 20 G" index="67" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 20 B" index="66" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 21 R" index="65" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 21 G" index="64" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 21 B" index="63" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 22 R" index="62" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 22 G" index="61" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 22 B" index="60" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 23 R" index="59" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 23 G" index="58" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 23 B" index="57" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 24 R" index="56" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 24 G" index="55" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 24 B" index="54" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 25 R" index="53" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 25 G" index="52" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 25 B" index="51" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 26 R" index="50" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 26 G" index="49" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 26 B" index="48" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 27 R" index="47" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 27 G" index="46" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 27 B" index="45" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 28 R" index="44" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 28 G" index="43" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
            <light name="Key 28 B" index="42" devid="\\?\HID#VID_2341&amp;PID_8036&amp;MI_02#7&amp;b5b0acb&amp;0&amp;0000#{4d1e55b2-f16f-11cf-88cb-001111000030}"/>
        </lights>
        <options/>
    </game>
```

**Note:** the string in quotes after `devid=` is your device path. It might differ in your install, so if that doesn't work, manually map one of your lights then use find/replace option to replace my devid with yours.

## WIP Features

- [Misc.] Write an auto-config app
- [Misc.] ~~Write a forwarder binary to keypresses so that real cab can play Op3 PC version as well without having to use an arduino.~~
(DONE, checkout NostMIDI folder)

## Donation

If this project helps you and you want to give back, you can help me with my future projects.

While not necessary, donations are much appreciated and will only go towards funding future github projects (arcade hardware ain't cheap :( ).

Of course you'll also receive my gratitude and I'll remember you if you post a feature request ;)

[![paypal](https://www.paypalobjects.com/en_US/i/btn/btn_donateCC_LG.gif)](https://www.paypal.com/donate?hosted_button_id=WT735CX4UMZ9U)
