#ifndef MAIN_H
    #define MAIN_H
    #include <stdint.h>
    #include <stdbool.h>

    #define SNVS_HPSR_PI_MASK (0x2U)

    struct systime_t {
        uint8_t seconds;
        uint8_t minutes;
        uint8_t hours;
        uint8_t days;
    };

    struct system_t {
        volatile uint32_t epoch;
        volatile systime_t systemTime;
        volatile bool timeUpdate;
    };

    system_t sysData;

    void gpt2_isr();
    void gpt2_init();
    void snvs_isr();
    void snvs_pi_init();

#endif