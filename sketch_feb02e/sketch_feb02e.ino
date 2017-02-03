int DELAY_TIME = 50;
int analogPin = 0;
int val = 0;
int FADE_DELAY= 10;
int random_pin;
int pin_total=5;
int led_pwm_pins[] = {3,5,6,9,10};
void setup() {
  for (int e = 0; e < pin_total; e++){
    pinMode(led_pwm_pins[e], OUTPUT);
  }
  Serial.begin(9600);
  
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
  val = analogRead(analogPin);
  Serial.println(val);
  
        for (int e = 0; e < pin_total; e++){
          fade(led_pwm_pins[e],val/10);
        }
        delay(100);
       
}
