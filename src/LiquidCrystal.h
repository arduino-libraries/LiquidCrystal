#ifndef LiquidCrystal_h
#define LiquidCrystal_h

#include <inttypes.h>
#include "Print.h"

#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

#define LCD_BACKLIGHT 0x08
#define LCD_NOBACKLIGHT 0x00
#define En 0x04
#define Rw 0x02
#define Rs 0x01

class LiquidCrystal : public Print {
public:
  LiquidCrystal(uint8_t lcd_addr, uint8_t lcd_cols, uint8_t lcd_rows);
  LiquidCrystal(uint8_t rs, uint8_t enable,
    uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
    uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);
  LiquidCrystal(uint8_t rs, uint8_t rw, uint8_t enable,
    uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
    uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);
  LiquidCrystal(uint8_t rs, uint8_t rw, uint8_t enable,
    uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3);
  LiquidCrystal(uint8_t rs, uint8_t enable,
    uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3);

  void init(uint8_t fourbitmode, uint8_t rs, uint8_t rw, uint8_t enable,
      uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
      uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);

  void begin(uint8_t cols, uint8_t rows, uint8_t charsize = LCD_5x8DOTS);

  void clear();
  void home();

  void noDisplay();
  void display();
  void noBlink();
  void blink();
  void noCursor();
  void cursor();
  void scrollDisplayLeft();
  void scrollDisplayRight();
  void leftToRight();
  void rightToLeft();
  void autoscroll();
  void noAutoscroll();

  void setRowOffsets(int row1, int row2, int row3, int row4);
  void createChar(uint8_t, uint8_t[]);
  void setCursor(uint8_t, uint8_t);
  virtual size_t write(uint8_t);
  void command(uint8_t);

  using Print::write;

  void backlight();
  void noBacklight();
  void setBacklightPin(uint8_t pin, uint8_t polarity);
  void printAt(uint8_t col, uint8_t row, const char* str);
  void printf(const char* format, ...);
  void printCenter(uint8_t row, const char* str);
  void printRight(uint8_t row, const char* str);
  void clearLine(uint8_t row);
  uint8_t getCursorCol() const { return _current_col; }
  uint8_t getCursorRow() const { return _current_row; }
  void saveCursor();
  void restoreCursor();
  void createCharFromProgmem(uint8_t location, const uint8_t charmap[]);
  void scrollLineLeft(uint8_t row);
  void scrollLineRight(uint8_t row);
  void startAsyncScroll(uint8_t row, uint32_t interval);
  void updateAsyncScroll();
  void stopAsyncScroll();
  void typewrite(const char* str, uint16_t delay_ms);
  void progressHorizontal(uint8_t row, uint8_t percentage);

private:
  void send(uint8_t, uint8_t);
  void write4bits(uint8_t);
  void write8bits(uint8_t);
  void pulseEnable();
  void i2cTransmit(uint8_t value);
  void write4bitsI2C(uint8_t value);

  uint8_t _rs_pin;
  uint8_t _rw_pin;
  uint8_t _enable_pin;
  uint8_t _data_pins[8];
  uint8_t _backlight_pin;
  uint8_t _bl_polarity;

  uint8_t _LcdAddr;
  uint8_t _backlightval;
  uint8_t _isI2C;

  uint8_t _displayfunction;
  uint8_t _displaycontrol;
  uint8_t _displaymode;

  uint8_t _initialized;
  uint8_t _numcols;
  uint8_t _numlines;
  uint8_t _row_offsets[4];

  uint8_t _current_col;
  uint8_t _current_row;
  uint8_t _saved_col;
  uint8_t _saved_row;

  uint8_t _scroll_row;
  uint32_t _scroll_interval;
  uint32_t _last_scroll_time;
  uint32_t _typewrite_last_time;
};

#endif
