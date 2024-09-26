//Librerias
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(-1); 
// Definicion motor
const byte motorIzqA = 5;
//const byte motorIzqB = 4;
const byte enableIzq = 10;
// Definicion ultrasonico
const byte trigg = 3;
const byte echo = 2;
// Definicion de velocidad
const byte velMax = 254;
const byte velMin = 33; // Velocidad inicial
byte velocidad = 0;

void setup() {
  // Inicializacion de puerto serie
  Serial.begin(9600);
  
  // Inicializacion del ultrasonico
  pinMode(trigg, OUTPUT);
  pinMode(echo, INPUT);
  digitalWrite(trigg, LOW);

  //Inicialización de motor
  pinMode(motorIzqA, OUTPUT); 
  analogWrite(enableIzq, 0);

  // Inicializacion del display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  
  delay(2000);
  display.clearDisplay();
}

void loop() {
  display.clearDisplay();
  int distancia = mide_distancia();
  control_velocidad(distancia);

  mostrarDistancia(distancia);

  Serial.println(distancia);
}

int mide_distancia(){
  gatillo();
  long tiempo = pulseIn(echo, HIGH);
  int distancia = tiempo/58;
  return distancia;
}

//gatillo = disparo de la salida ultrasonica 
void gatillo(){
  digitalWrite(trigg, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigg, LOW);
}

void iniciar_motor(int vel){
  digitalWrite(motorIzqA, HIGH); // Activa el motor en sentido A
  analogWrite(enableIzq, vel); // Establece la velocidad
}

void control_velocidad(int distancia){
  if(distancia > 50){
    iniciar_motor(velMax);
    mostrarVelocidad(velMax);
  }else if(distancia <= 50){
    for (int i = velMax; i >= velMin; i -= 10) {
      iniciar_motor(i);
      mostrarVelocidad(i);
    }
  }

}

void mostrarVelocidad(int velocidad){
  display.clearDisplay();

  int porcentajeVelocidad = map(velocidad, velMin, velMax, 0, 100);
  display.setCursor(50, 0);  
  display.print("PV:");
  display.print(porcentajeVelocidad);

  display.display();

}

void mostrarDistancia(int distancia){
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(10, 10);
  display.setTextColor(WHITE);
  display.print("D: ");
  display.print(distancia);

  display.display();
}

