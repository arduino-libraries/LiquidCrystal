#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);
LiquidCrystal_I2C lcd2(0x26, 16, 2);
void setup()
{
	// initialize the LCD
	lcd.begin();
  lcd2.begin();
  lcd.backlight();
  lcd2.backlight();
}

void loop()
{
	bool blinking = true;
  bool blinking2 = false;
	lcd.cursor();
  lcd2.cursor();

	while (1) {
		if (blinking) {
			lcd.clear();
			lcd.print("No cursor blink");
			lcd.noBlink();
			blinking = false;
      lcd.noBacklight();

      lcd2.clear();
			lcd2.print("Cursor blink");
			lcd2.blink();
			blinking2 = true;
      lcd2.backlight();
		} else {
			lcd.clear();
			lcd.print("Cursor blink");
			lcd.blink();
			blinking = true;
      lcd.backlight();

      lcd2.clear();
			lcd2.print("No cursor blink");
			lcd2.noBlink();
			blinking2 = false;
      lcd2.noBacklight();
		}
		delay(4000);
	}
}
