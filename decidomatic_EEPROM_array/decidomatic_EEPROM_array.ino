#include <EEPROM.h>
#include <avr/pgmspace.h>

//                        attiny45
//                   reset -+---+- power
//                     pb3 -+*  +- pb2 (no)
//            (button) pb4 -+   +- pb1 (maybe)
//                  ground -+---+- pb0 (yes)

// this solution is inelegant as FUCK (pre-rolled sequence of 200...)
// but makes it "feel" random

const int yes = 0;
const int maybe = 1;
const int no = 2;
int counter = 0;
int result;
byte rolls[] = {
0, 2, 2, 1, 0, 2, 1, 2, 0, 1,
2, 0, 3, 2, 1, 0, 1, 0, 2, 1,
1, 2, 0, 2, 0, 0, 2, 0, 2, 1,
0, 0, 2, 0, 1, 2, 0, 1, 2, 1,
0, 1, 2, 1, 0, 0, 1, 1, 2, 0,
2, 0, 1, 0, 0, 1, 1, 0, 1, 0,
1, 2, 1, 0, 2, 1, 1, 2, 2, 0,
2, 1, 2, 1, 1, 0, 2, 1, 0, 1,
0, 1, 2, 1, 2, 1, 1, 0, 2, 2,
1, 0, 1, 0, 0, 2, 0, 2, 1, 0,
2, 1, 2, 2, 1, 0, 1, 2, 0, 2,
0, 0, 2, 0, 2, 1, 0, 1, 1, 0,
1, 2, 2, 0, 1, 2, 0, 2, 0, 0,
1, 2, 0, 1, 2, 1, 2, 1, 1, 0,
0, 1, 2, 0, 2, 1, 2, 0, 2, 0,
0, 1, 2, 1, 0, 0, 1, 2, 1, 2,
0, 2, 1, 0, 1, 0, 2, 0, 2, 2,
1, 2, 1, 0, 1, 0, 0, 1, 2, 1,
0, 1, 2, 1, 0, 0, 1, 0, 2, 2,
0, 2, 0, 2, 1, 2, 0, 1, 0, 1
};

boolean analyze = true;

void setup() {
  pinMode(yes, OUTPUT);
  pinMode(maybe, OUTPUT);
  pinMode(no, OUTPUT);
  
  int randumb = EEPROM.read(1) % 200;
  result = rolls[randumb];
  EEPROM.write(1, (randumb+1) % 200);
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



