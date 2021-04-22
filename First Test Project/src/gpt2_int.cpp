#include <Arduino.h>
#include "system.h"

void gpt2_isr() 
{
  GPT2_SR |= GPT_SR_OF3;
  sysData.timeUpdate = true;
  ++sysData.epoch;
  ++sysData.systemTime.seconds;
  if (sysData.systemTime.seconds == 60u) {
    ++sysData.systemTime.minutes;
    sysData.systemTime.seconds = 0u;
    if (sysData.systemTime.minutes == 60u) {
      ++sysData.systemTime.hours;
      sysData.systemTime.minutes = 0u;
      if (sysData.systemTime.hours == 24u) {
        ++sysData.systemTime.days;
        sysData.systemTime.hours = 0u;
      }
    }
  }
  asm volatile("dsb");
}

void gpt2_init() {
  CCM_CCGR0 |= CCM_CCGR0_GPT2_BUS(CCM_CCGR_ON); // Enable GPT2 bus clock
  GPT2_CR = 0;                                  // Zero out GPT2 Operations
  GPT2_PR = 4095;         // Prescale - actual value is prescale + 1
  GPT2_OCR1 = 8;          // 32768/4096 = 8 for 1 second interrupt
  GPT2_SR = 0x3f;         // bits are cleared by writing a 1 - clear all bits
  GPT2_IR = GPT_IR_OF1IE; // OF1IE Output Compare 1 Interrupt Enable
  GPT2_CR = GPT_CR_EN |
            GPT_CR_CLKSRC(4); // Enable GPT and set clock source to ipg_clk_32k
  attachInterruptVector(IRQ_GPT2, gpt2_isr);
  NVIC_ENABLE_IRQ(IRQ_GPT2);
}
