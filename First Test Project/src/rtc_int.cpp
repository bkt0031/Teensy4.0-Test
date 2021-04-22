#include <Arduino.h>
#include "system.h"

void snvs_isr() 
{
  /*
   * Normally you would read the interrupt status values and act
   * on the code to service the particular interrupt that was
   * generated. In this case only the periodic interrupt is being
   * used so only reset it.
   */
  SNVS_HPSR |= SNVS_HPSR_PI_MASK; // reset interrupt
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

void snvs_pi_init() 
{
  SNVS_HPCR &= ~SNVS_HPCR_PI_EN;
  while ((SNVS_HPCR & SNVS_HPCR_PI_EN))
    ;

  SNVS_HPCR |= SNVS_HPCR_PI_FREQ(0x0F);
  SNVS_HPCR |= SNVS_HPCR_PI_EN;
  while (!(SNVS_HPCR & SNVS_HPCR_PI_EN))
    ;

  attachInterruptVector(IRQ_SNVS_IRQ, snvs_isr);
  NVIC_ENABLE_IRQ(IRQ_SNVS_IRQ);
}
