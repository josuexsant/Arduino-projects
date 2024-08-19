int outputDigital = 3;
int inputAnalog = 0;

void setup() {
  pinMode(outputDigital, OUTPUT);
}

void loop() {
  int analogValue = analogRead(inputAnalog);
  int pwmValue = analogValue / 4;
  analogWrite(outputDigital, pwmValue); 
}
