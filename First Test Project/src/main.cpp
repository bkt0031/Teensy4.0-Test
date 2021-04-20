#include <Arduino.h>
#include <ILI9341_t3n.h>
#include <SPI.h>
#include <ili9341_t3n_font_Arial.h>
#include "system.h"

#define ILI9341_RST 23
#define ILI9341_DC 9
#define ILI9341_CS 10

system_t sysData;

char dateStr[15];

void gpt2_isr()
{
  GPT2_SR |= GPT_SR_OF3;
  sysData.timeUpdate = true;
  ++sysData.epoch;
  ++sysData.systemTime.seconds;
  if(sysData.systemTime.seconds == 60u) {
    ++sysData.systemTime.minutes;
    sysData.systemTime.seconds = 0u;
    if(sysData.systemTime.minutes == 60u) {
      ++sysData.systemTime.hours;
      sysData.systemTime.minutes = 0u;
      if(sysData.systemTime.hours == 24u) {
        ++sysData.systemTime.days;
        sysData.systemTime.hours = 0u;
      }
    }
  }
  asm volatile("dsb");
}
void gpt2_init() 
{
  CCM_CCGR0 |= CCM_CCGR0_GPT2_BUS(CCM_CCGR_ON);   // Enable GPT2 bus clock
  GPT2_CR = 0;                                    // Zero out GPT2 Operations
  GPT2_PR = 4095;                                 // Prescale - actual value is prescale + 1
  GPT2_OCR1 = 8;                                  // 32768/4096 = 8 for 1 second interrupt
  GPT2_SR = 0x3f;                                 // bits are cleared by writing a 1 - clear all bits
  GPT2_IR = GPT_IR_OF1IE;                         // OF1IE Output Compare 1 Interrupt Enable
  GPT2_CR = GPT_CR_EN | GPT_CR_CLKSRC(4);         // Enable GPT and set clock source to ipg_clk_32k
  attachInterruptVector(IRQ_GPT2, gpt2_isr);
  NVIC_ENABLE_IRQ(IRQ_GPT2);
}

ILI9341_t3n tft = ILI9341_t3n(ILI9341_CS, ILI9341_DC, ILI9341_RST);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  tft.begin();
  gpt2_init();
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