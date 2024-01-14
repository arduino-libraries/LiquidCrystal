#include "LiquidCrystal_Base.h"

void LiquidCrystal_Base::init(uint8_t lcd_cols,  uint8_t lcd_rows, uint8_t charsize)
{
    _cols = lcd_cols;
	_rows = lcd_rows;

    if (_rows > 1) {
		_displayfunction |= LCD_2LINE;
	}

    if ((charsize != 0) && (_rows == 1)) {
		_displayfunction |= LCD_5x10DOTS;
	}
}

void LiquidCrystal_Base::begin()
{
    // put the LCD into 4 bit or 8 bit mode
    if (!(_displayfunction & LCD_8BITMODE))
    {
        // this is according to the Hitachi HD44780 datasheet
        // figure 24, pg 46

        // we start in 8bit mode, try to set 4 bit mode
        write4bits(0x03);        // <<4
        delayMicroseconds(4500); // wait min 4.1ms

        // second try
        write4bits(0x03);        // <<4
        delayMicroseconds(4500); // wait min 4.1ms

        // third go!
        write4bits(0x03); // <<4
        delayMicroseconds(150);

        // finally, set to 4-bit interface
        write4bits(0x02); // <<4
    }
    else
    {
        // this is according to the Hitachi HD44780 datasheet
        // page 45 figure 23

        // Send function set command sequence
        command(LCD_FUNCTIONSET | _displayfunction);
        delayMicroseconds(4500); // wait more than 4.1 ms

        // second try
        command(LCD_FUNCTIONSET | _displayfunction);
        delayMicroseconds(150);

        // third go
        command(LCD_FUNCTIONSET | _displayfunction);
    }

    // set # lines, font size, etc.
    command(LCD_FUNCTIONSET | _displayfunction);

    // turn the display on with no cursor or blinking default
    _displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
    display();

    // clear it off
    clear();

    // Initialize to default text direction (for romance languages)
    _displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
    // set the entry mode
    command(LCD_ENTRYMODESET | _displaymode);

    home();
}

/********** high level commands, for the user! */
void LiquidCrystal_Base::clear(){
	command(LCD_CLEARDISPLAY);// clear display, set cursor position to zero
	delayMicroseconds(2000);  // this command takes a long time!
}

void LiquidCrystal_Base::home(){
	command(LCD_RETURNHOME);  // set cursor position to zero
	delayMicroseconds(2000);  // this command takes a long time!
}
// Turn the display on/off (quickly)
void LiquidCrystal_Base::noDisplay() {
  _displaycontrol &= ~LCD_DISPLAYON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void LiquidCrystal_Base::display() {
  _displaycontrol |= LCD_DISPLAYON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// Turns the underline cursor on/off
void LiquidCrystal_Base::noCursor() {
  _displaycontrol &= ~LCD_CURSORON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void LiquidCrystal_Base::cursor() {
  _displaycontrol |= LCD_CURSORON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// Turn on and off the blinking cursor
void LiquidCrystal_Base::noBlink() {
  _displaycontrol &= ~LCD_BLINKON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}
void LiquidCrystal_Base::blink() {
  _displaycontrol |= LCD_BLINKON;
  command(LCD_DISPLAYCONTROL | _displaycontrol);
}

// These commands scroll the display without changing the RAM
void LiquidCrystal_Base::scrollDisplayLeft(void) {
  command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}
void LiquidCrystal_Base::scrollDisplayRight(void) {
  command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

// This is for text that flows Left to Right
void LiquidCrystal_Base::leftToRight(void) {
  _displaymode |= LCD_ENTRYLEFT;
  command(LCD_ENTRYMODESET | _displaymode);
}

// This is for text that flows Right to Left
void LiquidCrystal_Base::rightToLeft(void) {
  _displaymode &= ~LCD_ENTRYLEFT;
  command(LCD_ENTRYMODESET | _displaymode);
}

// This will 'right justify' text from the cursor
void LiquidCrystal_Base::autoscroll(void) {
  _displaymode |= LCD_ENTRYSHIFTINCREMENT;
  command(LCD_ENTRYMODESET | _displaymode);
}

// This will 'left justify' text from the cursor
void LiquidCrystal_Base::noAutoscroll(void) {
  _displaymode &= ~LCD_ENTRYSHIFTINCREMENT;
  command(LCD_ENTRYMODESET | _displaymode);
}

// Allows us to fill the first 8 CGRAM locations
// with custom characters
void LiquidCrystal_Base::createChar(uint8_t location, uint8_t charmap[]) {
  location &= 0x7; // we only have 8 locations 0-7
  command(LCD_SETCGRAMADDR | (location << 3));
  for (int i=0; i<8; i++) {
    write(charmap[i]);
  }
}

void LiquidCrystal_Base::setCursor(uint8_t col, uint8_t row,  uint8_t offsets[])
{
    if (row > _rows) {
		row = _rows-1;    // we count rows starting w/0
	}
	command(LCD_SETDDRAMADDR | (col + offsets[row]));
}

void LiquidCrystal_Base::printstr(const char c[]){
	//This function is not identical to the function used for "real" I2C displays
	//it's here so the user sketch doesn't have to be changed
	print(c);
}