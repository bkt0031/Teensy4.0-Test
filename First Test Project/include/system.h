#ifndef SYSTEM_H
#define SYSTEM_H
#include "rtc_time.h"
#include <stdbool.h>
#include <stdint.h>

#define SNVS_HPSR_PI_MASK (0x2U)

void gpt2_isr();
void gpt2_init();
void snvs_isr();
void snvs_pi_init();
extern rtc_time rtc;

#endif