 /* Saturn Controller Demux
 * ------------------ 
 * This sketch is designed to demux Sega Saturn gamepad
 * signals into descrete outputs for use with arcade 
 * PCBs. 
 * 
 * There are two select lines, four data input lines, and
 * 12 discrete outputs.
 * 
 * This is a much cleaner implementation of the Saturn pad Demux code.
 * Many improvements have been made such as setting outputs as open drain,
 * removing unneccesary if/else statements, implementation of button 
 * combo based functions such as select/coin, buttonmap switching between
 * standard 6 button and Neo Geo 4 button modes. 
 * 
 * Arthrimus August 4 2019
 *
 */

#include <EEPROM.h>

int UP = 0;                      // Sets up button press values. 0 = button not pressed, 1 = button pressed.
int DN = 0; 
int LT = 0;
int RT = 0;
int A = 0;
int B = 0;
int C = 0;
int X = 0;
int Y = 0;
int Z = 0;
int L = 0;
int R = 0;
int ST = 0;   
int SL = 0;

int D0 = 15;                     // choose the input pins for the digital inputs, follows Arduino pinout.
int D1 = 14;
int D2 = 19;
int D3 = 18;
int S0 = 16;                     // Chooses the output pins for the select outputs, follows Arduino pinout.
int S1 = 17;  

int val = 0;                     // variable for reading the pin status (should be zero)
int outputb = 0;                 // variable for storing PORTB output values.
int outputd = 0;                 // variable for storing PORTD output values.
int buttonmap = 0;               // variable for storing which buttonmap is used for outputs, 0 = sixbuttonmode.
int sbcombo = 0;
int sbfcombo = 0;
int ngcombo = 0;
int sbcount = 0;
int sbfcount = 0;
int ngcount = 0;
int combodelay = 80;
int addr = 0;

void setup() {
  pinMode(D0, INPUT_PULLUP);     // Declares D0-3 as inputs with internal pullup.
  pinMode(D1, INPUT_PULLUP);
  pinMode(D2, INPUT_PULLUP);
  pinMode(D3, INPUT_PULLUP);
  pinMode(S0, OUTPUT);           // Declares Select Pins as outputs.
  pinMode(S1, OUTPUT);

  buttonmap = EEPROM.read(0);
 }


void loop(){                     // The main loop of the program. Calls all of the other loops as needed.
  
  demuxpad();                    // Runs the pad demux operation to collect buttonpress data from the controller

  buttoncombos();                // Runs the button combination check.  
if (buttonmap == 0){             // Stores output data for PORTB and PORTD based on sixbutton map.
  sixbuttonmode();}

if (buttonmap == 1){
  sixbuttonflipped();}

if (buttonmap == 2){             // Stores output data for PORTB and PORTD based on neogeo map.
  neogeomode();}

  DDRB = outputb;                // Sets PORTB and PORTD outputs based on inputs and the chosen buttonmap.
  DDRD = outputd;
}


void sixbuttonmode(){           // Translates demuxpad data into the sixbutton output map.

if (Y == 1)
  outputb |= 1;                    
if (Z == 1)
  outputb |= 2; 
if (A == 1)
  outputb |= 4;    
if (ST == 1) 
  outputb |= 8;
if (C == 1)
  outputb |= 16;
if (B == 1) 
  outputb |= 32;    
if (UP == 1)
  outputd |= 2;                    
if (SL == 1)
  outputd |= 4;
if (DN == 1)
  outputd |= 16;           
if (LT == 1)   
  outputd |= 32;
if (RT == 1)
  outputd |= 64;
if (X == 1) 
  outputd |= 128;    
}

void sixbuttonflipped(){           // Translates demuxpad data into the sixbutton output map.

if (B == 1)
  outputb |= 1;                    
if (C == 1)
  outputb |= 2; 
if (X == 1)
  outputb |= 4;    
if (ST == 1) 
  outputb |= 8;
if (Z == 1)
  outputb |= 16;
if (Y == 1) 
  outputb |= 32;    
if (UP == 1)
  outputd |= 2;                    
if (SL == 1)
  outputd |= 4;
if (DN == 1)
  outputd |= 16;           
if (LT == 1)   
  outputd |= 32;
if (RT == 1)
  outputd |= 64;
if (A == 1) 
  outputd |= 128;    
}

void neogeomode(){              // Translates demuxpad data into the neogeo output map.

if (X == 1)
  outputb |= 1;                    
if (Y == 1)
  outputb |= 2; 
if (Z == 1)
  outputb |= 4;    
if (ST == 1) 
  outputb |= 8;
if (C == 1)
  outputb |= 16;
if (B == 1) 
  outputb |= 32;    
if (UP == 1)
  outputd |= 2;                    
if (SL == 1)
  outputd |= 4;
if (DN == 1)
  outputd |= 16;           
if (LT == 1)   
  outputd |= 32;
if (RT == 1)
  outputd |= 64;
if (A == 1) 
  outputd |= 128;    
}


