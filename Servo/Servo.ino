#include <Servo.h>

Servo servo;
const byte ang_min = 0;
const byte ang_max = 160;
int potenciometro = A0;


void setup() {
  Serial.begin(9600);
  servo.attach(9);
}

void loop() {
  int angulo = map(analogRead(potenciometro), 0, 1023, ang_min, ang_max);
  servo.write(angulo);
  Serial.println(angulo);
  delay(20);
}