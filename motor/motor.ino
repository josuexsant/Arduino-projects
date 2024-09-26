const byte motorIzquierdoA = 3;
const byte motorIzquierdoB = 4;
const byte enableIzquierdo = 10;
const byte velocidad_inicial = 0;

void setup() {
  Serial.begin(9600);
  pinMode(motorIzquierdoA,OUTPUT);
  pinMode(motorIzquierdoB,OUTPUT);
  analogWrite(enableIzquierdo,velocidad_inicial);
}

void control_izq(bool sentido, byte vel){
  if(sentido){
    digitalWrite(motorIzquierdoA, HIGH);
    digitalWrite(motorIzquierdoB, LOW);
  }else{
    digitalWrite(motorIzquierdoA, LOW);
    digitalWrite(motorIzquierdoB, HIGH);
  }
  analogWrite(enableIzquierdo,vel);
}

void loop() {
  control_izq(true,64);
  delay(2000);
  control_izq(true,0);
  delay(1000);
  control_izq(false,254);
  delay(2000);
  control_izq(true,0);
  delay(1000);
}