#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET     4
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES     10

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
static const unsigned char PROGMEM logo_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

void setup() {
  Serial.begin(9600);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3D)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  display.display();
  delay(2000);
  display.clearDisplay();
  drawCircle();
  display.display();
}

void loop() {
  drawAngle(150);
  delay(2000);
}

void drawCircle() {
  int16_t x0 = 64;
  int16_t y0 = 60;
  int16_t radius = 50;
  for (int16_t angle = 0; angle < 360; angle += 10) {
    int16_t x = x0 + radius * cos(angle * DEG_TO_RAD);
    int16_t y = y0 + radius * sin(angle * DEG_TO_RAD);
    display.drawPixel(x, y, SSD1306_WHITE);
  }
}

void drawAngle(int angle) {
  int16_t x0 = 64;
  int16_t y0 = 60;
  int16_t radius = 50;
  float rad = radians(angle);

  // Ensure the angle is within the range of 0 to 160 degrees
  if (angle < 0) angle = 0;
  if (angle > 160) angle = 160;

  int16_t x1 = x0 + radius * cos(rad);
  int16_t y1 = y0 - radius * sin(rad); // Adjusted to ensure the line goes from left to right

  display.drawLine(x0, y0, x1, y1, SSD1306_WHITE);
  display.display();
}
