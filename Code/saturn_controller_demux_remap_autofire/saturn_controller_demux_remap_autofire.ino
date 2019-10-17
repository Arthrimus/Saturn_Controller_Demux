 /* Saturn Controller Demux
 * ------------------ 
 * This sketch is designed to demux Sega Saturn gamepad
 * signals into descrete outputs for use with arcade 
 * PCBs. 
 * 
 * There are two select lines, four data input lines, and
 * 12 discrete outputs.
 * 
 * 
 * Arthrimus October 13th 2019
 *
 */

#include <EEPROM.h>

//Buttonpress Status Variables
int UP = 0;                      // Sets up button press variables.
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
// Digital Pins (Arduino)
int D0 = 15;                     // choose the input pins for the digital inputs, follows Arduino pinout.
int D1 = 14;
int D2 = 19;
int D3 = 18;
// Select Pins (Arduino)
int S0 = 16;                     // Chooses the output pins for the select outputs, follows Arduino pinout.
int S1 = 17;  
// General Variables
int val = 0;                     // variable for reading the pin status (should be zero)
int outputb = 0;                 // variable for storing PORTB output values.
int outputd = 0;                 // variable for storing PORTD output values.
int buttonmap = 0;               // variable for storing which buttonmap is used for outputs, 0 = sixbuttonmode.
int remapcount = 0;              // variable for storing the count for the button combo timer
int remapcombo = 0;              // variable for storing the button combo state
int autofire = 0;
int autofirecombo = 0;
int autofirecount = 0;
int autofiretimer1 = 0;
int autofiretimer2 = 0;
int autofiretimer3 = 0;
int autofiretimer4 = 0;
int autofiretimer5 = 0;
int autofiretimer6 = 0;
int combodelay = 160;             // variable for storing the number of cycles for the combo timer
int combodelay2 = 220;           // variable for storing the number of cycles for combo timer 2
int SLcount = 0;                 // variable for storing the count for the select mode combo timer
int NB = 0;                      // variable for storing the number of face buttons pressed simultaniously.
int SLST = 0;
//Buttonmap Values
int XO = 1;                      // Stores the current output map for each input
int YO = 2;
int ZO = 3;
int AO = 4;
int BO = 5;
int CO = 6;
//Autofire Values
int XA = 0;                      // Stores the current autofire setting for each input
int YA = 0;
int ZA = 0;
int AA = 0;
int BA = 0;
int CA = 0;
// Previous Buttonpress Variables
int XP = 0;                     // Stores the previous state of each button
int YP = 0;
int ZP = 0;
int AP = 0;
int BP = 0;
int CP = 0;
int LP = 0;
int RP = 0;
// Current Buttonpress Variables
int XC = 0;                    // Stores the current state of each button
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
SLST = EEPROM.read(6);
XA = EEPROM.read(7);
YA = EEPROM.read(8);
ZA = EEPROM.read(9);
AA = EEPROM.read(10);
BA = EEPROM.read(11);
CA = EEPROM.read(12);

}


void loop(){                     // The main loop of the program. Calls all of the other loops as needed.
  
  demuxpad();                    // Runs the pad demux operation to collect buttonpress data from the controller

  buttoncombos();                // Runs the button combination check.  
if (buttonmap == 1){             // Stores output data for PORTB and PORTD based on sixbutton map.
  autofire = 0;
  buttonmapping();
}else if (autofire == 1){
  autofiremapping();
}else{
  setautofire();
  setoutputs();
  }
  DDRB = outputb;                // Sets PORTB and PORTD outputs based on inputs and the chosen buttonmap.
  DDRD = outputd;
}

