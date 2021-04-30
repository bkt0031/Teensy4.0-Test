#include <Arduino.h>
#include "system.h"
#include "rtc_time.h"


void snvs_isr() 
{
  /*
   * Normally you would read the interrupt status values and act
   * on the code to service the particular interrupt that was
   * generated. In this case only the periodic interrupt is being
   * used so only reset it.
   */
  SNVS_HPSR |= SNVS_HPSR_PI_MASK; // reset interrupt
  rtc.one_second_tick();
  asm volatile("dsb");
}

void snvs_pi_init() 
{
  SNVS_HPCR &= ~SNVS_HPCR_PI_EN;
  while ((SNVS_HPCR & SNVS_HPCR_PI_EN));

  SNVS_HPCR |= SNVS_HPCR_PI_FREQ(0x0F);
  SNVS_HPCR |= SNVS_HPCR_PI_EN;
  while (!(SNVS_HPCR & SNVS_HPCR_PI_EN));

  attachInterruptVector(IRQ_SNVS_IRQ, snvs_isr);
  NVIC_ENABLE_IRQ(IRQ_SNVS_IRQ);
}
