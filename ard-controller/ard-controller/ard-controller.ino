int D1 = 6;
int CP = 7;
int MR = 8;
int ITR = 2;

int n = 0;


void setup() {
  pinMode(D1, OUTPUT);
  pinMode(CP, OUTPUT);
  pinMode(MR, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(2), increment, RISING);
}


void increment() {
  ++n;
  n = n % 16;
  setCounter(D1, n);
}

void setCounter(int pin, int n) {
  if(n < 8) {
    n = n | 0b10000000;
    shiftOut(D1, CP, MSBFIRST, n);
  } else {
    n = n - 8;
    n = n << 4;
    n = n | 0b00001000;
    shiftOut(D1, CP, MSBFIRST, n);
  }
}

void loop() {
  
  //for(int i = 0; i < 16; ++i) {
  //  setCounter(D1, i);
  //  delay(1000);
  //}
}
