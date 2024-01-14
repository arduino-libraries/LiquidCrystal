/*
    LiquidCrystal_I2C - Arduino library to control a 16x2 LCD via an I2C adapter based on PCF8574

    Copyright(C) 2020 Blackhack <davidaristi.0504@gmail.com>

    This program is free software : you can redistribute it and /or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.If not, see < https://www.gnu.org/licenses/>.
*/

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4); // Default address of most PCF8574 modules, change according

/*
* When using lcd.print() (and almost everywhere you use string literals),
* is a good idea to use the macro F(String literal).
* This tells the compiler to store the string array in the flash memory
* instead of the ram memory. Usually you have more spare flash than ram.
* More info: https://www.arduino.cc/reference/en/language/variables/utilities/progmem/
*/

void setup()
{
    lcd.begin();
    lcd.backlight();
}

void loop()
{
    //Autoscroll
    lcd.setCursor(5, 0);
    lcd.print(F("Autoscrolling"));
    lcd.setCursor(10, 1);
    lcd.autoscroll();

    for (int i = 0; i < 10; i++)
    {
        lcd.print(i);
        delay(1000);
    }

    lcd.noAutoscroll();
    lcd.clear();

    // Scroll left and right
    lcd.setCursor(10, 0);
    lcd.print(F("To the left!"));
    for (int i = 0; i < 10; i++)
    {
        lcd.scrollDisplayLeft();
        delay(1000);
    }
    lcd.clear();
    lcd.print(F("To the right!"));
    for (int i = 0; i < 10; i++)
    {
        lcd.scrollDisplayRight();
        delay(1000);
    }
    lcd.clear();

    //Cursor
    lcd.setCursor(0, 0);
    lcd.cursor();
    lcd.print(F("Cursor"));
    delay(6000);
    lcd.clear();

    //Cursor blink
    lcd.setCursor(0, 0);
    lcd.blink();
    lcd.print(F("Cursor blink"));
    delay(6000);
    lcd.clear();

    //Blink without cursor
    lcd.setCursor(0, 0);
    lcd.noCursor();
    lcd.print(F("Just blink"));
    delay(6000);
    lcd.noBlink();
    lcd.clear();
}
