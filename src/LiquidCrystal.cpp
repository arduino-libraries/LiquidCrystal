#include "LiquidCrystal.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <inttypes.h>
#include "Arduino.h"
#include <Wire.h>

LiquidCrystal::LiquidCrystal(uint8_t lcd_addr, uint8_t lcd_cols, uint8_t lcd_rows) {
  _LcdAddr = lcd_addr;
  _numcols = lcd_cols;
  _numlines = lcd_rows;
  _isI2C = 1;
  _backlightval = LCD_NOBACKLIGHT;
  _displayfunction = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;
}

LiquidCrystal::LiquidCrystal(uint8_t rs, uint8_t rw, uint8_t enable,
           uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
           uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7) {
  _isI2C = 0;
  init(0, rs, rw, enable, d0, d1, d2, d3, d4, d5, d6, d7);
}

LiquidCrystal::LiquidCrystal(uint8_t rs, uint8_t enable,
           uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
           uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7) {
  _isI2C = 0;
  init(0, rs, 255, enable, d0, d1, d2, d3, d4, d5, d6, d7);
}

LiquidCrystal::LiquidCrystal(uint8_t rs, uint8_t rw, uint8_t enable,
           uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3) {
  _isI2C = 0;
  init(1, rs, rw, enable, d0, d1, d2, d3, 0, 0, 0, 0);
}

LiquidCrystal::LiquidCrystal(uint8_t rs,  uint8_t enable,
           uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3) {
  _isI2C = 0;
  init(1, rs, 255, enable, d0, d1, d2, d3, 0, 0, 0, 0);
}

void LiquidCrystal::init(uint8_t fourbitmode, uint8_t rs, uint8_t rw, uint8_t enable,
       uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3,
       uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7) {
  _rs_pin = rs;
  _rw_pin = rw;
  _enable_pin = enable;
  _backlight_pin = 255;
  _bl_polarity = 1;
  _current_col = 0;
  _current_row = 0;
  _scroll_interval = 0;
  _initialized = 0;

  _data_pins[0] = d0; _data_pins[1] = d1; _data_pins[2] = d2; _data_pins[3] = d3;
  _data_pins[4] = d4; _data_pins[5] = d5; _data_pins[6] = d6; _data_pins[7] = d7;

  if (fourbitmode)
    _displayfunction = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;
  else
    _displayfunction = LCD_8BITMODE | LCD_1LINE | LCD_5x8DOTS;

  begin(16, 1);
}

void LiquidCrystal::begin(uint8_t cols, uint8_t lines, uint8_t dotsize) {
  _numcols = cols;
  _numlines = lines;

  if (_isI2C) {
    Wire.begin();
    _displayfunction |= LCD_2LINE;
  } else {
    if (lines > 1) {
      _displayfunction |= LCD_2LINE;
    }
  }

  setRowOffsets(0x00, 0x40, 0x00 + cols, 0x40 + cols);

  if ((dotsize != LCD_5x8DOTS) && (lines == 1)) {
    _displayfunction |= LCD_5x10DOTS;
  }

  if (_isI2C) {
    delayMicroseconds(50000);
    write4bitsI2C(0x03 << 4);
    delayMicroseconds(4500);
    write4bitsI2C(0x03 << 4);
    delayMicroseconds(4500);
    write4bitsI2C(0x03 << 4);
    delayMicroseconds(150);
    write4bitsI2C(0x02 << 4);
  } else {
    pinMode(_rs_pin, OUTPUT);
    if (_rw_pin != 255) pinMode(_rw_pin, OUTPUT);
    pinMode(_enable_pin, OUTPUT);
    for (int i=0; i<((_displayfunction & LCD_8BITMODE) ? 8 : 4); ++i) {
      pinMode(_data_pins[i], OUTPUT);
    }
    delayMicroseconds(50000);
    digitalWrite(_rs_pin, LOW);
    digitalWrite(_enable_pin, LOW);
    if (_rw_pin != 255) digitalWrite(_rw_pin, LOW);

    if (! (_displayfunction & LCD_8BITMODE)) {
      write4bits(0x03); delayMicroseconds(4500);
      write4bits(0x03); delayMicroseconds(4500);
      write4bits(0x03); delayMicroseconds(150);
      write4bits(0x02);
    } else {
      command(LCD_FUNCTIONSET | _displayfunction); delayMicroseconds(4500);
      command(LCD_FUNCTIONSET | _displayfunction); delayMicroseconds(150);
      command(LCD_FUNCTIONSET | _displayfunction);
    }
  }

  command(LCD_FUNCTIONSET | _displayfunction);
  _displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
  display();
  clear();
  _displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;
  command(LCD_ENTRYMODESET | _displaymode);
  _initialized = 1;
}

