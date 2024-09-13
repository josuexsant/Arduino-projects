#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Servo.h>

Adafruit_SSD1306 display(128, 64, &Wire, -1);
Servo servo;
const byte ang_min = 0;
const byte ang_max = 160;
int potenciometro = A0;

int prev_x1 = 64;
int prev_y1 = 60;

void setup() {
  Serial.begin(9600);
  servo.attach(9);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(1000);
  display.clearDisplay();
  drawCircle();
  display.display();
}

void loop() {
  int angulo = map(analogRead(potenciometro), 0, 1023, ang_min, ang_max);
  servo.write(angulo);
  Serial.println(angulo);
  delay(20);
  drawAngle(angulo);
}

void drawCircle() {
  display.drawCircle(64, 60, 55, WHITE);
  display.drawCircle(64, 60, 57, WHITE);

  int x0 = 64;
  int y0 = 60;
  int radius = 50;
  for (int angle = 0; angle < 360; angle += 10) {
    int x = x0 + radius * cos(angle * DEG_TO_RAD);
    int y = y0 + radius * sin(angle * DEG_TO_RAD);
    display.drawPixel(x, y, SSD1306_WHITE);
  }

  radius = 49;
  for (int angle = 0; angle < 360; angle += 10) {
    int x = x0 + radius * cos(angle * DEG_TO_RAD);
    int y = y0 + radius * sin(angle * DEG_TO_RAD);
    display.drawPixel(x, y, SSD1306_WHITE);
  }
}

void drawAngle(int angle) {
  int x0 = 64;
  int y0 = 60;
  int radius = 45;
  float rad = radians(angle * 1.125);
  int x1 = x0 + radius * cos(rad) * -1;
  int y1 = y0 - radius * sin(rad);

  display.drawLine(x0, y0, prev_x1, prev_y1, SSD1306_BLACK);
  display.drawLine(x0, y0, x1, y1, SSD1306_WHITE);
  display.fillCircle(64, 60, 3, WHITE);

  // Clear the previous angle display
  display.fillRect(100, 0, 28, 10, SSD1306_BLACK);
  display.setCursor(100, 0);
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.print(angle);

  display.display();

  prev_x1 = x1;
  prev_y1 = y1;
}
