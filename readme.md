This code is to use with ToF10120 Laser Range Sensor to measure distance in (mm) and dispalys the readings on an OLED screen, via I²C inteface and the Serial interface.

It can measure distances from Liquids, as well as Solids, up to 2 metres away.

Modified and adapted from https://www.electroniclinic.com/tof10120-laser-rangefinder-arduino-display-interfacing-code/ and original Chinese source,
by Martin Glass December 2022 (c)

see this video demo : https://youtu.be/PnQWMkhcioA

The design uses a simple connection system: the VCC (red), GND(black), Blue (SDA) and Green (SCL) wires from the TOF 10120 cable plug into the same pins of the OLED display. 4 wires of similar colours are soldered onto the OLED display pin ends, 

and then onto the Arduino VCC (5V), GND, SDA (pin A4), SCL (pin A5).

Power is supplied via the USB socket on the Arduino.

An STL file of the simple case design is also provided, for 3D printing.



Ideas for further development:

Use an ESP32/M5 board to connect via WiFi, with the firmware providing a web server to feed live data to any device on the home network/internet.

Make a fixed position case to attach the ToF device to an Oil tank.

Use the dimensions of the Oil Tank to calculate litres of Oil consumed / volume remaining, woth mm accuracy.

Use a series of live readings to calculate the rate of oil consumption / time remaining, with mm accuracy.
