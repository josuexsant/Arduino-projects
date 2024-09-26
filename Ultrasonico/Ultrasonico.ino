#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(-1);
const byte trigg = 3;
const byte echo = 2;

//trigg entrada
//echo salida
void setup() {
  Serial.begin(9600);
  pinMode(trigg, OUTPUT);
  pinMode(echo, INPUT);
  digitalWrite(trigg, LOW);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(2000);
  display.clearDisplay();
}

void loop() {
  display.clearDisplay();
  int distancia = mide_distancia();

  display.setTextSize(1);
  display.setCursor(10, 10);
  display.setTextColor(WHITE);
  display.print("D: ");
  display.print(distancia);
  display.display();

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