#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 4
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

bool state = true;
int boton = 3;
int ventilador = 7;
long tiempo_anterior;
long diferencia;

void setup(void) {
  Serial.begin(9600);
  sensors.begin();
  pinMode(ventilador, OUTPUT);
  pinMode(boton, INPUT);
  attachInterrupt(digitalPinToInterrupt(boton), changeState, FALLING);
}

void changeState() {
  diferencia = millis() - tiempo_anterior;
  tiempo_anterior = millis();
  if (diferencia > 500)
    state = !state;
}

float getTenpeture() {
   sensors.requestTemperatures();
   return sensors.getTempCByIndex(0);
  //return 27.2;
}

void loop(void) {
  if (state) {
    if (getTenpeture() > 27) {
      digitalWrite(ventilador, HIGH);
    } else {
      digitalWrite(ventilador, LOW);
    }
    Serial.println(String(getTenpeture()));
  } else {
    digitalWrite(ventilador, LOW); 
  }
}
