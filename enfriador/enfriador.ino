#include <OneWire.h>
#include <DallasTemperature.h>
// TODO: Agregar librerias del display

#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// TODO: Asignar pines al display
bool state = true; //ESTADO DEL SISTEMA
int stopping_botton = 3; //BOTON DE EMERGENCIA
int up_button = 4; //BOTON PARA SUBIR EL UMBRAL
int down_botton = 5; //BOTON PARA BAJAR EL UMBRAL
int ventilador = 7;
long tiempo_anterior;
long diferencia;
int umbral = 27;

void setup(void) {
  Serial.begin(9600);
  sensors.begin();
  pinMode(ventilador, OUTPUT);
  pinMode(stopping_botton, INPUT);
  attachInterrupt(digitalPinToInterrupt(stopping_botton), changeState, FALLING);
  attachInterrupt(digitalPinToInterrupt(up_botton), changeState, FALLING);
  attachInterrupt(digitalPinToInterrupt(down_botton), changeState, FALLING);
}

void changeState() {
  diferencia = millis() - tiempo_anterior;
  tiempo_anterior = millis();
  if (diferencia > 500)
    state = !state;
}

float getTenpeture() {
   //sensors.requestTemperatures();
   //return sensors.getTempCByIndex(0);
  return 27.2; // TEMPERATURA SIMULADA
}

void loop(void) {
  if (state) {
    if (getTenpeture() > umbral) {
      digitalWrite(ventilador, HIGH);
    } else {
      digitalWrite(ventilador, LOW);
    }
    Serial.println(String(getTenpeture()));
  } else {
    digitalWrite(ventilador, LOW);
    // TODO: Hacer el mensaje de que el sistema esta en stop en el display
  }
}
