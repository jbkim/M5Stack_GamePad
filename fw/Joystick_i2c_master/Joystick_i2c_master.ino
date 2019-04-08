#include <M5Stack.h>
#include "Wire.h"

#define JOY_ADDR 0x52

#define UP    1
#define DOWN  2
#define LEFT  4
#define RIGHT 8

void setup() {
  M5.begin();
  M5.Lcd.clear();
  //disable the speak noise
  dacWrite(25, 0);

  Wire.begin(21, 22, 400000);
}

uint8_t x_data;
uint8_t y_data;
uint8_t select_data;
uint8_t btn_data;

char data[100];

void loop() {
  // put your main code here, to run repeatedly:
  Wire.requestFrom(JOY_ADDR, 4);
  if (Wire.available()) {
    x_data = Wire.read();
    y_data = Wire.read();
    select_data = Wire.read();
    btn_data = Wire.read();
        
    sprintf(data, "x:%d y:%d button:%d\n", x_data, y_data, select_data);
    Serial.print(data);

    if (btn_data & UP) Serial.println("UP");
    if (btn_data & DOWN) Serial.println("DOWN");
    if (btn_data & LEFT) Serial.println("LEFT");
    if (btn_data & RIGHT) Serial.println("RIGHT");                
  }
  delay(200);
}
