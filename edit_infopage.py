# This file (edit_infopage.py) is public domain or CC-0 licensed, have fun.

# This tool takes a file containing the infopage from a ZBS243 device and inserts the device MAC address (8-bytes), the AES key for pairing (16-bytes) and the PAN identifier (2-bytes) into the file.

import sys, os

masterkey = bytearray.fromhex("D306D9348E29E5E358BF2934812002C1")
pan = [ int(panid.strip(), 16) for panid in os.environ.get("EPS_PANID", default="0x47, 0x44").split(",") ]

with open("dump_infopage.bin", "rb") as f:
	d = bytearray(f.read())

print("MAC?")
macstring = input()
mac = bytearray.fromhex(macstring)
if len(mac) != 6:
	print("Wrong length!")
	sys.exit(1)

offset = 16
for i in range(2):
	d[offset+i] = 0xFF
offset += 2

for i in range(6):
	d[offset+i] = mac[5-i]
offset += 6

for i in range(16):
	d[offset+i] = masterkey[i]
offset += 16

for i in range(2):
	d[offset+i] = pan[i]
offset += 2

with open("dump_infopage.bin", "wb") as f:
	f.write(d)
