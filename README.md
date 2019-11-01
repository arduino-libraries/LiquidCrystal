# Liquid Crystal Library for Arduino

## Description

This library allows an Arduino board to control LiquidCrystal displays (LCDs) based on the Hitachi HD44780 (or a compatible) chipset, which is found on most text-based LCDs. The library works within either 4- or 8-bit mode (i.e. using 4 or 8 data lines in addition to the rs, enable, and, optionally, the rw control lines).

## Installation

![image](https://user-images.githubusercontent.com/36513474/67681689-a5eee280-f9af-11e9-837d-350f8f0aebd0.png)

### First Method

1. In the Arduino IDE, navigate to Sketch > Include Library > Manage Libraries
1. Then the Library Manager will open and you will find a list of libraries that are already installed or ready for installation.
1. Then search for LiquidCrystal using the search bar.
1. Click on the text area and then select the specific version and install it.

### Second Method

1. Navigate to the Releases page.
1. Download the latest release.
1. Extract the zip file
1. In the Arduino IDE, navigate to Sketch > Include Library > Add .ZIP Library

## Features

- ### Easy to use

    It is simple, basic and very easy to understand. The user only needs to import the library in his code and start using its functions.

- ### Compatible chipset

    ![image](https://user-images.githubusercontent.com/36513474/67893895-4e03d780-fb79-11e9-814b-d8fa03689344.png)

    Using Liquid Crystal library, Arduino board can control liquid displays based on the Hitachi HD44780 chipset. These chipset LCDs are easily available, come in different shapes and sizes.

- ### No technical details required

    A key benefit of using this liquid crystal library is that there is no need to care that much about the technical details or timings when using the display. The library happily does all of this.

- ### Extendable

    The library is extendable, therefore it can grow to support new LCD control devices such as I2C, SPI, Serial, 1wire, RF, CAM, etc.

- ### Intuitive syntax

    Liquid Crystal has a simple and intuitive syntax to handle variables and functions. The user only needs to import the library and calls its functions

- ### Give back

    Liquid Crystal is free for everyone. The licensed library can be copied, redistributed and used in the projects, assignments or anywhere.

## Functions

- LiquidCrystal()
- begin()
- clear()
- home()
- setCursor()
- write()
- print()
- cursor()
- noCursor()
- blink()
- noBlink()
- display()
- noDisplay()
- scrollDisplayLeft()
- scrollDisplayRight()
- autoscroll()
- noAutoscroll()
- leftToRight()
- rightToLeft()
- createChar()

## Example

There are many examples implemented where this library is used. You can find other examples from [Github-Liquid-Crystal](https://github.com/arduino-libraries/LiquidCrystal/tree/master/examples) and [Arduino-Reference](https://www.arduino.cc/en/Reference/LiquidCrystal). The following are the few examples of this library.

### Blink

This sketch prints "Hello World!" to the LCD and makes the cursor block blink.

```C++
#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  lcd.begin(16, 2);
  lcd.print("Hello World!");
}

void loop() {
  lcd.noBlink();
  delay(3000);
  lcd.blink();
  delay(3000);
}
```

### Display

This sketch prints "Hello World!" to the LCD and uses the display() and noDisplay() functions to turn on and off the display.

```C++
#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  lcd.begin(16, 2);
  lcd.print("Hello World!");
}

void loop() {
  lcd.noDisplay();
  delay(500);
  lcd.display();
  delay(500);
}
```

You can find liquid crystal tutorials from [here](https://www.arduino.cc/en/Tutorial/HelloWorld?from=Tutorial.LiquidCrystal)

## Contributing

If you want to contribute to this project:

- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell others about this library
- Contribute new protocols

Please read [CONTRIBUTING.md](https://github.com/arduino-libraries/LiquidCrystal/blob/master/CONTRIBUTING.md) for details on our code of conduct, and the process for submitting pull requests to us.

## Credits

The authors of this library are Arduino and Adafruit. This Library is maintained by Arduino <info@arduino.cc>.

Based on previous work by:

- T. Igoe
- D. A. Mellis
- C. Maglie
- M. Faccihin
- M. kooijman
- A. Guadalupi
- F. Vanzati
- Zeveland
- S. Fitzgerald
- J. Nussbaum
- I. Gupta
- C. Park
- A. Daftery
- A. K. Sahoo
- Isaac

## Current stable version

**version:** v1.0.7

## License

Copyright (C) 2006-2008 Hans-Christoph Steiner. All rights reserved.
Copyright (c) 2010 Arduino LLC. All right reserved.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
