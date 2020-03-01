#include <Keypad_MC17.h>
#include <Keypad.h>
#include <Wire.h>

#define I2CADDR 0x20

const byte ROWS = 4; //four rows
const byte COLS = 8; //eight columns
char keys[ROWS][COLS] = {
  {'a','b','c','d','e','f','g','h'},
  {'i','j','j','l','m','n','o','p'},
  {'q','r','s','t','u','v','w','x'},
  {'y','z','1','2','3','4','5','6'}
};
byte rowPins[ROWS] = {8, 9, 10, 11}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {12, 13, 14, 15, 0, 1, 2, 3}; //connect to the column pinouts of the keypad

Keypad_MC17 keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS, I2CADDR);


int MR = 5;
int D1 = 6;
int CP1 = 7;
int D2 = 8;
int CP2 = 9;

int n = 0;
int d = 0;




void setup() {
  Serial.begin(9600);
    
  Serial.println("blah");
  keypad.begin( );


  pinMode(MR, OUTPUT);

  pinMode(D1, OUTPUT);
  pinMode(CP1, OUTPUT);
  
  pinMode(D2, OUTPUT);
  pinMode(CP2, OUTPUT);

  digitalWrite(MR, HIGH);

  //pinMode(MR, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(2), incrementNumerator, RISING);
  attachInterrupt(digitalPinToInterrupt(3), incrementDenominator, RISING);
}


void incrementNumerator() {
  ++n;
  n = n % 16;
  setCounter(CP1, D1, n);
}


void incrementDenominator() {
  ++d;
  d = d % 16;
  setCounter(CP2, D2, d);
}

void reset() {
  digitalWrite(MR, LOW);
  delay(1);
  digitalWrite(MR, HIGH);  
}

void setCounter(int dPin, int cpPin, int n) {
  if(n < 8) {
    n = n | 0b10000000;
  } else {
    n = n - 8;
    n = n << 4;
    n = n | 0b00001000;
  }
  shiftOut(dPin, cpPin, MSBFIRST, n);
}

void writeRatio(int ratio[]) {
  writeRatio(ratio[0], ratio[1]);
}

void writeRatio(int n, int d) {
  Serial.print(n);
  Serial.print("/");
  Serial.println(d);
  reset();
  setCounter(D1, CP1, n-1);
  setCounter(D2, CP2, d-1);  
}

void loop() {

  
  //Serial.println("blah1");
  char key = keypad.getKey();

  switch(key) {
    case 'a':
      writeRatio(1,1);
      break;
    case 'd':
      writeRatio(16,15);
      break;
    case 'c':
      writeRatio(9,8);
      break;
    case 'f':
      writeRatio(6,5);
      break;
    case 'e':
      writeRatio(5,4);
      break;
    case 'h':
      writeRatio(4,3);
      break;
    case 'g':
      writeRatio(7,5);
      break;
    case 'z':
      writeRatio(3,2);
      break;
    case 'y':
      writeRatio(8,5);
      break;
    case '2':
      writeRatio(5,3);
      break;
    case '1':
      writeRatio(16,9);
      break;
    case '4':
      writeRatio(15,8);
      break;
    case '3':
      writeRatio(2,1);
      break;
    case NO_KEY:
    default:
      break;
    
  }
  
  if (key != NO_KEY){
    Serial.println(key);
  }
  
  //Serial.println("blah");
  
  //delay(1);
  //playNotes();
  playSeq();
//  writeRatio(7,7);
//  delay(9000);
}

void playSeq() {
  int wait = 500;
//  for(int j = 1; j <= 16; ++j) {
//    writeRatio(1,j);
//    delay(wait);
//  }
  for(int j = 1; j <= 16; ++j) {
    writeRatio(j,j);
    delay(wait);
  }

}

void playNotes() {
  int wait = 4000;
  writeRatio(1,1);
  delay(wait );
  writeRatio(16,15);
  delay(wait );
  writeRatio(9,8);
  delay(wait );
  writeRatio(6,5);
  delay(wait );  
  writeRatio(5,4);
  delay(wait );  
  writeRatio(4,3);
  delay(wait );  
  writeRatio(7,5);
  delay(wait );  
  writeRatio(3,2);
  delay(wait );  
  writeRatio(8,5);
  delay(wait );  
  writeRatio(5,3);
  delay(wait );  
  writeRatio(16,9);
  delay(wait );  
  writeRatio(15,8);
  delay(wait );  
  writeRatio(2,1);
  delay(wait );  
}
