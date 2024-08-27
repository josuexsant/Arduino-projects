int digitalInput = 7;

void setup() {
  Serial.begin(9600);
  pinMode(digitalInput, INPUT);
  pinMode(2,OUTPUT);
}

void loop() {
  Serial.println(digitalRead(digitalInput));
  digitalRead(digitalInput);
  digitalWrite(2,HIGH);

}
