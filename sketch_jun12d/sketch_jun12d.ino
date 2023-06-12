// 프로젝트 16 - LED 매트릭스 
#include <Wire.h>
#include "Adafruit_LEDBackpack.h"
#include "adafruit_GFX.h"

Adafruit_BiocolorMatrix matrix = Adafruit_BiocolorMatrix();

void setup() {
  // put your setup code here, to run once:
  matrix.begin(0x70);
}

void loop() {
  // put your main code here, to run repeatedly:
  uint16_t color = random(4)
  int x = random(8);
  int y = random(8);
  matrix.drawPixel(x, y, color);
  matrix.writeDisplay();
  delay(2);
}
