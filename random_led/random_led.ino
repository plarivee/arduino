int DELAY_TIME = 200;
int FADE_DELAY= 10;
int random_pin;
int pin_total=5;
int led_pwm_pins[] = {3,5,6,9,10};
void setup() {
  for (int e = 0; e < pin_total; e++){
    pinMode(led_pwm_pins[e], OUTPUT);
  }
}

void on(int pin){
  digitalWrite(pin,HIGH);
}
void off(int pin){
  digitalWrite(pin, LOW);
}

void fade(int pin, int br){
  analogWrite(pin,br);
}

void loop() {
  random_pin = random(0,1000);
  //random_pin = 14;

  if (random_pin == 14){
    for (int r =0; r < 10; r++){
      for (int i = 0; i< 125; i++){
        for (int e = 0; e < pin_total; e++){
          fade(led_pwm_pins[e],i);
        }
        delay(FADE_DELAY);
      }
      for (int i = 125; i>= 0; i--){
        for (int e = 0; e < pin_total; e++){
          fade(led_pwm_pins[e],i);
        }
        delay(FADE_DELAY);
      }
      delay(DELAY_TIME*10);
      }
  }else {
    random_pin = random(0,pin_total);
    on(led_pwm_pins[random_pin]);
    delay(DELAY_TIME);
    off(led_pwm_pins[random_pin]);
  }
}
