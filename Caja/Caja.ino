#include <Servo.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(-1); 

//Servo
Servo servo;
const byte ang_min = 90;
const byte ang_max = 0;

//Sensor proximidad
const byte trigg = 3;
const byte echo = 2;

//led
int led = 7;

void setup() {
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  //delay(2000);
  display.clearDisplay();

  pinMode(trigg, OUTPUT);
  pinMode(echo, INPUT);
  digitalWrite(trigg, LOW);

  servo.attach(9);

  pinMode(led,OUTPUT);
}

void loop() {
  int distancia = mide_distancia();

  abrirBote(distancia);
  cerrarBote(distancia);
}

void gatillo(){
  digitalWrite(trigg, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigg, LOW);
}

int mide_distancia(){
  gatillo();
  long tiempo = pulseIn(echo, HIGH);
  int distancia = tiempo/58;
  return distancia;
}

void abrirBote(int distancia){
    if(distancia < 20){
        servo.write(ang_max);
        digitalWrite(led,HIGH);
        mensajeB();
    }
}

void cerrarBote(int distancia){
    if(distancia > 20){
      servo.write(ang_min);
      digitalWrite(led,LOW);
      mensajeA();
    }
}


void animacion(bool ojos_cerrados) {
  int desplazamiento_y = -10;  // Desplazar la animación 10 píxeles hacia arriba

  // OJOS
  if (!ojos_cerrados) {
    display.drawCircle(48, 32 + desplazamiento_y, 10, WHITE);  // Ojo izquierdo
    display.fillCircle(48, 32 + desplazamiento_y, 5, WHITE);   // Pupila izquierda
    display.drawCircle(80, 32 + desplazamiento_y, 10, WHITE);  // Ojo derecho
    display.fillCircle(80, 32 + desplazamiento_y, 5, WHITE);   // Pupila derecha
  } else {
    // Ojos cerrados (líneas horizontales)
    display.drawLine(38, 32 + desplazamiento_y, 58, 32 + desplazamiento_y, WHITE);  // Ojo izquierdo cerrado
    display.drawLine(70, 32 + desplazamiento_y, 90, 32 + desplazamiento_y, WHITE); // Ojo derecho cerrado
  }
 

  // BOCA
  display.drawLine(54, 48 + desplazamiento_y, 74, 48 + desplazamiento_y, WHITE);  
  display.drawLine(54, 48 + desplazamiento_y, 50, 52 + desplazamiento_y, WHITE);  
  display.drawLine(74, 48 + desplazamiento_y, 78, 52 + desplazamiento_y, WHITE);  

  display.drawRoundRect(30, 20 + desplazamiento_y, 68, 48, 10, WHITE);  
}

void mensajeB(){
  display.clearDisplay();

  display.setTextSize(1);          
  display.setTextColor(WHITE);     
  display.setCursor(35, 0);        
  display.print("BIENVENIDO :)");          
  animacion(false);
  display.display();  
}

void mensajeA(){
  display.clearDisplay();         

  display.setTextSize(1);          
  display.setTextColor(WHITE);    
  display.setCursor(35, 0);        
  display.print("ADIOS :(");   
  animacion(true);
  display.display(); 
}
