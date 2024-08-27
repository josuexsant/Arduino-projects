int boton = 3;
int led = 5;
bool estado_pulsador;
long tiempo_anterior;
long diferencia;
void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(boton, INPUT);
  attachInterrupt(digitalPinToInterrupt(boton),consulta_estado,CHANGE);
}

void consulta_estado(){
  diferencia = millis() - tiempo_anterior;
  tiempo_anterior = millis();
  Serial.println(diferencia);
  if(diferencia > 500){
    if(digitalRead(led) == true){
    digitalWrite(led,LOW);
    Serial.println("-- APAGADO --");
    delay(500);
  }else{
    digitalWrite(led,HIGH);
    Serial.println("-- ENCENDIDO --");
    delay(500);
  }
  }
}

void loop(){
  delay(5000);
}