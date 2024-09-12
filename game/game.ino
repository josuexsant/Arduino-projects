#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <OneWire.h>
#include <DallasTemperature.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1);


int potenciometro = A0;
int inicio = 3;
bool juegoIniciado = false;
int pelotaX = 50;
int pelotaY = 30;
int velocidadX = 2;
int velocidadY = 2;
int pelotaRadio = 2;
int puntos = 0;
int vidas = 5;
int nivel = 1;

void setup() {
  pinMode(inicio, INPUT);
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(2000);
  display.clearDisplay();
  gameStart();
  display.display();
  randomSeed(analogRead(0));
}

void setBarra(int position) {
  if (juegoIniciado == false) return;
  display.fillRect(position, 59, 20, 1, WHITE);
}

int getPositionPotenciometro() {
  if (juegoIniciado == false) return 0;
  int valor = analogRead(potenciometro);
  int position = map(valor, 0, 1023, 0, 108);
  return position;
}

void setPelota(int barraPosition) {
  display.clearDisplay();
  
  pelotaX += random(-2, 4) * velocidadX; 
  pelotaY += velocidadY;

  // cambio de posicion si sale de los bordes laterales
  if (pelotaX < 0 || pelotaX > 120 - pelotaRadio) {
    pelotaX = random(10, 110);
  }

  // comprobar si la pelota toca la barra o pasa el borde inferior
  if (pelotaY >= 57) {
    if (pelotaX >= barraPosition && pelotaX <= barraPosition + 20) {
      puntos++; // aumentar puntos
    } else {
      vidas--; // disminuir vidas
      if (vidas <= 0) {
        juegoIniciado = false; // termino del juego 
        gameOver();
      }
    }

    pelotaY = 0; // reinicio de posición en la parte superior
    pelotaX = random(10, 110); 
  }

  display.fillCircle(pelotaX, pelotaY, pelotaRadio, WHITE);
  setBarra(barraPosition);

  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("P: ");
  display.print(puntos);

  display.setCursor(40, 0);
  display.print("V: ");
  display.print(vidas);

  display.setCursor(80, 0);
  display.print("N: ");
  display.print(nivel);

  display.display();
  delay(30);

  //cambio de nivel 
  if (puntos == 10 && nivel == 1) {
    nivel = 2;
    velocidadY = 4; // aumenta la velocidad de la pelota
    displayNivel();
  } else if (puntos == 15 && nivel == 2) {
    juegoIniciado = false; // juego completado
    displayGanaste();
  }
}

void displayNivel() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 34);
  display.print("NIVEL 2");
  display.display();
  delay(2000);
}

void displayGanaste() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 34);
  display.print("GANASTE!");
  display.display();
  delay(3000);
}

void gameStart() {
  while (juegoIniciado == false) {
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, 34);
    display.print("GAME START");
    display.display();
    delay(500);

    display.clearDisplay();
    display.display();
    delay(500);

    // reiniciar juego 
    if (digitalRead(inicio) == LOW) {
      juegoIniciado = true;
      puntos = 0;  
      vidas = 5;
      nivel = 1;
      velocidadY = 2;
    }
  }
}

void gameOver() {
  while (juegoIniciado == false) {
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, 34);
    display.print("GAME OVER");
    display.display();
    delay(500);

    display.clearDisplay();
    display.display();
    delay(500);
  }
}

void loop() {
  if (!juegoIniciado) return;

  int barraPosition = getPositionPotenciometro(); 
  setPelota(barraPosition);
}