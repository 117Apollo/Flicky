//117_Apollo's code for flight sim switch box
//Seems to work well, but I'm not a software engineer so might not be 100% efficient
#include <Joystick.h>
Joystick_ Joystick;

#define inputSW0 0
#define inputSW1 1
#define inputSW2 2
#define inputSW3 3
#define inputSW4 4
#define inputSW5 5
#define inputSW6 6
#define inputSW7 7
#define inputSW8 8
#define inputRC0 9
#define inputRD0 10
#define inputRC1 11
#define inputRD1 12
#define inputRB0 13
#define inputRC2 A0
#define inputRD2 A1
#define inputRC3 A2
#define inputRD3 A3
#define inputRC4 A4
#define inputRD4 A5

int currentStateRC0;
int previousStateRC0;
int cwblock0;
int ccwblock0;
String encdir0 = "";

int currentStateRC1;
int previousStateRC1;
int cwblock1;
int ccwblock1;
String encdir1 = "";

int currentStateRC2;
int previousStateRC2;
int cwblock2;
int ccwblock2;
String encdir2 = "";

int currentStateRC3;
int previousStateRC3;
int cwblock3;
int ccwblock3;
String encdir3 = "";

int currentStateRC4;
int previousStateRC4;
int cwblock4;
int ccwblock4;
String encdir4 = "";

int currentStateSW0;
int currentStateSW1;
int currentStateSW2;
int currentStateSW3;
int currentStateSW4;
int currentStateSW5;
int currentStateSW6;
int currentStateSW7;
int currentStateSW8;

int previousStateSW0;
int previousStateSW1;
int previousStateSW2;
int previousStateSW3;
int previousStateSW4;
int previousStateSW5;
int previousStateSW6;
int previousStateSW7;
int previousStateSW8;

void setup() {
  pinMode(inputSW0, INPUT);
  pinMode(inputSW1, INPUT);
  pinMode(inputSW2, INPUT);
  pinMode(inputSW3, INPUT);
  pinMode(inputSW4, INPUT);
  pinMode(inputSW5, INPUT);
  pinMode(inputSW6, INPUT);
  pinMode(inputSW7, INPUT);
  pinMode(inputSW8, INPUT);
  pinMode(inputRC0, INPUT);
  pinMode(inputRD0, INPUT);
  pinMode(inputRC1, INPUT);
  pinMode(inputRD1, INPUT);
  pinMode(inputRC2, INPUT);
  pinMode(inputRD2, INPUT);
  pinMode(inputRC3, INPUT);
  pinMode(inputRD3, INPUT);
  pinMode(inputRC4, INPUT);
  pinMode(inputRD4, INPUT);
  pinMode(inputRB0, INPUT);

  Serial.begin (9600);

  Joystick.begin();

  previousStateRC0 = digitalRead(inputRC0);
  previousStateRC1 = digitalRead(inputRC1);
  previousStateRC2 = digitalRead(inputRC2);
  previousStateRC3 = digitalRead(inputRC3);
  previousStateRC4 = digitalRead(inputRC4);
}

int check_switch(int currentState, int *previousState, int id){
  if (currentState != *previousState) {
    Serial.print(currentState);
    Serial.println(id);
    //The below doesn't really work very well
    //Joystick.setButton(id, currentState);
     Joystick.setButton(id, 1);
     delay(100);
     Joystick.setButton(id, 0);  
    *previousState = currentState;
    //The reading flutters when switched to HIGH so this prevents a short on/off loop
    delay(500);
    return 0;
  }
}

int check_rotor(int cwid, int ccwid, int currentStateRC, int currentStateRD, int *previousStateRC, String *encdir, int *ccwblock, int *cwblock){
  if (currentStateRC != *previousStateRC) {
    if (currentStateRD != currentStateRC) {
      *encdir = "CCW";
      if ((*ccwblock) == 0){
        Joystick.setButton(ccwid, 1);
        delay(100);
        Joystick.setButton(ccwid, 0);
        *cwblock = 1;
        Serial.print(cwid);
        Serial.println(*encdir);
      } else {
        *ccwblock = 0;
      }
    } else {
      *encdir = "CW";
      if ((*cwblock) == 0) {
        Joystick.setButton(cwid, 1);
        delay(100);
        Joystick.setButton(cwid, 0);
        *ccwblock = 1;
        Serial.print(cwid);
        Serial.println(*encdir);
      } else {
        *cwblock = 0;
      }
    }
  }
  *previousStateRC = currentStateRC;
  return 0;
}

int check_btn(int id, int currentStateBTN){
  if (currentStateBTN == 0){
     Joystick.setButton(id, 1);
     delay(100);
     Joystick.setButton(id, 0);  
     delay(500);      
     Serial.println(id);
  }
  return 0;
}

void loop() {
  check_switch(digitalRead(inputSW0), &previousStateSW0, 0);
  check_switch(digitalRead(inputSW1), &previousStateSW1, 1);
  check_switch(digitalRead(inputSW2), &previousStateSW2, 2);
  check_switch(digitalRead(inputSW3), &previousStateSW3, 3);
  check_switch(digitalRead(inputSW4), &previousStateSW4, 4);
  check_switch(digitalRead(inputSW5), &previousStateSW5, 5);
  check_switch(digitalRead(inputSW6), &previousStateSW6, 6);
  check_switch(digitalRead(inputSW7), &previousStateSW7, 7);
  check_switch(digitalRead(inputSW8), &previousStateSW8, 8);

  check_rotor(9, 10, digitalRead(inputRC0), digitalRead(inputRD0), &previousStateRC0, &encdir0, &ccwblock0, &cwblock0);
  check_rotor(11, 12, digitalRead(inputRC1), digitalRead(inputRD1), &previousStateRC1, &encdir1, &ccwblock1, &cwblock1);
  check_rotor(13, 14, digitalRead(inputRC2), digitalRead(inputRD2), &previousStateRC2, &encdir2, &ccwblock2, &cwblock2);
  check_rotor(15, 16, digitalRead(inputRC3), digitalRead(inputRD3), &previousStateRC3, &encdir3, &ccwblock3, &cwblock3);
  check_rotor(17, 18, digitalRead(inputRC4), digitalRead(inputRD4), &previousStateRC4, &encdir4, &ccwblock4, &cwblock4);
  
  check_btn(19, digitalRead(inputRB0));  
  //Most rotary click buttons not implement yet as ran out of inputs, need shift register
  //check_btn(20, digitalRead(inputRB1));  
  //check_btn(21, digitalRead(inputRB2));  
  //check_btn(22, digitalRead(inputRB3));  
  //check_btn(23, digitalRead(inputRB4));
}
