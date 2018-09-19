# ATtiny13A-MOSFET

Using Atmel Studio 7.0


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
