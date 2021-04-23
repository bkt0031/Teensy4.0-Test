#include <Arduino.h>
#include <ILI9341_t3n.h>
#include <SPI.h>
#include <ili9341_t3n_font_Arial.h>
#include "system.h"

#define ILI9341_RST 23
#define ILI9341_DC 9
#define ILI9341_CS 10

char dateStr[15];
uint32_t rtcPtrVal;
system_t sysData = {0u, {0u, 0u, 0u, 0u}, 0u};

ILI9341_t3n tft = ILI9341_t3n(ILI9341_CS, ILI9341_DC, ILI9341_RST);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  tft.begin();
  // gpt2_init();
  snvs_pi_init();
  delay(500);
  Serial.println("Setting up display...");
  Serial.println("   rotation");
  tft.setRotation(3u);
  Serial.println("   font");
  tft.setFont(Arial_12);
  Serial.println("   screen color");
  tft.fillScreen(ILI9341_BLACK);
  Serial.println("   font color");
  tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
  Serial.println("Display \"Hello World\"");
  tft.setCursor(40,80);
  tft.println("Hello World!");
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if(sysData.timeUpdate) {
    sysData.timeUpdate = false;
    sprintf(dateStr, "%03dd %02d:%02d:%02d", 
            sysData.systemTime.days,
            sysData.systemTime.hours, 
            sysData.systemTime.minutes,
            sysData.systemTime.seconds);
    tft.setCursor(40, 120);
    tft.println(dateStr);
  }
  delay(100);
}