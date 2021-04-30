#include <Arduino.h>
#include <ILI9341_t3n.h>
#include <SPI.h>
#include <ili9341_t3n_font_Arial.h>
#include "system.h"
#include "rtc_time.h"

#define ILI9341_RST 23
#define ILI9341_DC 9
#define ILI9341_CS 10

char dateStr[23];
uint32_t rtcPtrVal;

ILI9341_t3n tft = ILI9341_t3n(ILI9341_CS, ILI9341_DC, ILI9341_RST);
rtc_time rtc = rtc_time();

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
  tft.setFont(Arial_16);
  Serial.println("   screen color");
  tft.fillScreen(ILI9341_BLACK);
  Serial.println("   font color");
  tft.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
  Serial.println("Display \"Hello World\"");
  tft.setCursor(40,80);
  tft.println("Hello World!");
  rtc.create_date_time_string(dateStr, sizeof(dateStr), format_24);
  tft.setCursor(40, 120);
  tft.println(dateStr);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(rtc.is_tick()) {
    rtc.clear_tick();
    rtc.create_date_time_string(dateStr, sizeof(dateStr), format_24);
    tft.setCursor(40, 120);
    tft.println(dateStr);
    Serial.printf("tft: %s\n", dateStr);
  }
  delay(100);
}