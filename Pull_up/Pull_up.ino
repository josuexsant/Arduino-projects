int digitalInput = 1;

void setup() {
  Serial.begin(9600);
  delay(200);
  pinMode(digitalInput, INPUT);
}

void loop() {
  Serial.println(digitalRead(digitalInput));
}
