<H1>ToF10120 Laser Range Sensor with OLED Display</H1>

This project uses a ToF10120 Laser Range Sensor to measure distance in (mm) and dispalys the readings on an OLED screen, via I²C inteface and the Serial interface.

It can measure distances from Liquids, as well as Solids, up to 2 metres away.

The code works on Arduino and other Microcontroller boards, for example with the Arduino IDE appl.

The code has been created, odified and adapted from https://www.electroniclinic.com/tof10120-laser-rangefinder-arduino-display-interfacing-code/ and original Chinese source,

<i>by Martin Glass December 2022 (c)</i>


<b>See this video demo : https://youtu.be/PnQWMkhcioA</b>

The design uses a simple connection system: the VCC (red), GND(black), Blue (SDA) and Green (SCL) wires from the TOF 10120 cable plug into the same pins of the OLED display. 4 wires of similar colours are soldered onto the OLED display pin ends, 

and then onto the Arduino VCC (5V), GND, SDA (pin A4), SCL (pin A5).

Power is supplied via the USB socket on the Arduino.

An STL file of the simple case design is also provided, for 3D printing.



<H1>Ideas for further development</H1>

Use an ESP32/M5 board to connect via WiFi, with the firmware providing a web server to feed live data to any device on the home network/internet.

Make a fixed position case to attach the ToF device to an Oil tank.

Use the dimensions of the Oil Tank to calculate litres of Oil consumed / volume remaining, woth mm accuracy.

Use a series of live readings to calculate the rate of oil consumption / time remaining, with mm accuracy.
