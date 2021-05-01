# Teensy4.0-Test
A noodling around repository for the Teensy 4.0
## Introduction
I have been doing a lot of programming over the past 5 years in the Cypress Semiconductor/Infineon Technology PSoC realm specifically the 5LP. While I really enjoy designing with their PSoCs there are concerns with the Infineon acquision of Cypress as product development seems to have slowed. There have been no new updates to PSoC Creator in a while, and even their last news blog post is coming up on a year old. I would not say it is completely silent, but in my perspective it has slowed.

With that in mind I decided to spread out a bit more exploring other microcontrollers and PSoC devices. The Teensy 4.0 is my first such device. Personally I have in the past steered clear of anything embracing the Arduino framework as I found it too limiting in the development sense. The lack of JTAG/SWD/etc. support is a frustration point for me to the level that I don't think I want to really develop anything serious with the Teensy, but there is an entertainment value exploring what is there (plus the price is right.) 

These projects are part of the Teensy 4.0 exploration. There are no goals in mind other than to code up accessing different peripherals (Serial/SPI/I2C/I2S/etc) and components of the NXP IMXRT1062. Just getting a feel for how the PSoC works and how to code for it. I will be using the PlatformIO Visual Studio Code IDE for the development effort. 

## Test Project Idea
Somthing I have been thinking about while tinkering around with the real time clock in the Teensy 4.0 is maybe replacing an iPhone app I use for an alarm clock. The app has multiple alarm selections that can be configured and will alarm by slowly raising the volume of a song randomly selected from a playlist. Unfortunately Apple has severe restrictions on apps accessing a playlist so the app writer has to play games to make it work, and Apple seems to break it periodically with IOS updates. This kind of project would tick most of the boxes I have with regards to testing the Teensy 4.0 functionality. 

### High Level Requirements
* Multiple alarms can be configured
* Alarm can play music stored on an SD card
* Alarm can be set to ramp up volume of music played
* The clock should be syncronized with an external time source (GPS, WWVB, NTP, etc.)
* The clock should adjust for Daylight Savings Time
* Battery backup for power failure
* Utilize a display to show time, menues, and configuration options

I have most of the components required for this kind of project:

* Teensy 4.0 Development Board
* Teensy 4.0 Audio Adapter Board
* TFT Display
* WWVB Receiver Board (EverSet ES100)

While I'm not 100% sold on using WWVB for time syncronization it does have it's benefits over the other options. Still I have a GPS board as well as an Ethernet controller board that I can play with if needed.

This would be a back burner project as I have two other higher priority things I am working on at present. 