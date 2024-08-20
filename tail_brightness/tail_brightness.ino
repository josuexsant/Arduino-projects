int leds[] = { 3, 5, 6, 9, 10, 11 };
int cursor = 0;
bool right = true;
int tail = 70;
int time = 70;

void setup() {
  for (int i = 0; i < 6; i++) {
    pinMode(leds[i], OUTPUT);
  }
}

void loop() {
  if (right) {
    for (int i = 0; i < 6; i++) {
      analogWrite(leds[i], 255);

      if (i > 0) { 
        analogWrite(leds[i - 1], tail);
        }

      delay(time);

      if (i > 1) {
        analogWrite(leds[i - 2], tail*0.5); 
        }
      if (i > 2) { 
        analogWrite(leds[i - 3], 0); 
      }

      if ( i == 5) {
        delay(30);
        analogWrite(leds[4], 0);
        delay(30);
        analogWrite(leds[3], 0);
        delay(30);
        analogWrite(leds[2], 0);
        delay (200);
      }
    }
    right = false;
  } else {
    for (int i = 5; i >= 0; i--) {
      analogWrite(leds[i], 255);

      if (i < 5) { 
        analogWrite(leds[i + 1], tail);
        }
      delay(time);

      if (i < 4) {
         analogWrite(leds[i + 2], tail*0.5); 
         }
      if (i < 3) { 
        analogWrite(leds[i + 3], 0); 
        }

      if (i == 0){
        delay(30);
        analogWrite(leds[3], 0);
        delay(30);
        analogWrite(leds[2], 0);
        delay(30);
        analogWrite(leds[1], 0);
        delay (200);
       delay(200);
      }
    }

    right = true;
  }
}


