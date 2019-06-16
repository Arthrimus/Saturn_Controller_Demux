# Sega Saturn Crontroller Input Demultiplexed to Discrete Outputs.

This is an Arduino sketch for demultiplexing Saturn controller inputs to discrete outputs. I desinged it for Arcade Supergun use but it could be adapted for use in many other control applications that require discrete outputs.

# Instructions

The upload the .ino file to an Arduino Uno or similar compatible device and connect the I/O pins according to the layout described in the .ino file. If you wish to remap the buttons you can modify the pin selections in the file to suit your needs. There are 2 versions uploaded here v0.1 and v0.6. V0.1 is configured correctly to match the pinout of my original V0.1-V0.3 boards. I reworked the board layout at v0.4 onward so if you have board revision V0.4 or newer you should use the V0.6 code.

# Custom PCB Info.

I have designed several prototype PCBs for this project. Currently they are available as Saturn to DB15 adapters. They use the same DB15 pinout as Undamned's DB15 USB Decoders. You can order the most current version from <a href="https://oshpark.com/shared_projects/9CTTduIO">Oshpark</a>
