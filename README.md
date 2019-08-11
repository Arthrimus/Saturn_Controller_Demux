# Sega Saturn Crontroller Input Demultiplexed to Discrete Outputs.

This is an Arduino sketch for demultiplexing Saturn controller inputs to discrete outputs. I desinged it for Arcade Supergun use but it could be adapted for use in many other control applications that require discrete outputs.

# Instructions

The upload the .ino file to an Arduino Uno or similar compatible device and connect the I/O pins according to the layout described in the .ino file. If you wish to remap the buttons you can modify the pin selections in the file to suit your needs. There are 2 versions uploaded here v0.1 and v0.6. V0.1 is configured correctly to match the pinout of my original V0.1-V0.3 boards. I reworked the board layout at v0.4 onward so if you have board revision V0.4 or newer you should use the V0.6 code.

# Pinout (Arduino pin labels) 

  These values are hard coded and cannot be easily changed. This is because the code uses direct port maniplulation to set the button outputs to open drain when not pressed. This is a safety feature.

Button Outputs
-UP    = 1
-L     = 2
-R     = 3
-DOWN  = 4
-LEFT  = 5
-RIGHT = 6
-X     = 7
-Y     = 8
-Z     = 9
-A     = 10
-START = 11  
-B     = 13
-C     = 12

Digital Inputs
D1    = 14
D0    = 15
D3    = 18
D2    = 19

Select Outputs
S0    = 16
S1    = 17

# Button Map Information

There are currently two buttonmap options. Six Button mode is standard operation. X,Y,Z are mapped to P1,P2,P3 and A,B,C are mapped to K1,K2,K3. In NEO GEO mode A,X,Y,Z are mapped to P1,P2,P3,K1 and B,C are mapped to K2,K3. This makes more sense for NEO GEO games when using an arcade stick with a six button layout. 

Switching buttonmaps is done by pressing the following button combinations:
Six Button mode = START + A
Neo-Geo mode = START + B

# Select Button

Since the Saturn pad doesn't have a select button I have implemented a software solution that can be access by pressing the following button combination: START + Z

# Custom PCB Info.

I have designed several prototype PCBs for this project. Currently they are available as Saturn to DB15 adapters. They use the same DB15 pinout as Undamned's DB15 USB Decoders. You can order the most current version from <a href="https://oshpark.com/shared_projects/9CTTduIO">Oshpark</a>
