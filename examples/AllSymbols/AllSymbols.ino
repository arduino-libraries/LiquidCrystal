#include <Wire.h>
#include <LiquidCrystal_I2C.h>

uint8_t bell[8] = {0x4, 0xe, 0xe, 0xe, 0x1f, 0x0, 0x4};
uint8_t note[8] = {0x2, 0x3, 0x2, 0xe, 0x1e, 0xc, 0x0};
uint8_t clock[8] = {0x0, 0xe, 0x15, 0x17, 0x11, 0xe, 0x0};
uint8_t heart[8] = {0x0, 0xa, 0x1f, 0x1f, 0xe, 0x4, 0x0};
uint8_t duck[8] = {0x0, 0xc, 0x1d, 0xf, 0xf, 0x6, 0x0};
uint8_t check[8] = {0x0, 0x1, 0x3, 0x16, 0x1c, 0x8, 0x0};
uint8_t cross[8] = {0x0, 0x1b, 0xe, 0x4, 0xe, 0x1b, 0x0};
uint8_t retarrow[8] = {0x1, 0x1, 0x5, 0x9, 0x1f, 0x8, 0x4};

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
		0b00100};

uint8_t snow[8] =
	{
		0b01000,
		0b11101,
		0b01011,
		0b00001,
		0b00100,
		0b01110,
		0b00100,
		0b10000};

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 20, 4);
LiquidCrystal_I2C lcd2(0x26, 16, 2);

LiquidCrystal_I2C *lcd_ptr;

void setup()
{
	lcd.begin();
	lcd2.begin();

	lcd.createChar(0, bell);
	lcd.createChar(1, note);
	lcd.createChar(2, clock);
	lcd.createChar(3, heart);
	lcd.createChar(4, duck);
	lcd.createChar(5, check);
	lcd.createChar(6, cross);
	lcd.createChar(7, retarrow);

	lcd2.createChar(0, happy);
	lcd2.createChar(1, wow);
	lcd2.createChar(2, anchor);
	lcd2.createChar(3, snow);

	lcd.print("LCD Memory");
	lcd2.print("LCD Memory");

	delay(5000);
	displayKeyCodes();
}

void keyCodes2004(uint8_t i)
{
	lcd.clear();
	lcd.print("Codes 0x");
	lcd.print(i, HEX);
	lcd.print("-0x");
	lcd.print(i + 16, HEX);
	lcd.setCursor(0, 1);

	for (int j = 0; j < 16; j++)
	{
		lcd.write(i + j);
	}
	
}

void keyCodes1602(uint8_t i)
{
	lcd2.clear();
	lcd2.print("Codes 0x");
	lcd2.print(i, HEX);
	lcd2.print("-0x");
	lcd2.print(i + 16, HEX);
	lcd2.setCursor(0, 1);

	for (int j = 0; j < 16; j++)
	{
		lcd2.write(i + j);
	}
	
}

// display all keycodes
void displayKeyCodes(void)
{
	uint8_t i = 0;

	while (1)
	{

		keyCodes2004(i);
		keyCodes1602(i);
		delay(5000);

    i += 16;
	}
}

void loop()
{
	displayKeyCodes();
}
