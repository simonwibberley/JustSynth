#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 8; //three columns
char keys[ROWS][COLS] = {
  {'a','b','c','d','e','f','g','h'},
  {'i','j','j','l','m','n','o','p'},
  {'q','r','s','t','u','v','w','x'},
  {'y','z','1','2','3','4','5','6'}
};
byte rowPins[ROWS] = {8, 9, 10, 11}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {7, 12, 6, 13, 5, A0, 4, A1}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


int D1 = 6;
int CP1 = 7;
//int MR = 8;
int D2 = 8;
int CP2 = 9;

int n = 0;
int d = 0;




void setup() {
  Serial.begin(9600);

  pinMode(D1, OUTPUT);
  pinMode(CP1, OUTPUT);
  
  pinMode(D2, OUTPUT);
  pinMode(CP2, OUTPUT);
  
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

void setCounter(int cpPin, int dPin, int n) {
  if(n < 8) {
    n = n | 0b10000000;
    shiftOut(dPin, cpPin, MSBFIRST, n);
  } else {
    n = n - 8;
    n = n << 4;
    n = n | 0b00001000;
    shiftOut(dPin, cpPin, MSBFIRST, n);
  }
}

void writeRatio(int ratio[]) {
  setCounter(CP1, D1, ratio[0]-1);
  setCounter(CP2, D2, ratio[1]-1);  
}

void writeRatio(int n, int d) {
  setCounter(CP1, D1, n-1);
  setCounter(CP2, D2, d-1);  
}

void loop() {
  char key = keypad.getKey();

  switch(key) {
    case 'a':
      writeRatio(1,1);
      break;
    case 'b':
      writeRatio(16,15);
      break;
    case 'c':
  writeRatio(9,8);
      break;

    case NO_KEY:
    default:
      break;
    
  }
  
  if (key != NO_KEY){
    Serial.println(key);
  }
  
//   delay(1);
   //playNotes();
}


void playNotes() {
  int wait = 2000;
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
