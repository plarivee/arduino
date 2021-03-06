/*
  Shift Register Example
  Turning on the outputs of a 74HC595 using an array

 Hardware:
 * 74HC595 shift register
 * LEDs attached to each of the outputs of the shift register

 */
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
  dataArray[0]  = 0b00000000;
  dataArray[1] = 0b00000001;
  dataArray[2] = 0b00000011;
  dataArray[3] = 0b00000111;
  dataArray[4] = 0b00001111;
  dataArray[5] = 0b00011111;
  dataArray[6] = 0b00111111;
  dataArray[7] = 0b01111111;
  dataArray[8] = 0b11111111;
  dataArray[9] = 0b11111111;
//  dataArray[0] = 0b00011000;
//  dataArray[1] = 0b00111100;
//  dataArray[2] = 0b01111110;
//  dataArray[3] = 0b11111111;
//  dataArray[4] = 0b11000000;
//  dataArray[5] = 0b00110000;
//  dataArray[6] = 0b00001100;
//  dataArray[7] = 0b00000011;
//  dataArray[8] = 0b11111111;

  //function that blinks all the LEDs
  //gets passed the number of blinks and the pause time
  //blinkAll_2Bytes(2,500);
}

void loop() {
  //blinkAll_2Bytes(2,50);
    //load the light sequence you want from array
    //data = dataArray[j];
    //data = random(9,18);
    data = analogRead(potPin)/100;
buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    buttonStatus ++;
  }
Serial.println(buttonStatus);
    int buttonMod = buttonStatus % 3;
    Serial.println(buttonMod);
   if (buttonMod == 0) {
     digitalWrite(latchPin, 0);
     shiftOut(dataPin, clockPin, dataArray[0]);
     digitalWrite(latchPin, 1);
     delay(100);
   } else if (buttonMod == 1) {
    blinkAll_2Bytes(2,50);
   }else if (buttonMod == 2 ) {
    if ( data >=9 ){
          digitalWrite(latchPin, 0);
          shiftOut(dataPin, clockPin, dataArray[9]);
          digitalWrite(latchPin, 1);
          delay(100);
          digitalWrite(latchPin, 0);
          shiftOut(dataPin, clockPin, dataArray[0]);
          digitalWrite(latchPin, 1);
          delay(100);
    }else {
    digitalWrite(latchPin, 0);
    shiftOut(dataPin, clockPin, dataArray[data]);
    digitalWrite(latchPin, 1);
    delay(50);
    previousData = data;
    }
   }
}



// the heart of the program
void shiftOut(int myDataPin, int myClockPin, byte myDataOut) {
  // This shifts 8 bits out MSB first,
  //on the rising edge of the clock,
  //clock idles low

  //internal function setup
  int i=0;
  int pinState;
  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin, OUTPUT);

  //clear everything out just in case to
  //prepare shift register for bit shifting
  digitalWrite(myDataPin, 0);
  digitalWrite(myClockPin, 0);

  //for each bit in the byte myDataOut�
  //NOTICE THAT WE ARE COUNTING DOWN in our for loop
  //This means that %00000001 or "1" will go through such
  //that it will be pin Q0 that lights.
  for (i=7; i>=0; i--)  {
    digitalWrite(myClockPin, 0);

    //if the value passed to myDataOut and a bitmask result
    // true then... so if we are at i=6 and our value is
    // %11010100 it would the code compares it to %01000000
    // and proceeds to set pinState to 1.
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


//blinks the whole register based on the number of times you want to
//blink "n" and the pause between them "d"
//starts with a moment of darkness to make sure the first blink
//has its full visual effect.
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

