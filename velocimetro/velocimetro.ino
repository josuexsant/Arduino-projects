#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <OneWire.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1);

const byte motorIzqA = 5;
const byte motorIzqB = 4;
const byte enableIzq = 10;
int boton = 3; 
int potenciometro = A0; 
bool direccion = true; 
byte velocidad = 0;
const byte velMax = 255;
const byte velMin = 0;
int angRueda = 0;  
int velAnt = 0;  
unsigned long ruedaMillis = 0; 
const int ruedaInter = 100; 
unsigned long flechaMillis = 0;
const int flechaInter = 500; 
bool mostrarFlecha = true; 

void setup() {
  Serial.begin(9600);
  
  pinMode(boton, INPUT);
  attachInterrupt(digitalPinToInterrupt(boton), cambiarDireccion, RISING);

  pinMode(motorIzqA, OUTPUT);
  pinMode(motorIzqB, OUTPUT);
  analogWrite(enableIzq, velocidad);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(1000);
  display.clearDisplay();
  display.display();
}

void loop() {
  // velocidad del potenciometro y motor
  velocidad = map(analogRead(potenciometro), 0, 1023, velMin, velMax);
  control_izq(direccion, velocidad);

  // tiempos de los giros
  unsigned long Millis = millis();
  if (Millis - ruedaMillis >= ruedaInter) {
    ruedaMillis = Millis;

    // cambios de velocidad
    if (velocidad > 0) {
      angRueda += map(velocidad, velMin, velMax, 1, 10);  
      if (angRueda >= 360) {
        angRueda = 0;
      }
    }

    rueda(velocidad);
  }

  // parpadeo de las flechas
  if (Millis - flechaMillis >= flechaInter) {
    flechaMillis = Millis; 
    mostrarFlecha = !mostrarFlecha; 
  }
}

// motor 
void control_izq(bool sentido, byte vel) {
  if (sentido) {
    digitalWrite(motorIzqA, HIGH);
    digitalWrite(motorIzqB, LOW);
  } else {
    digitalWrite(motorIzqA, LOW);
    digitalWrite(motorIzqB, HIGH);
  }
  analogWrite(enableIzq, vel);
}

void cambiarDireccion() {
  direccion = !direccion;
}

void rueda(int velocidad) {
  display.clearDisplay();

  // dibujo rueda
  display.drawCircle(64, 32, 31, WHITE);
  display.drawCircle(64, 32, 29, WHITE); 
  display.fillCircle(64, 32, 5, WHITE);

  // dibujo de los angulos de la rueda
  for (int angulo = 0; angulo < 360; angulo += 30) {
    float radian = (angulo + angRueda) * (PI / 180); 
    int x1 = 64 + 5 * cos(radian); 
    int y1 = 32 + 5 * sin(radian); 
    int x2 = 64 + 25 * cos(radian); 
    int y2 = 32 + 25 * sin(radian); 
    display.drawLine(x1, y1, x2, y2, WHITE);
  }

 
  if (mostrarFlecha) {
    if (direccion) {
      // flecha izquierda
      display.drawLine(15, 20, 25, 30, WHITE);
      display.drawLine(15, 20, 15, 50, WHITE);
      display.drawLine(15, 20, 5, 30, WHITE);
    } else {
      // flecha derecha
      display.drawLine(113, 50, 123, 40, WHITE);
      display.drawLine(113, 20, 113, 50, WHITE);
      display.drawLine(113, 50, 103, 40, WHITE);
    }
  }

  // mostrar la velocidad 
  display.setTextSize(1);     
  display.setTextColor(WHITE); 
  display.setCursor(0, 0);     
  display.print("V: ");
  display.print(velocidad);
  display.display();
}