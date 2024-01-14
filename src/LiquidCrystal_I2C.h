#ifndef FDB_LIQUID_CRYSTAL_I2C_H
#define FDB_LIQUID_CRYSTAL_I2C_H

#include "LiquidCrystal_Base.h"

// flags for backlight control
#define LCD_BACKLIGHT 0x08
#define LCD_NOBACKLIGHT 0x00

#define En B00000100  // Enable bit
#define Rw B00000010  // Read/Write bit
#define Rs B00000001  // Register select bit


class LiquidCrystal_I2C : public LiquidCrystal_Base {
public:
	
	LiquidCrystal_I2C(uint8_t lcd_addr, uint8_t lcd_cols, uint8_t lcd_rows, uint8_t charsize = LCD_5x8DOTS);
	void init(uint8_t lcd_addr, uint8_t lcd_cols, uint8_t lcd_rows, uint8_t charsize = LCD_5x8DOTS);
	void begin();
	void printLeft();
	void printRight();
	void setCursor(uint8_t col, uint8_t row);
	
	void shiftIncrement(); //todo
	void shiftDecrement();
	
	void noBacklight();
	void backlight();
	bool getBacklight();

	inline void blink_on() { blink(); } // todo? transfer in base classe
	inline void blink_off() { noBlink(); }
	inline void cursor_on() { cursor(); }
	inline void cursor_off() { noCursor(); }

// Compatibility API function aliases
	void setBacklight(uint8_t new_val);				// alias for backlight() and nobacklight()
	void load_custom_character(uint8_t char_num, uint8_t *rows);	// alias for createChar()
	void printstr(const char[]);

	virtual size_t write(uint8_t value);
	virtual void command(uint8_t value);
	virtual void write4bits(uint8_t value);
private:
	void send(uint8_t, uint8_t);
	void expanderWrite(uint8_t);
	void pulseEnable(uint8_t);
	uint8_t _addr;
	uint8_t _backlightval;
};

#endif 