void setautofire(){
autofiretimer1 = (autofiretimer1 + 1);
autofiretimer2 = (autofiretimer2 + 1);
autofiretimer3 = (autofiretimer3 + 1);
autofiretimer4 = (autofiretimer4 + 1);
autofiretimer5 = (autofiretimer5 + 1);
autofiretimer6 = (autofiretimer6 + 1);

if (autofiretimer1 > 1){
  autofiretimer1 = 0; 
}
if (autofiretimer2 > 2){
  autofiretimer2 = 0; 
}
if (autofiretimer3 > 3){
  autofiretimer3 = 0; 
}
if (autofiretimer4 > 5){
  autofiretimer4 = 0; 
}
if (autofiretimer5 > 7){
  autofiretimer5 = 0; 
}
if (autofiretimer6 > 9){
  autofiretimer6 = 0; 
}

if ((XA == 1 && autofiretimer1 < 1) || (XA == 2 && autofiretimer2 < 2) || (XA == 3 && autofiretimer3 < 2) || (XA == 4 && autofiretimer4 < 3) || (XA == 5 && autofiretimer5 < 4) || (XA == 6 && autofiretimer6 < 5)){
    X = 0;     
  }
if ((YA == 1 && autofiretimer1 < 1) || (YA == 2 && autofiretimer2 < 2) || (YA == 3 && autofiretimer3 < 2) || (YA == 4 && autofiretimer4 < 3) || (YA == 5 && autofiretimer5 < 4) || (YA == 6 && autofiretimer6 < 5)){
    Y = 0;     
  }
if ((ZA == 1 && autofiretimer1 < 1) || (ZA == 2 && autofiretimer2 < 2) || (ZA == 3 && autofiretimer3 < 2) || (ZA == 4 && autofiretimer4 < 3) || (ZA == 5 && autofiretimer5 < 4) || (ZA == 6 && autofiretimer6 < 5)){
    Z = 0;     
  }  
if ((AA == 1 && autofiretimer1 < 1) || (AA == 2 && autofiretimer2 < 2) || (AA == 3 && autofiretimer3 < 2) || (AA == 4 && autofiretimer4 < 3) || (AA == 5 && autofiretimer5 < 4) || (AA == 6 && autofiretimer6 < 5)){
    A = 0;     
  }
if ((BA == 1 && autofiretimer1 < 1) || (BA == 2 && autofiretimer2 < 2) || (BA == 3 && autofiretimer3 < 2) || (BA == 4 && autofiretimer4 < 3) || (BA == 5 && autofiretimer5 < 4) || (BA == 6 && autofiretimer6 < 5)){
    B = 0;     
  }
if ((CA == 1 && autofiretimer1 < 1) || (CA == 2 && autofiretimer2 < 2) || (CA == 3 && autofiretimer3 < 2) || (CA == 4 && autofiretimer4 < 3) || (CA == 5 && autofiretimer5 < 4) || (CA == 6 && autofiretimer6 < 5)){
    C = 0;     
  }
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

// New Previous State 
XP = XC;                      // new previous state variables = old current state variables
YP = YC;
ZP = ZC;
AP = AC;
BP = BC;
CP = CC;
LP = L;
RP = R;
STP = ST;
// Reset All Variables
outputb = 0;                   // Resets Port Maniplulation Variables
outputd = 0;
UP = 0;                        // Resets all button state variables
DN = 0;
LT = 0;
RT = 0;
SL = 0;
ST = 0;
NB = 0;
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
  delay(13);
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
if (ST == 1){
  SLcount = 0;  
}
if ((NB == 3 && (ST == 1)) || (L == 1 && (ST == 1 && (R == 1 && SLST == 0))) || (L == 1 && SLST == 1) || (R == 1 && SLST == 2)){       // Checks if X,Y,Z and Start or L, R and Start are all pressed
  SL = 1;                       // Sets Select as pressed
  ST = 0;                       // Sets Start as pressed
}
if (L == 1 && (R == 1 && (LP == 1 && (RP == 1)))){        // Checks if Start and 2 buttons are pressed. 
  SLcount = (SLcount + 1);
}else{ 
  SLcount = 0;
}

if (SLcount >= combodelay2){{
SLcount = 0;
SLST = (SLST + 1);                
 }
if (SLST > 2){
  SLST = 0;
}
EEPROM.write(6,SLST);
}

if (ST == 1 && (NB == 2 && (STP == 1))){        // Checks if Start and 2 buttons are pressed. 
  remapcount = (remapcount + 1);
}else{ 
  remapcount = 0;
}

if (remapcount >= combodelay){
remapcount = 0;
buttonmap = 1;                // Sets buttonmap mode to 1 
 }

if (ST == 1 && (NB == 1 && (STP == 1))){        // Checks if Start and 2 buttons are pressed. 
  autofirecount = (autofirecount + 1);
}else{ 
  autofirecount = 0;
}

if (autofirecount >= combodelay){
autofirecount = 0;
autofire = 1;                // Sets autofire mode to 1 
 }
}

