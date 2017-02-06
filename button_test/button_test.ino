//Pin connected to ST_CP of 74HC595
int latchPin = 8;
//Pin connected to SH_CP of 74HC595
int clockPin = 12;
////Pin connected to DS of 74HC595
int dataPin = 11;

//Analog in
int potPin = 0;

//Button pin
int buttonPin=4;
int buttonState=0;
int currentState=LOW;
int buttonStatus=0;

//holders for infromation you're going to pass to shifting function
byte previousData=0;
byte data=0;
byte dataArray[18];

void setup() {
  //set pins to output because they are addressed in the main loop
  pinMode(latchPin, OUTPUT);
  pinMode(buttonPin,INPUT);
  Serial.begin(9600);

  //Binary notation as comment
  dataArray[0] = 0b00000000;
  dataArray[1] = 0b00000001;
  dataArray[2] = 0b00000011;
  dataArray[3] = 0b00000111;
  dataArray[4] = 0b00001111;
  dataArray[5] = 0b00011111;
  dataArray[6] = 0b00111111;
  dataArray[7] = 0b01111111;
  dataArray[8] = 0b11111111;
  dataArray[9] = 0b11111111;
}

void loop() {
  data = analogRead(potPin)/100;
  currentState = digitalRead(buttonPin);
  Serial.println(currentState);

  if (currentState != buttonState && currentState == HIGH){
      buttonStatus ++;
      delay(10);
  }
  
  Serial.println(buttonStatus);
  int buttonMod = buttonStatus % 3;
  Serial.println(buttonMod);
  
  if (buttonMod == 0) {
     pushIt(latchPin, dataPin, clockPin, dataArray[0]);
     delay(100);
  } else if (buttonMod == 1) {
    blinkAll_2Bytes(2,50);
  }else if (buttonMod == 2 ) {
    if ( data >=9 ){
      pushIt(latchPin, dataPin, clockPin, dataArray[9]);
      delay(100);
      pushIt(latchPin, dataPin, clockPin, dataArray[0]);
      delay(100);
    }else {
      pushIt(latchPin, dataPin, clockPin, dataArray[data]);
      delay(50);
      previousData = data;
    }
  }
}

void pushIt(int thatLatchPin, int thatDataPin, int thatClockPin, byte thatDataOut){
  digitalWrite(thatLatchPin, 0);
  shiftOut(thatDataPin, thatClockPin, thatDataOut);
  digitalWrite(thatLatchPin, 1);
}


// the heart of the program
void shiftOut(int myDataPin, int myClockPin, byte myDataOut) {
  int i=0;
  int pinState;
  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin, OUTPUT);

  digitalWrite(myDataPin, 0);
  digitalWrite(myClockPin, 0);

  for (i=7; i>=0; i--)  {
    digitalWrite(myClockPin, 0);

    if ( myDataOut & (1<<i) ) {
      pinState= 1;
    }
    else { 
      pinState= 0;
    }

    //Sets the pin to HIGH or LOW depending on pinState
    digitalWrite(myDataPin, pinState);
    //register shifts bits on upstroke of clock pin  
    digitalWrite(myClockPin, 1);
    //zero the data pin after shift to prevent bleed through
    digitalWrite(myDataPin, 0);
  }

  //stop shifting
  digitalWrite(myClockPin, 0);
}

void blinkAll_2Bytes(int n, int d) {
  digitalWrite(latchPin, 0);
  shiftOut(dataPin, clockPin, 0);
  shiftOut(dataPin, clockPin, 0);
  digitalWrite(latchPin, 1);
  delay(500);
  for (int x = 0; x < n; x++) {
    digitalWrite(latchPin, 0);
    shiftOut(dataPin, clockPin, 255);
    shiftOut(dataPin, clockPin, 255);
    digitalWrite(latchPin, 1);
    delay(d);
    digitalWrite(latchPin, 0);
    shiftOut(dataPin, clockPin, 0);
    shiftOut(dataPin, clockPin, 0);
    digitalWrite(latchPin, 1);
    delay(d);
  }
}

