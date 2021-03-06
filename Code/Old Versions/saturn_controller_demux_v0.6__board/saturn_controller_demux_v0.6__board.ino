 /* Saturn Controller Demux
 * ------------------ 
 * This sketch is designed to demux Sega Saturn gamepad
 * signals into descrete outputs for use with arcade 
 * PCBs. 
 * 
 * There are two select lines, four data input lines, and
 * 13 discrete outputs. The controlls can be remapped by 
 * changing the pin assignments below.
 * 
 * Appollogies for the sloppy code. It took a lot of trial and error
 * to get all the timings right for MC Cthulu boards to work properly
 * I tried to clean it up as much as I could.
 * 
 * Arthrimus December 24 2018
 *
 */

int UP = 1; // These choose the pins for the button outputs. (Change these-
int DN = 4; // if you wish to remap the buttons.)
int LT = 5;
int RT = 6;
int A = 10;
int B = 13;
int C = 12;
int X = 7;
int Y = 8;
int Z = 9;
int L = 2;
int R = 3;
int ST = 11;   
int D0 = 15;  // choose the input pins for the digital lines (Probably don't change these)
int D1 = 14;
int D2 = 19;
int D3 = 18;
int S0 = 16; // Chooses the output pins for the select lines (Probably don't change these either)
int S1 = 17;

int val = 0;     // variable for reading the pin status (should be zero)
int outputb = 0;
int outputd = 0;

void setup() {
  pinMode(UP, OUTPUT);  // declares buttons as outputs (don't change these)
  pinMode(DN, OUTPUT); 
  pinMode(LT, OUTPUT);
  pinMode(RT, OUTPUT);
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(X, OUTPUT);
  pinMode(Y, OUTPUT);
  pinMode(Z, OUTPUT);
  pinMode(L, OUTPUT);
  pinMode(R, OUTPUT);
  pinMode(ST,OUTPUT);
  pinMode(D0, INPUT_PULLUP);    // declare pushbutton as input (or these)
  pinMode(D1, INPUT_PULLUP);
  pinMode(D2, INPUT_PULLUP);
  pinMode(D3, INPUT_PULLUP);
  pinMode(S0, OUTPUT); // Declare Select Pins as outputs (these either)
  pinMode(S1, OUTPUT);
}

void loop(){

outputb = 0;
outputd = 0;
  
  {                             // This is the start of the first bit of the demuxer, there are four of these
  delay(5);
  digitalWrite(S1, LOW);
  digitalWrite(S0, HIGH); // Sets the select lines S0 HIGH, S1 LOW
 
  }
  val = digitalRead(D0);  // read input value from data line
  if (val == LOW) {         // check if the data input is HIGH (button released)
  outputb |= 32;          // B
  }
  val = digitalRead(D1); 
  if (val == LOW) {       
  outputb |= 2;           // C
  }
  val = digitalRead(D2);
  if (val == LOW) {       
  outputb |= 4;           // A
  }
  val = digitalRead(D3); 
  if (val == LOW) {      
  outputb |= 8;           // Start
  }                                // This is the end of the first bit of the demuxer.

{                               // This is the start of the second bit of the demuxer.
  delay(5);
  digitalWrite(S1, LOW);           // Sets the select lines S0 LOW, S1 LOW
  digitalWrite(S0, LOW);         
  }
    val = digitalRead(D0);
  if (val == LOW) {       
  outputb |= 16;              // Z
  }
  val = digitalRead(D1); 
  if (val == LOW) {      
  outputb |= 1;               // Y
  }
  val = digitalRead(D2);
  if (val == LOW) {       
  outputd |= 128;             // X
  }
  val = digitalRead(D3); 
  if (val == LOW) {           // R
    
  }                             // This is the end of the second bit of the demuxer.       
          { 
  delay(5);                    // This is the start of the third bit of the demuxer.
  digitalWrite(S1, HIGH);       // Sets the select lines S0 HIGH, S1 HIGH
  digitalWrite(S0, HIGH);  

  }
  val = digitalRead(D3); 
  if (val == LOW) {      
                              // L 
  }                            // This is the end of the third bit of the demuxer. 
   {                       // This is the start of the fourth bit of the demuxer.
  delay(5);
  digitalWrite(S1, HIGH);// Sets the select lines S0 LOW, S1 HIGH
  digitalWrite(S0, LOW);   

  }
    val = digitalRead(D0); 
  if (val == LOW) {       
  outputd |= 2;               // UP
  }
  val = digitalRead(D1); 
  if (val == LOW) {      
  outputd |= 16;              // DOWN
  }
  val = digitalRead(D2);
  if (val == LOW) {       
  outputd |= 32;              // LEFT
  }
  val = digitalRead(D3); 
  if (val == LOW) {      
  outputd |= 64;              // RIGHT
  }                         // This is the end of the fourth bit of the demuxer. 

  DDRB = outputb;
  DDRD = outputd;
  
  }        // End of the program.
