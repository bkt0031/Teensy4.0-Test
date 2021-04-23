# First Test Project
# Description
Pretty boring stuff here. Along with the Teensy4.0 I purchased a QVGA (320x240) 2.2" TFT Display from China. In this project I will create a *Hello World!* clock of sorts just to test out SPI, interrupts, the RTC, and this crazy display. I'm also just trying to get used to the PlatformIO way of doing things as well as getting into using C++ for microcontroller development (not my language of choice - sorry). I'm sure my coding will keep wandering back to C - it will take some time.

* My first pass was to use an interrupt off of GPT2 connected to the 32.768 KHz clock. Something was not right as the clock was lagging behind. Most likely I got something messed up with the prescaler or OCR value. Back to the +3000 page i.MX RT1060 Processor Reference Manual where found out you can generate an periodic interrupt directly from the RTC (SNVS function block). I coded that up and now the system epoch counter is much better.
