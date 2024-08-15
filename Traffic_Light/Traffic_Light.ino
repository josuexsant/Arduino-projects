int green = 1;
int yellow = 2;
int red = 3;

void setup() {
  pinMode(green, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(red, OUTPUT);
}

void blinking(int led) {
  for (int i = 0; i < 4; i++) {
    digitalWrite(led, LOW);
    delay(250);         
    digitalWrite(led, HIGH);
    delay(250);          
  }
}

void turnOn(int led, bool blink){
  digitalWrite(led, HIGH);
  delay(2000);
  if (blink) {
    blinking(led);
  }
  digitalWrite(led, LOW);
}

void loop() {
  turnOn(green, true);
  turnOn(yellow, false);
  turnOn(red, false);
}
