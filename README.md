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

# Coin Button

Since the Saturn pad doesn't have a select button I have implemented a software solution for adding coins. Coin can be triggered by pressing any 3 face buttons and Start simultaniously. This combination of buttons will cancel out the Start button press so Coin and Start cannot be triggered simultaniously in this way. There is also support for mapping coin to any of the 6 face buttons or shoulder buttons. When mapped to any of these buttons Coin does not cancel out Start, so they can both be pressed simultaniously. 


# BUTTON REMAPPING AND AUTOFIRE

The now standard firmware supports button remapping and autofire settings for all 6 face buttons and both triggers.

To enter button remapping mode hold any 2 face buttons and START simultaniously for 3 seconds.
Once in remapping mode press each button the corresponding number of times to achive the desired output based on the list below.

 - X = 1 press
 - Y = 2 presses
 - Z = 3 presses
 - A = 4 presses
 - B = 5 presses
 - C = 6 presses
 - Coin = 7 presses
 - N/A = 8 presses

 To enter auto fire programming mode hold any 1 face button and START simultaniously for 3 seconds. 
 Once in auto fire programming mode press each button that you want to set as auto fire the number of times that corresponds to the desired speed in the list below.
 
  - ~30hz = 1 press
  - ~20hz = 2 presses
  - ~15hz = 3 presses
  - ~12hz = 4 presses
  - ~7.5hz = 5 presses
  - ~6hz = 6 presses
  - N/A = 7 presses
  
Button mapping and auto fire settings are saved in the EEPROM so they will persist after power cycling the AVR.

# Retro-Bit Fix (NOW STANDARD)
I've added a special branch of the firmware implementing a number of timing changes to get Retro-Bit Wireless Saturn controllers working with these adapters. These changes have not been committed to the main branch of the firmware because they have also somehow broke Brook Retro Board compatibility. Until I figure out the source of that problem this will remain a separate branch of the firmware. 

This branch is dependent on the library "DigitalWriteFast" it can be found here. https://github.com/NicksonYap/digitalWriteFast

# Custom PCB Info.

I have designed several prototype PCBs for this project. Currently they are available as Saturn to DB15 adapters. You can find the most up to date version in the root of the PCB folder of this repository.