void buttonmapping(){
if (ST == 1 && (NB == 2)){                        // Checks if the buttonmap combo is still held. 
 XO = 0;                                          // Resets all buttonmap values to 0
 YO = 0;
 ZO = 0;
 AO = 0;
 BO = 0;
 CO = 0;
}else{                                                       // If buttonmap combo is no longer pressed, continue to button mapping mode
if (XC == 1 && (XP == 0 && (NB == 1))){            // If X is currently pressed, if X was previously not pressed, if only one button (X) is pressed and if XO is less than 6
  XO = (XO + 1);                                             // If all of the above conditions are met, XO is iterated +1
}
if (XO > 6){                                       // If XO is greater than 6, XO is reset to 0
  XO = 0;
}
if (YC == 1 && (YP == 0 && (NB == 1))){
  YO = (YO + 1);
}
if (YO > 6){
  YO = 0;
}
if (ZC == 1 && (ZP == 0 && (NB == 1))){
  ZO = (ZO + 1);
}
if (ZO > 6){
  ZO = 0;
}
if (AC == 1 && (AP == 0 && (NB == 1))){
  AO = (AO + 1);
}
if (AO > 6){
  AO = 0;
}
if (BC == 1 && (BP == 0 && (NB == 1))){
  BO = (BO + 1);
}
if (BO > 6){
  BO = 0;
}
if (CC == 1 && (CP == 0 && (NB == 1))){
  CO = (CO + 1);
}
if (CO > 6){
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
void autofiremapping(){
if (ST == 1 && (NB == 1)){                        // Checks if the buttonmap combo is still held. 
 XA = 0;                                          // Resets all buttonmap values to 0
 YA = 0;
 ZA = 0;
 AA = 0;
 BA = 0;
 CA = 0;
}else{                                                       // If buttonmap combo is no longer pressed, continue to button mapping mode
if (XC == 1 && (XP == 0 && (NB == 1))){            // If X is currently pressed, if X was previously not pressed, if only one button (X) is pressed and if XO is less than 6
  XA = (XA + 1);                                             // If all of the above conditions are met, XO is iterated +1
}
if (XA > 6){                                       // If XO is greater than 6, XO is reset to 0
  XA = 0;
}
if (YC == 1 && (YP == 0 && (NB == 1))){
  YA = (YA + 1);
}
if (YA > 6){
  YA = 0;
}
if (ZC == 1 && (ZP == 0 && (NB == 1))){
  ZA = (ZA + 1);
}
if (ZA > 6){
  ZA = 0;
}
if (AC == 1 && (AP == 0 && (NB == 1))){
  AA = (AA + 1);
}
if (AA > 6){
  AA = 0;
}
if (BC == 1 && (BP == 0 && (NB == 1))){
  BA = (BA + 1);
}
if (BA > 6){
  BA = 0;
}
if (CC == 1 && (CP == 0 && (NB == 1))){
  CA = (CA + 1);
}
if (CA > 6){
  CA = 0;
  }
if (ST == 1 && (STP == 0)){
    autofire = 0;
    EEPROM.write(7,XA);
    EEPROM.write(8,YA);
    EEPROM.write(9,ZA);
    EEPROM.write(10,AA);
    EEPROM.write(11,BA);
    EEPROM.write(12,CA);
    
  } 
 }
}
