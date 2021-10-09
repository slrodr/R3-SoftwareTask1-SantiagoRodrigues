# Software Task 1
**Objective:** Wiring two 7-segments display to an Arduino Uno using two CD4511 BCD to 7-segments decoders with a potentiometer. The two displays are then programmed to show a number from 00 to 99 based on the potentiometer reading. 
[TinkerCAD Project](https://www.tinkercad.com/things/7LsDfke30OW)
## Wiring
Starting with the potentiometer, it was connected to GND and 5V-Vcc. Its output was connected to A0. It's important to remember that a potentiometer needs an analog pin and not a digital one. 

A 7 segment display is a component that, as the name suggests, is composed of 7 LEDs arranged in such a way that different combinations of LEDs lighting up can produce a number from 0 to 9. If all LEDs are turned on, the displayed number is 8. In this display, pins a-g correspond to the individual LED segments. Pin DP corresponds to the decimal point LED. Finally, the two "com" pins are common with either ground or power (depending on the type of display used). In this project, both displays used were of the type cathode, therefore, their "com" pins were common with ground. Since the decimal point wasn't needed for this project, it was also connected to ground.

The CD4511 is a BCD to 7 segment decoder. It takes a number in binary form as input and displays this number on a 7 segment display. Therefore, it has 4 input pins and 7 output pins (one for each LED segment). Pin 8 is connected to GND and pin 16 is connected to Vcc. Pins 9-15 correspond to the a-f pins in the 7 segment display (output pins). Pins D0-D3 (7, 1, 2, 6) are the pins for the 4-bit input, these are the pins connected to the Arduino Uno. Pin 5 is the Latch Enabled pin (LE). When LE is high the current stage is stored and the display does not change. 


## Code
The code is quite straightforward. It starts by reading the value from the potentiometer. Since this value is originally from 0 to 1023, it is mapped to be equivalent of 0 to 99. Next, this sensor value is separated into two numbers, the units (from 0 to 9) and the tens (multiples of 10). For instance, 13 would be separated into 3 (unit) and 1 (ten), 99 would be separated into 9 (unit) and 9 (tens). The first display displays the tens and the second one displays the units. This is done through the following code:

    int secondDigit = sensorValue % 10;
    int firstDigit = (sensorValue - secondDigit)/ 10

The next step is getting the 4-bit input that corresponds to each digit. This is done with the help of two functions *firstNumber* and *secondNumber*. It works by iterating through an array that corresponds to pins D0-D3 of the BCD decoder and writing the 4-bit sequence equivalent to the digit. However, it writes it from least-significant bit to most significant. The least-significant bit is at the leftmost position here. 

## Issues
It seems the displays only display odd numbers. Possibly because of the way the potentiometer values are mapped from 0-99 some values had no direct correspondence from the read potentiometer values.
I tried to fix it in several ways. One of them was mapping the values from 0-100 and then correcting any read values equal to 100 to be equal to 99. This does work and yields more even numbers showing in the displays. However, the reading is essentially wrong since the mapping from 0 to 99 is very different from mapping from 0 to 100. Another thing tried was mapping from 1-100 and then taking each sensorValue n to be equal to n-1. This also works, but with the same issue previously discussed.