void LiquidCrystal::setRowOffsets(int row0, int row1, int row2, int row3) {
  _row_offsets[0] = row0; _row_offsets[1] = row1;
  _row_offsets[2] = row2; _row_offsets[3] = row3;
}

void LiquidCrystal::clear() {
  command(LCD_CLEARDISPLAY);
  delayMicroseconds(2000);
  _current_col = 0;
  _current_row = 0;
}

void LiquidCrystal::home() {
  command(LCD_RETURNHOME);
  delayMicroseconds(2000);
  _current_col = 0;
  _current_row = 0;
}

void LiquidCrystal::setCursor(uint8_t col, uint8_t row) {
  const size_t max_lines = sizeof(_row_offsets) / sizeof(*_row_offsets);
  if (row >= max_lines) row = max_lines - 1;
  if (row >= _numlines) row = _numlines - 1;
  _current_col = col;
  _current_row = row;
  command(LCD_SETDDRAMADDR | (col + _row_offsets[row]));
}

void LiquidCrystal::noDisplay() { _displaycontrol &= ~LCD_DISPLAYON; command(LCD_DISPLAYCONTROL | _displaycontrol); }
void LiquidCrystal::display() { _displaycontrol |= LCD_DISPLAYON; command(LCD_DISPLAYCONTROL | _displaycontrol); }
void LiquidCrystal::noCursor() { _displaycontrol &= ~LCD_CURSORON; command(LCD_DISPLAYCONTROL | _displaycontrol); }
void LiquidCrystal::cursor() { _displaycontrol |= LCD_CURSORON; command(LCD_DISPLAYCONTROL | _displaycontrol); }
void LiquidCrystal::noBlink() { _displaycontrol &= ~LCD_BLINKON; command(LCD_DISPLAYCONTROL | _displaycontrol); }
void LiquidCrystal::blink() { _displaycontrol |= LCD_BLINKON; command(LCD_DISPLAYCONTROL | _displaycontrol); }
void LiquidCrystal::scrollDisplayLeft(void) { command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT); }
void LiquidCrystal::scrollDisplayRight(void) { command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT); }
void LiquidCrystal::leftToRight(void) { _displaymode |= LCD_ENTRYLEFT; command(LCD_ENTRYMODESET | _displaymode); }
void LiquidCrystal::rightToLeft(void) { _displaymode &= ~LCD_ENTRYLEFT; command(LCD_ENTRYMODESET | _displaymode); }
void LiquidCrystal::autoscroll(void) { _displaymode |= LCD_ENTRYSHIFTINCREMENT; command(LCD_ENTRYMODESET | _displaymode); }
void LiquidCrystal::noAutoscroll(void) { _displaymode &= ~LCD_ENTRYSHIFTINCREMENT; command(LCD_ENTRYMODESET | _displaymode); }

void LiquidCrystal::createChar(uint8_t location, uint8_t charmap[]) {
  location &= 0x7;
  command(LCD_SETCGRAMADDR | (location << 3));
  for (int i=0; i<8; i++) { write(charmap[i]); }
}

inline void LiquidCrystal::command(uint8_t value) { send(value, LOW); }
inline size_t LiquidCrystal::write(uint8_t value) {
  send(value, HIGH);
  _current_col++;
  return 1;
}

void LiquidCrystal::send(uint8_t value, uint8_t mode) {
  if (_isI2C) {
    uint8_t highnib = value & 0xf0;
    uint8_t lownib = (value << 4) & 0xf0;
    write4bitsI2C(highnib | mode);
    write4bitsI2C(lownib | mode);
  } else {
    digitalWrite(_rs_pin, mode);
    if (_rw_pin != 255) digitalWrite(_rw_pin, LOW);
    if (_displayfunction & LCD_8BITMODE) { write8bits(value); }
    else { write4bits(value>>4); write4bits(value); }
  }
}

void LiquidCrystal::pulseEnable(void) {
  digitalWrite(_enable_pin, LOW); delayMicroseconds(1);
  digitalWrite(_enable_pin, HIGH); delayMicroseconds(1);
  digitalWrite(_enable_pin, LOW); delayMicroseconds(100);
}

void LiquidCrystal::write4bits(uint8_t value) {
  for (int i = 0; i < 4; i++) { digitalWrite(_data_pins[i], (value >> i) & 0x01); }
  pulseEnable();
}

void LiquidCrystal::write8bits(uint8_t value) {
  for (int i = 0; i < 8; i++) { digitalWrite(_data_pins[i], (value >> i) & 0x01); }
  pulseEnable();
}

