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

uint8_t happy[8] =
{
    0b00000,
    0b10001,
    0b00000,
    0b00000,
    0b10001,
    0b01110,
    0b00000,
    0b00000,
};

uint8_t wow[8] =
{
    0b00000,
    0b10001,
    0b00000,
    0b01110,
    0b10001,
    0b01110,
    0b00000,
    0b00000,
};

uint8_t anchor[8] =
{
    0b01110,
    0b01010,
    0b01110,
    0b00100,
    0b10101,
    0b10101,
    0b01110,
    0b00100
};

uint8_t snow[8] =
{
    0b01000,
    0b11101,
    0b01011,
    0b00001,
    0b00100,
    0b01110,
    0b00100,
    0b10000
};

void setup()
{
    lcd.begin();
    lcd.backlight();

    lcd.createChar(0, happy);
    lcd.createChar(1, wow);
    lcd.createChar(2, anchor);
    lcd.createChar(3, snow);


    lcd.write(0);
    lcd.write(1);
    lcd.write(2);
    lcd.write(3);
}

void loop()
{
}
