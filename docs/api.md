# LiquidCrystal

## Functions

### `LiquidCrystal()`

#### Description

Creates a variable of type LiquidCrystal. The display can be controlled using 4 or 8 data lines. If the former, omit the pin numbers for d0 to d3 and leave those lines unconnected. The RW pin can be tied to ground instead of connected to a pin on the Arduino; if so, omit it from this function's parameters.

#### Syntax

```
LiquidCrystal(rs, enable, d4, d5, d6, d7)
LiquidCrystal(rs, rw, enable, d4, d5, d6, d7)
LiquidCrystal(rs, enable, d0, d1, d2, d3, d4, d5, d6, d7)
LiquidCrystal(rs, rw, enable, d0, d1, d2, d3, d4, d5, d6, d7)
```

#### Parameters
rs: the number of the Arduino pin that is connected to the RS pin on the LCD

rw: the number of the Arduino pin that is connected to the RW pin on the LCD (optional)

enable: the number of the Arduino pin that is connected to the enable pin on the LCD

d0, d1, d2, d3, d4, d5, d6, d7: the numbers of the Arduino pins that are connected to the corresponding data pins on the LCD. d0, d1, d2, and d3 are optional; if omitted, the LCD will be controlled using only the four data lines (d4, d5, d6, d7).

#### Example

```
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);

void setup()
{
  lcd.begin(16,1);
  lcd.print("hello, world!");
}

void loop() {}
```

### `begin()`

#### Description

Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display. begin() needs to be called before any other LCD library commands.

#### Syntax

```
lcd.begin(cols, rows)
```

#### Parameters
lcd: a variable of type LiquidCrystal

cols: the number of columns that the display has

rows: the number of rows that the display has

### `clear()`

#### Description

Clears the LCD screen and positions the cursor in the upper-left corner.

#### Syntax

```
lcd.clear()
```

#### Parameters
lcd: a variable of type LiquidCrystal

### `home()`

#### Description

Positions the cursor in the upper-left of the LCD. That is, use that location in outputting subsequent text to the display. To also clear the display, use the clear() function instead.

#### Syntax

```
lcd.home()
```

#### Parameters
lcd: a variable of type LiquidCrystal


### `setCursor()`

#### Description

Position the LCD cursor; that is, set the location at which subsequent text written to the LCD will be displayed.

#### Syntax

```
lcd.setCursor(col, row)
```

#### Parameters
lcd: a variable of type LiquidCrystal

col: the column at which to position the cursor (with 0 being the first column)

row: the row at which to position the cursor (with 0 being the first row)

### `write()`

#### Description

Write a character to the LCD.

#### Syntax

```
lcd.write(data)
```

#### Parameters
lcd: a variable of type LiquidCrystal

data: the character to write to the display

#### Returns

byte
write() will return the number of bytes written, though reading that number is optional

#### Example

```
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  if (Serial.available()) {
    lcd.write(Serial.read());
  }
}
```

### `print()`

#### Description

Prints text to the LCD.

#### Syntax

```
lcd.print(data)
lcd.print(data, BASE)
```

#### Parameters
lcd: a variable of type LiquidCrystal

data: the data to print (char, byte, int, long, or string)

BASE (optional): the base in which to print numbers: BIN for binary (base 2), DEC for decimal (base 10), OCT for octal (base 8), HEX for hexadecimal (base 16).

#### Returns

byte
print() will return the number of bytes written, though reading that number is optional

#### Example

```
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);

void setup()
{
  lcd.print("hello, world!");
}

void loop() {}
```

### `cursor()`

#### Description

Display the LCD cursor: an underscore (line) at the position to which the next character will be written.

#### Syntax

```
lcd.cursor()
```

#### Parameters
lcd: a variable of type LiquidCrystal


### `noCursor()`

#### Description

Hides the LCD cursor.

#### Syntax

```
lcd.noCursor()
```

#### Parameters
lcd: a variable of type LiquidCrystal


### `blink()`

#### Description

Display the blinking LCD cursor. If used in combination with the cursor() function, the result will depend on the particular display.

#### Syntax

```
lcd.blink()
```

#### Parameters
lcd: a variable of type LiquidCrystal

### `noBlink()`

#### Description

Turns off the blinking LCD cursor.

#### Syntax

```
lcd.noBlink()
```

#### Parameters
lcd: a variable of type LiquidCrystal

### `display()`

#### Description

Turns on the LCD display, after it's been turned off with noDisplay(). This will restore the text (and cursor) that was on the display.

#### Syntax

```
lcd.display()
```

#### Parameters
lcd: a variable of type LiquidCrystal

### `noDisplay()`

#### Description

Turns off the LCD display, without losing the text currently shown on it.

#### Syntax

```
lcd.noDisplay()
```

#### Parameters
lcd: a variable of type LiquidCrystal

### `scrollDisplayLeft()`

#### Description

Scrolls the contents of the display (text and cursor) one space to the left.

#### Syntax

```
lcd.scrollDisplayLeft()
```

#### Parameters
lcd: a variable of type LiquidCrystal

### `scrollDisplayRight()`

#### Description

Scrolls the contents of the display (text and cursor) one space to the right.

#### Syntax

```
lcd.scrollDisplayRight()
```

#### Parameters
lcd: a variable of type LiquidCrystal

### `autoscroll()`

#### Description

Turns on automatic scrolling of the LCD. This causes each character output to the display to push previous characters over by one space. If the current text direction is left-to-right (the default), the display scrolls to the left; if the current direction is right-to-left, the display scrolls to the right. This has the effect of outputting each new character to the same location on the LCD.

#### Syntax

```
lcd.autoscroll()
```

#### Parameters
lcd: a variable of type LiquidCrystal

### `noAutoscroll()`

#### Description

Turns off automatic scrolling of the LCD.

#### Syntax

```
lcd.noAutoscroll()
```

#### Parameters
lcd: a variable of type LiquidCrystal

### `leftToRight()`

#### Description

Set the direction for text written to the LCD to left-to-right, the default. This means that subsequent characters written to the display will go from left to right, but does not affect previously-output text.

#### Syntax

```
lcd.leftToRight()
```

#### Parameters
lcd: a variable of type LiquidCrystal

### `rightToLeft()`

#### Description

Set the direction for text written to the LCD to right-to-left (the default is left-to-right). This means that subsequent characters written to the display will go from right to left, but does not affect previously-output text.

#### Syntax

```
lcd.rightToLeft()
```

#### Parameters
lcd: a variable of type LiquidCrystal

### `createChar()`

#### Description

Create a custom character (glyph) for use on the LCD. Up to eight characters of 5x8 pixels are supported (numbered 0 to 7). The appearance of each custom character is specified by an array of eight bytes, one for each row. The five least significant bits of each byte determine the pixels in that row. To display a custom character on the screen, write() its number.

>NB : When referencing custom character "0", if it is not in a variable, you need to cast it as a byte, otherwise the compiler throws an error.

#### Syntax

```
lcd.createChar(num, data)
```

#### Parameters
lcd: a variable of type LiquidCrystal

num: which character to create (0 to 7)

data: the character's pixel data

#### Example

```

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

byte smiley[8] = {
  B00000,
  B10001,
  B00000,
  B00000,
  B10001,
  B01110,
  B00000,
};

void setup() {
  lcd.createChar(0, smiley);
  lcd.begin(16, 2);  
  lcd.write(byte(0));
}

void loop() {}
```