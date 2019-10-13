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
int remapcount = 0;
int remapcombo = 0;
int combodelay = 80;
int NB = 0;

//Buttonmap Values
int XO = 1;
int YO = 2;
int ZO = 3;
int AO = 4;
int BO = 5;
int CO = 6;

int XP = 0;
int YP = 0;
int ZP = 0;
int AP = 0;
int BP = 0;
int CP = 0;

int XC = 0;
int YC = 0;
int ZC = 0;
int AC = 0;
int BC = 0;
int CC = 0;
int STP = 0;

void setup() {
  pinMode(D0, INPUT_PULLUP);     // Declares D0-3 as inputs with internal pullup.
  pinMode(D1, INPUT_PULLUP);
  pinMode(D2, INPUT_PULLUP);
  pinMode(D3, INPUT_PULLUP);
  pinMode(S0, OUTPUT);           // Declares Select Pins as outputs.
  pinMode(S1, OUTPUT);
 
XO = EEPROM.read(0);
YO = EEPROM.read(1);
ZO = EEPROM.read(2);
AO = EEPROM.read(3);
BO = EEPROM.read(4);
CO = EEPROM.read(5);
}


void loop(){                     // The main loop of the program. Calls all of the other loops as needed.
  
  demuxpad();                    // Runs the pad demux operation to collect buttonpress data from the controller

  buttoncombos();                // Runs the button combination check.  
if (buttonmap == 1){             // Stores output data for PORTB and PORTD based on sixbutton map.
  buttonmapping();
}else{
  setoutputs();
  }
  DDRB = outputb;                // Sets PORTB and PORTD outputs based on inputs and the chosen buttonmap.
  DDRD = outputd;
}


void setoutputs(){           // Translates demuxpad data into the sixbutton output map.

if (Y == 2 || X == 2 || Z == 2 || A == 2 || B == 2 || C == 2)
  outputb |= 1;                    
if (Z == 3 || Y == 3 || X == 3 || A == 3 || B == 3 || C == 3)
  outputb |= 2; 
if (A == 4 || Y == 4 || X == 4 || Z == 4 || B == 4 || C == 4)
  outputb |= 4;    
if (ST == 1) 
  outputb |= 8;
if (C == 6 || Y == 6 || X == 6 || Z == 6 || A == 6 || B == 6)
  outputb |= 16;
if (B == 5 || Y == 5 || X == 5 || Z == 5 || A == 5 || C == 5) 
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
if (X == 1 || Y == 1 || Z == 1 || A == 1 || B == 1 || C == 1) 
  outputd |= 128;    
}




void demuxpad(){               // Does the heavy lifting of demuxing the data from the controller into buttonpresses.

outputb = 0;
outputd = 0;
UP = 0;
DN = 0;
LT = 0;
RT = 0;
SL = 0;
STP = ST;
ST = 0;
NB = 0;
XP = XC;
YP = YC;
ZP = ZC;
AP = AC;
BP = BC;
CP = CC;
XC = 0;
YC = 0;
ZC = 0;
AC = 0;
BC = 0;
CC = 0;
X = 0;
Y = 0;
Z = 0;
A = 0;
B = 0;
C = 0;

  {                             // This is the start of the first bit of the demuxer, there are four of these
  delay(1);
  digitalWrite(S1, LOW);
  digitalWrite(S0, HIGH);       // Sets the select lines S0 HIGH, S1 LOW
  
  }
  val = digitalRead(D0);        // read input value from data line
  if (val == LOW) {             // check if the data input is LOW (button pressed)
  B = BO;                        // Stores the B button as pressed.
  BC = 1;                     
  }
  val = digitalRead(D1); 
  if (val == LOW) {       
  C = CO;
  CC = 1;
  }
  val = digitalRead(D2);
  if (val == LOW) {       
  A = AO;
  AC = 1;
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
  Z = ZO;
  ZC = 1;
  }
  val = digitalRead(D1); 
  if (val == LOW) {      
  Y = YO;
  YC = 1;
  }
  val = digitalRead(D2);
  if (val == LOW) {       
  X = XO;
  XC = 1;
  }
  val = digitalRead(D3); 
  if (val == LOW) {           
  R = 1;  
  }else{R = 0;
  }                             // This is the end of the second bit of the demuxer.       
          { 
  delay(1);                     // This is the start of the third bit of the demuxer.
  digitalWrite(S1, HIGH);       // Sets the select lines S0 HIGH, S1 HIGH
  digitalWrite(S0, HIGH);  

  }
  val = digitalRead(D3); 
  if (val == LOW) {      
  L = 1;                     
  }  else{L = 0;
  }                          // This is the end of the third bit of the demuxer. 
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

NB = (XC + YC + ZC + AC + BC + CC);

} 

void buttoncombos(){
if ((NB == 3 && (ST == 1)) || (L == 1 && (ST == 1 && (R ==1)))){       // Checks if X,Y,Z and Start or L, R and Start are all pressed
  SL = 1;                       // Sets Select as pressed
  ST = 0;                       // Sets Start as pressed
}

if (ST == 1 && (NB == 2 && (remapcombo == 1))){       // Checks if B and Start are both pressed
  remapcount = (remapcount + 1);
}

if (ST == 1 && (NB == 2)){       // Checks if A and Start are both pressed
remapcombo = 1;
}else{ 
  remapcombo = 0;
  remapcount = 0;
}

if (remapcount >= combodelay){
remapcount = 0;
buttonmap = 1;                // Sets buttonmap mode to 1 
 }
}

void buttonmapping(){
if (ST == 1 && (NB == 2)){
 XO = 0;
 YO = 0;
 ZO = 0;
 AO = 0;
 BO = 0;
 CO = 0;
}else{
if (XC == 1 && (XP == 0 && (NB == 1 && XO < 6))){
  XO = (XO + 1);
}else if (XC == 1 && (XP == 0 && (NB == 1 && XO == 6))){
  XO = 0;
  }
if (YC == 1 && (YP == 0 && (NB == 1 && YO < 6))){
  YO = (YO + 1);
}else if (YC == 1 && (YP == 0 && (NB == 1 && YO == 6))){
  YO = 0;
  }
if (ZC == 1 && (ZP == 0 && (NB == 1 && ZO < 6))){
  ZO = (ZO + 1);
}else if (ZC == 1 && (ZP == 0 && (NB == 1 && ZO == 6))){
  ZO = 0;
  }
if (AC == 1 && (AP == 0 && (NB == 1 && AO < 6))){
  AO = (AO + 1);
}else if (AC == 1 && (AP == 0 && (NB == 1 && AO == 6))){
  AO = 0;
  }
if (BC == 1 && (BP == 0 && (NB == 1 && BO < 6))){
  BO = (BO + 1);
}else if (BC == 1 && (BP == 0 && (NB == 1 && BO == 6))){
  BO = 0;
  }  
if (CC == 1 && (CP == 0 && (NB == 1 && CO < 6))){
  CO = (CO + 1);
}else if (CC == 1 && (CP == 0 && (NB == 1 && CO == 6))){
  CO = 0;
  }
if (ST == 1 && (STP == 0)){
    buttonmap = 0;
    EEPROM.write(0,XO);
    EEPROM.write(1,YO);
    EEPROM.write(2,ZO);
    EEPROM.write(3,AO);
    EEPROM.write(4,BO);
    EEPROM.write(5,CO);
    
  } 
 }
}
