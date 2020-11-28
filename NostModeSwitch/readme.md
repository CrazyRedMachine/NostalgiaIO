# NostModeSwitch for NostalgiaIO

This is a binary meant to set the LightMode and palette used by NostalgiaIO in HID mode. It is mostly useful for multi-boot frontends as it allows to switch to the correct mode before launching a game.

For ease of use I included pre-compiled binaries. It's easier to modify the ahk version to suit your needs but I'm still including a C version as with Pop'n, in case you have trouble running the ahk version on a real cab or something.

## Usage

```NostModeSwitch.exe <num> <palette>```

Where ``<num>`` can take the value

0 : Mixed (HID-only when messages come, fallback to reactive when HID messages stop coming)

1 : Combined (HID + button presses)

2 : Invert (ON is OFF and vice-versa)

3 : Interlace (pressed keys illuminate in 3 different colors)

4 : Rainbow (rainbow wave runs on the panel while pressed keys turn off)

5 : Wave (single-color wave on the panel, while a different color illuminates the pressed keys)

6 : Breath (periodic fade in fade out effect on panel, while a different color illuminates the pressed keys)

7 : Fade (keys light up as you press them then slowly fade out once they are released)

8 : Velocity Fade (same as fade but key velocity determines color)

9 : Rainbow Fade (same as fade but color gradually shifts along the rainbow spectrum)

and ``<palette>`` can take the value

0 : Original arcade palette

1 : Alternate palette

2 : RGB palette

## How it works

On the NostalgiaIO firmware, there is a secondary HID output report with ID 6, meant to trigger a modeswitch and palette switch.

This binary opens the USB device whose path is written in ```devicepath.dat``` and sends the correct HID report.

The autohotkey version finds the path automatically based on VID=2341 and PID=8036.

## How to retrieve devicepath (for the C version)

The included devicepath.dat should work out of the box, but in case you get the message ``Couldn't open device. Make sure devicepath.dat contains the correct path.`` and you are sure the device is plugged in, you can either go into windows device manager and look for the device path in the advanced properties of your arduino device, or the easiest way is to look at the value inside spicetools configuration file.

devicepath.dat file should contain the device path on its own on a single line. Multiple paths on multiple lines should work too in which case it will open the first valid path it finds.

If no valid path is found or if there is no `devicepath.dat` file, it will attempt to open the default path from the Leonardo firmware (same as the one found in this included devicepath file).
 
### spicetools

open ```%appdata%/spicetools.xml```, look for a "devid" value starting with ```\\?\HID#VID_2341&amp;PID_8036``` (Leonardo)

Note that you'll have to replace "```&amp;```" occurrences by "```&```".
