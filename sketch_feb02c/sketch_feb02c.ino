int pinArray[] = {3,5,6,9,10};
int count = 0;
int timer = 100;
int pinCount = 5;

void setup(){
  for (count=0;count<pinCount;count++) {
    pinMode(pinArray[count], OUTPUT);
  }
}

void loop() {
  for (count=0;count<pinCount;count++) {
   analogWrite(pinArray[count], 200);
   delay(timer);
   analogWrite(pinArray[count + 1], 125);
   delay(timer);
   analogWrite(pinArray[count], 0);
   delay(timer*2);
  }
  for (count=pinCount-1;count>0;count--) {
   digitalWrite(pinArray[count], HIGH);
   delay(timer);
   digitalWrite(pinArray[count - 1], HIGH);
   delay(timer);
   digitalWrite(pinArray[count], LOW);
   //delay(timer*2);
  }
}

