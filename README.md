# Sega Saturn Crontroller Input Demultiplexed to Discrete Outputs.

This is an Arduino sketch for demultiplexing Saturn controller inputs to discrete outputs. I desinged it for Arcade Supergun use but it could be adapted for use in many other control applications that require discrete outputs.

# Instructions

The upload the .ino file to an Arduino Uno or similar compatible device and connect the I/O pins according to the pinout below.

# Pinout (Arduino pin labels) 

  These values are hard coded and cannot be easily changed. This is because the code uses direct port maniplulation to set the button outputs to open drain when not pressed. This is a safety feature.

**Button Outputs**
  - UP    = 1
  - Select = 2
  - DOWN  = 4
  - LEFT  = 5
  - RIGHT = 6
  - X     = 7
  - Y     = 8
  - Z     = 9
  - A     = 10
  - START = 11  
  - B     = 13
  - C     = 12

**Digital Inputs**
- D1    = 14
- D0    = 15
- D3    = 18
- D2    = 19

**Select Outputs**
- S0    = 16
- S1    = 17

# Button Map Information

There are currently three buttonmap options. 
- Six Button Mode: X,Y,Z are mapped to P1,P2,P3 and A,B,C are mapped to K1,K2,K3. 
- Six Button Flipped: A,B,C are mapped to P1,P2,P3 and X,Y,Z are mapped to K1,K2,K3. 
- NEO GEO Mode: A,X,Y,Z are mapped to P1,P2,P3,K1 and B,C are mapped to K2,K3. This makes more sense for NEO GEO games when using an arcade stick with a six button layout. 

Switching buttonmaps is done by pressing and holding the following button combinations for 3 seconds:
- Six Button mode = START + A
- Six Button Flipped = START + B
- Neo-Geo mode = START + C

Buttonmap selection is saved to the EEPROM so it stays selected after powering off.

# Coin Button

Since the Saturn pad doesn't have a select button I have implemented a software solution for adding coins. There are 3 different coin mappings that can be toggled by holding L & R for 5 seconds. Simply toggle through them until you find the one you like best. The options are as follows

 - L + R + START = COIN
 - L = COIN
 - R = COIN

I've also added a combination that doesn't use the shoulder buttons since some users may not have access to them (custom arcade stick users for example) 
COIN = X + Y + Z + START



# EXPEREMENTAL BUTTON REMAPPING AND AUTOFIRE

In the code folder there is an arduino sketch labeled "saturn_controller_demux_remap.ino" This is an experemental firmware that eliminates the normal 3 buttonmap profiles in exchange for full fledged on the fly remapping of A,B,C,X,Y and Z. 

To enter button remapping mode hold any 2 face buttons and START simultaniously for 3 seconds.
Once in remapping mode press each button the corresponding number of times to achive the desired output based on the list below.

 - X = 1 press
 - Y = 2 presses
 - Z = 3 presses
 - A = 4 presses
 - B = 5 presses
 - C = 6 presses
 - N/A = 7 presses
 
 In the code folder there is another sketch labaled "saturn_controller_demux_remap_autofire.ino" This is an even more experemental firmware that has the same button remapping system as the above version, but also adds auto fire capability as well. 
 
 To enter auto fire programming mode hold any 1 face button and START simultaniously for 3 seconds. 
 Once in auto fire programming mode press each button that you want to set as auto fire the number of times that corresponds to the desired speed in the list below.
 
  - ~30hz = 1 press
  - ~20hz = 2 presses
  - ~15hz = 3 presses
  - ~12hz = 4 presses
  - ~7.5hz = 5 presses
  - ~6hz = 6 presses
  
Button mapping and auto fire settings are saved in the EEPROM so they will persist after power cycling the AVR.

# Retro-Bit Fix
I've added a special branch of the firmware implementing a number of timing changes to get Retro-Bit Wireless Saturn controllers working with these adapters. These changes have not been committed to the main branch of the firmware because they have also somehow broke Brook Retro Board compatibility. Until I figure out the source of that problem this will remain a separate branch of the firmware. 

This branch is dependent on the library "DigitalWriteFast" it can be found here. https://github.com/NicksonYap/digitalWriteFast

# Custom PCB Info.

I have designed several prototype PCBs for this project. Currently they are available as Saturn to DB15 adapters. They use the same DB15 pinout as Undamned's DB15 USB Decoders. You can order the most current version from <a href="https://oshpark.com/shared_projects/X40sm7os">Oshpark</a>