void demuxpad(){               // Does the heavy lifting of demuxing the data from the controller into buttonpresses.

outputb = 0;
outputd = 0;
UP = 0;
DN = 0;
LT = 0;
RT = 0;
A = 0;
B = 0;
C = 0;
X = 0;
Y = 0;
Z = 0;
L = 0;
R = 0;
ST = 0;
SL = 0;

  
  {                             // This is the start of the first bit of the demuxer, there are four of these
  delay(1);
  digitalWrite(S1, LOW);
  digitalWrite(S0, HIGH);       // Sets the select lines S0 HIGH, S1 LOW
  
  }
  val = digitalRead(D0);        // read input value from data line
  if (val == LOW) {             // check if the data input is LOW (button pressed)
  B = 1;                        // Stores the B button as pressed.
  }
  val = digitalRead(D1); 
  if (val == LOW) {       
  C = 1;
  }
  val = digitalRead(D2);
  if (val == LOW) {       
  A = 1;
  }
  val = digitalRead(D3); 
  if (val == LOW) {      
  ST = 1;
  }                              // This is the end of the first bit of the demuxer.

{                                // This is the start of the second bit of the demuxer.
  delay(1);
  digitalWrite(S1, LOW);         // Sets the select lines S0 LOW, S1 LOW
  digitalWrite(S0, LOW);         
  }
    val = digitalRead(D0);
  if (val == LOW) {       
  Z = 1;
  }
  val = digitalRead(D1); 
  if (val == LOW) {      
  Y = 1;
  }
  val = digitalRead(D2);
  if (val == LOW) {       
  X = 1;
  }
  val = digitalRead(D3); 
  if (val == LOW) {           
  R = 1;  
  }                             // This is the end of the second bit of the demuxer.       
          { 
  delay(1);                     // This is the start of the third bit of the demuxer.
  digitalWrite(S1, HIGH);       // Sets the select lines S0 HIGH, S1 HIGH
  digitalWrite(S0, HIGH);  

  }
  val = digitalRead(D3); 
  if (val == LOW) {      
  L = 1;                     
  }                            // This is the end of the third bit of the demuxer. 
   {                           // This is the start of the fourth bit of the demuxer.
  delay(17);
  digitalWrite(S1, HIGH);      // Sets the select lines S0 LOW, S1 HIGH
  digitalWrite(S0, LOW);   

  }
    val = digitalRead(D0); 
  if (val == LOW) {       
  UP = 1;
  }
  val = digitalRead(D1); 
  if (val == LOW) {      
  DN = 1;
  }
  val = digitalRead(D2);
  if (val == LOW) {       
  LT = 1;
  }
  val = digitalRead(D3); 
  if (val == LOW) {      
  RT = 1;
  }                             // This is the end of the fourth bit of the demuxer. 


  } 

void buttoncombos(){
if (Z == 1 && (ST == 1)){       // Checks if Z and Start are both pressed
  SL = 1;                       // Sets Select as pressed
  Z = 0;                        // Sets Z as not pressed
  ST = 0;
}


if (ST == 1 && (A == 1 && (sbcombo == 1))){       // Checks if A and Start are both pressed
  sbcount = (sbcount + 1);
}

if (ST == 1 && (B == 1 && (sbfcombo == 1))){       // Checks if B and Start are both pressed
  sbfcount = (sbfcount + 1);
}

if (ST == 1 && (C == 1 && (ngcombo == 1))){       // Checks if C and Start are both pressed
  ngcount = (ngcount + 1);
}

if (ST == 1 && (A == 1)){       // Checks if A and Start are both pressed
sbcombo = 1;
}else{ 
  sbcombo = 0;
  sbcount = 0;
}
if (ST == 1 && (B == 1)){       // Checks if A and Start are both pressed
sbfcombo = 1;
}else{ 
  sbfcombo = 0;
  sbfcount = 0;
}

if (ST == 1 && (C == 1)){      // Checks if B and Start are both pressed
ngcombo = 1;
}else{ 
  ngcombo = 0;
  ngcount = 0;
}

if (sbcount >= combodelay){
sbcount = 0;
buttonmap = 0;                // Sets buttonmap to 0 (sixbuttonmode)              
EEPROM.write(0, 0);
}

if (sbfcount >= combodelay){
sbfcount = 0;
buttonmap = 1;                // Sets buttonmap to 0 (sixbuttonmode)    
EEPROM.write(0, 1);          
}

if (ngcount >= combodelay){
ngcount = 0;
buttonmap = 2;                // Sets buttonmap to 1 (neogeomode)
EEPROM.write(0, 2);
}
}
