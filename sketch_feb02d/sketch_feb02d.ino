
void setup() {
DDRB = B11111111;
}

void loop() {
  
    PORTB = random(0,32);
    delay(100);

}