void LiquidCrystal::i2cTransmit(uint8_t value) {
  Wire.beginTransmission(_LcdAddr);
  Wire.write((int)(value | _backlightval));
  Wire.endTransmission();
}

void LiquidCrystal::write4bitsI2C(uint8_t value) {
  i2cTransmit(value);
  i2cTransmit(value | En);
  delayMicroseconds(1);
  i2cTransmit(value & ~En);
  delayMicroseconds(50);
}

void LiquidCrystal::backlight() {
  if (_isI2C) {
    _backlightval = LCD_BACKLIGHT;
    i2cTransmit(0);
  } else if (_backlight_pin != 255) {
    digitalWrite(_backlight_pin, _bl_polarity);
  }
}

void LiquidCrystal::noBacklight() {
  if (_isI2C) {
    _backlightval = LCD_NOBACKLIGHT;
    i2cTransmit(0);
  } else if (_backlight_pin != 255) {
    digitalWrite(_backlight_pin, !_bl_polarity);
  }
}

void LiquidCrystal::setBacklightPin(uint8_t pin, uint8_t polarity) {
  if (!_isI2C) {
    _backlight_pin = pin;
    _bl_polarity = polarity;
    pinMode(_backlight_pin, OUTPUT);
    backlight();
  }
}

void LiquidCrystal::printAt(uint8_t col, uint8_t row, const char* str) {
  setCursor(col, row);
  print(str);
}

void LiquidCrystal::printf(const char* format, ...) {
  char buf[64];
  va_list args;
  va_start(args, format);
  vsnprintf(buf, sizeof(buf), format, args);
  va_end(args);
  print(buf);
}

void LiquidCrystal::printCenter(uint8_t row, const char* str) {
  uint8_t len = strlen(str);
  uint8_t col = (len >= _numcols) ? 0 : (_numcols - len) / 2;
  setCursor(col, row);
  print(str);
}

void LiquidCrystal::printRight(uint8_t row, const char* str) {
  uint8_t len = strlen(str);
  uint8_t col = (len >= _numcols) ? 0 : (_numcols - len);
  setCursor(col, row);
  print(str);
}

void LiquidCrystal::clearLine(uint8_t row) {
  setCursor(0, row);
  for (uint8_t i = 0; i < _numcols; i++) {
    print(" ");
  }
  setCursor(0, row);
}

void LiquidCrystal::saveCursor() {
  _saved_col = _current_col;
  _saved_row = _current_row;
}

void LiquidCrystal::restoreCursor() {
  setCursor(_saved_col, _saved_row);
}

void LiquidCrystal::createCharFromProgmem(uint8_t location, const uint8_t charmap[]) {
  location &= 0x7;
  command(LCD_SETCGRAMADDR | (location << 3));
  for (int i = 0; i < 8; i++) {
    write(pgm_read_byte_near(charmap + i));
  }
}

void LiquidCrystal::scrollLineLeft(uint8_t row) {
  saveCursor();
  setCursor(0, row);
  scrollDisplayLeft();
  restoreCursor();
}

void LiquidCrystal::scrollLineRight(uint8_t row) {
  saveCursor();
  setCursor(0, row);
  scrollDisplayRight();
  restoreCursor();
}

void LiquidCrystal::startAsyncScroll(uint8_t row, uint32_t interval) {
  _scroll_row = row;
  _scroll_interval = interval;
  _last_scroll_time = millis();
}

void LiquidCrystal::updateAsyncScroll() {
  if (_scroll_interval == 0) return;
  if (millis() - _last_scroll_time >= _scroll_interval) {
    scrollDisplayLeft();
    _last_scroll_time = millis();
  }
}

void LiquidCrystal::stopAsyncScroll() {
  _scroll_interval = 0;
}

void LiquidCrystal::typewrite(const char* str, uint16_t delay_ms) {
  _typewrite_last_time = millis();
  while (*str) {
    if (millis() - _typewrite_last_time >= delay_ms) {
      write(*str++);
      _typewrite_last_time = millis();
    }
  }
}

void LiquidCrystal::progressHorizontal(uint8_t row, uint8_t percentage) {
  if (percentage > 100) percentage = 100;
  uint8_t total_bars = (_numcols > 5) ? _numcols - 2 : _numcols;
  uint8_t filled_bars = (percentage * total_bars) / 100;

  setCursor(0, row);
  print("[");
  for (uint8_t i = 0; i < total_bars; i++) {
    if (i < filled_bars) write(0xFF);
    else print(" ");
  }
  print("]");
}
