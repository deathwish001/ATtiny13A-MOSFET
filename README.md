# ATtiny13A-MOSFET

## Overview

I had been searching on how to run an esp8266 data logger with minimumal power consumption on a 18650 3.7V Li-ion battery and come accross this solution.<sup>[1](#solution)</sup>

Althought you can minimise the power consuption of an esp8266 with deep sleep, usually you have other sensors/chips that are cosuming power. The idea is to use an Atmel ATtiny13A - *Microchip picoPower 8-bit AVR RISC-based microcontroller*, it's up and running 24/7 while everything else is without power, so the consumption of the rest of the circuit is 0A. ATtyni13A consumption is only 0.005mA (5µA) in a sleep mode.

As you can see, ATtyni13A is used only as a controller of 1 N-channel MOSFET, that is turning on/off a 3.3V power regulator for the esp8266 and it's sensors.</br></br>

## Required Materials

1. [Atmel ATtiny13A](https://www.microchip.com/wwwproducts/en/ATtiny13A)
1. [USBasp AVR programmer](https://www.aliexpress.com/store/product/USBasp-USBISP-3-3V-5V-AVR-Programmer-USB-ATMEGA8-L/1414081_2036883289.html?spm=2114.12010615.8148356.4.306e1808eNfb5t)
1. [AVR dude 6.3](http://www.nongnu.org/avrdude/)
1. [Atmel Studio 7.0](http://www.microchip.com/mplab/avr-support/atmel-studio-7)








## Referances
<a name="solution">1</a>: Home Circuits Blog - [Low power (5microA) ATtiny13A](https://homecircuits.eu/blog/low-power-picopower-attiny13a/)









# CPU Frequency / Fuses

avrdude command line with Atmel Studio 7.0 External Tools
```
Title: USBasp
Command: c:\users\<user>\Documents\Atmel Studio\avrdude-6.3-mingw32\avrdude.exe
Arguments: avrdude -v -pattiny13 -cusbasp -Pusb -U flash:w:"$(ProjectDir)Debug\$(TargetName).hex":i
Use Output Window: True
```
```
Title: USBasp fuse
Command: c:\users\<user>\Documents\Atmel Studio\avrdude-6.3-mingw32\avrdude.exe
Arguments: avrdude -v -pattiny13 -cusbasp -Pusb -Ulfuse:w:0x6A:m -Uhfuse:w:0xFF:m -Ulock:w:0xFF:m
Use Output Window: True

```
