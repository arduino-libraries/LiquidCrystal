#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 for a 16 chars and 2 line display
// LiquidCrystal_I2C lcd(0x27, 20, 4);
LiquidCrystal_I2C *lcd = NULL;

void setup()
{
	Serial.begin(9600);
	delay(1000);
	// initialize the LCD
	Serial.println("Starting");

	lcd = new LiquidCrystal_I2C(0x27, 20, 4);
	lcd->begin();
	lcd->clear();
	lcd->home();

	lcd->setCursor(0, 0);

	// Turn on the blacklight and print a message.
	lcd->backlight();
	lcd->print("Hello, world!");

	delay(4000);

}

void loop()
{
	lcd->noBacklight();
	delay(4000);
	lcd->backlight();

	delay(4000);

	lcd->clear();
	delay(4000);

	lcd->display();

	delay(4000);

	lcd->noDisplay();

	delay(4000);
}
