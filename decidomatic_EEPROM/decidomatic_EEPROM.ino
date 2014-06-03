#include <EEPROM.h>

//                        attiny45
//                   reset -+---+- power
//                     pb3 -+*  +- pb2 (no)
//            (button) pb4 -+   +- pb1 (maybe)
//                  ground -+---+- pb0 (yes)

const int yes = 0;
const int maybe = 1;
const int no = 2;
int counter = 0;
int result;

boolean analyze = true;

void setup() {
  randomSeed(321);
  pinMode(yes, OUTPUT);
  pinMode(maybe, OUTPUT);
  pinMode(no, OUTPUT);
  
  int randumb = EEPROM.read(0);
  for (int r=0; r<randumb; r++) {
    result = random(0,3);
  }
  EEPROM.write(0, (randumb+1) % 100);
}

void loop() {

  if (analyze == true) {
    for (int i=0; i<3; i++) { //blink the LEDs on & off
      cycle(3,HIGH);
      delay(300);
      cycle(3, LOW);
      delay(300);
    }
    digitalWrite(result, HIGH);
    delay(3000);
    cycle(3,LOW);
    analyze = false;
  }
}

void cycle(int maxPin, int state) {
  for (int i=0; i <= maxPin; i++){
    digitalWrite(i, state);
    delayMicroseconds(10);
  }
}



