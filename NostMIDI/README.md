[![Donate](https://img.shields.io/badge/Donate-PayPal-green.svg)](https://www.paypal.com/donate?hosted_button_id=WT735CX4UMZ9U)

# NostMIDI (ACIO to MIDI software solution)

This tool is a mod of my PANB handler for aciotest (as found in [Bemanitools 5](https://github.com/djhackersdev/bemanitools/) ).

It allows you to run Konaste version of Nostalgia on a real cab without any extra hardware requirement.

## Acknowledgments

ACIO handling code based on Bemanitools 5.
MIDI handling code makes use of Tobias Erichsen's teVirtualMIDI driver.

## How to use

Konaste Nostalgia runs on Windows 10 only, so you'll need a fresh install on your cab in order to use it.

It is recommended to use a second hard drive and swap it in the cab.

- Install Windows 10 on your HDD
- Install [teVirtualMIDI kernel driver](https://www.tobias-erichsen.de/wp-content/uploads/2020/01/teVirtualMIDISDKSetup_1_3_0_43.zip)
- Make sure the piano is still plugged on COM1 on your new install
- Run nostmidi.exe and let it detect your panel and create the midi device
- Select "Nostalgia ACIO MIDI Interface" as your input device in Konaste
- Enjoy

## Donation

If this project helps you and you want to give back, you can help me with my future projects.

While not necessary, donations are much appreciated and will only go towards funding future github projects (arcade hardware ain't cheap :( ).

Of course you'll also receive my gratitude and I'll remember you if you post a feature request ;)

[![paypal](https://www.paypalobjects.com/en_US/i/btn/btn_donateCC_LG.gif)](https://www.paypal.com/donate?hosted_button_id=WT735CX4UMZ9U)
