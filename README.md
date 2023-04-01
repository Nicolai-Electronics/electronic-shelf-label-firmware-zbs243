# Custom firmware for ZBS243 based Solum electronic shelf labels

This firmware for a modification of the custom firmware by Dmitri Grinbergs which allows for the pre-shared network key and PAN identifier to be set using the settings page in flash. The repository contains a small tool (`edit_infopage.py`) which inserts the MAC address, a PSK and a PAN identifier of your choosing into a dump of the infopage of a shelf label device. Once paired the network key and PAN identifier of the network paired to will remain set even after power loss, this allows the device to quickly reconnect to any coordinator which has the same nework key and PAN identifier combination set. The device will enter a pairing mode after starting up, displaying the currently configured network key and PAn identifier on the display.

## Building

This firmware supports multiple targets:

| Target                 | Size  | Colors      | Resolution |
| ---------------------- | ----- | ----------- | ---------- |
| zbs154v033             | 1.54" | red & black | 152x152    |
| zbs29v033              | 2.9"  | red & black | 128x296    |
| zbs29v033_BW           | 2.9"  | black only  | 128x296    |
| zbs42v033              | 4.2"  | red & black | 400x300    |

```
make BUILD=zbs154v033 clean
make BUILD=zbs154v033
```

## Flashing

Get `zbs_flasher.py` from https://github.com/atc1441/ZBS_Flasher

```
python ./zbs_flasher.py -p /dev/ttyUSB0 read-infopage dump_infopage.bin
python edit_infopage.py
python ./zbs_flasher.py -p /dev/ttyUSB0 write main.bin
python ./zbs_flasher.py -p /dev/ttyUSB0 write-infopage dump_infopage.bin
```

## Authors

This firmware has been created by Dmitry Grinbergs and was modified by Nicolai Electronics.

Dmitry Grinbergs original version of this firmware can be found here:
http://dmitry.gr/?r=05.Projects&proj=29.%20eInk%20Price%20Tags

A modified version by atc1441 can be found here:
https://github.com/atc1441/ZBS_Flasher

## License

This code/data/waveforms are free for use in hobby and other non-commercial products.

For commercial use contact Dmitry Grinbergs: <licensing@dmitry.gr>

Anyone (at the time of use) associated with "badge.team",  "Stichting Ifcat foundation" or "Nicolai Electronics" may use the code published at "http://dmitry.gr/?r=05.Projects&proj=29.%20eInk%20Price%20Tags" for any purpose they see fit. This license is revocable and non-transferable. It includes no warranty that said code is fit for any purpose.
