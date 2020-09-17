#include <bitset>
#include <iostream>
#include <Arduino.h>
#include <ArduinoUnitTests.h>
#include <ci/ObservableDataStream.h>
#include <LiquidCrystal_CI.h>

const byte rs = 1;
const byte rw = 2;
const byte enable = 3;
const byte d0 = 10;
const byte d1 = 11;
const byte d2 = 12;
const byte d3 = 13;
const byte d4 = 14;
const byte d5 = 15;
const byte d6 = 16;
const byte d7 = 17;

GodmodeState* state = GODMODE();
const int logSize = 100;
int pinLog[logSize], logIndex = 0;

class BitCollector : public DataStreamObserver {
  public:
    BitCollector() : DataStreamObserver(false, false) {}
    virtual void onBit(bool aBit) {
      if (aBit && logIndex < logSize) {
        int value = 0;
        value = (value << 1) + state->digitalPin[rs];
        value = (value << 1) + state->digitalPin[rw];
        value = (value << 1) + state->digitalPin[d7];
        value = (value << 1) + state->digitalPin[d6];
        value = (value << 1) + state->digitalPin[d5];
        value = (value << 1) + state->digitalPin[d4];
        value = (value << 1) + state->digitalPin[d3];
        value = (value << 1) + state->digitalPin[d2];
        value = (value << 1) + state->digitalPin[d1];
        value = (value << 1) + state->digitalPin[d0];
        pinLog[logIndex++] = value;
        // std::bitset<16> bits(value);
        // std::cout << value << " : " << bits << std::endl;
      }
    }

    virtual String observerName() const { return "BitCollector"; }
};

unittest(className) {
  LiquidCrystal_Test lcd(rs, enable, d4, d5, d6, d7);
  std::cout << "TESTING: " << lcd.className() << std::endl;
}

unittest(constructors)
{
  LiquidCrystal_Test lcd1(rs, enable, d4, d5, d6, d7);
  LiquidCrystal_Test lcd2(rs, rw, enable, d4, d5, d6, d7);
  LiquidCrystal_Test lcd3(rs, enable, d0, d1, d2, d3, d4, d5, d6, d7);
  LiquidCrystal_Test lcd4(rs, rw, enable, d0, d1, d2, d3, d4, d5, d6, d7);
  LiquidCrystal_Test* lcd5 = new LiquidCrystal_Test(rs, enable, d4, d5, d6, d7);
  LiquidCrystal_Test* lcd6 = new LiquidCrystal_Test(rs, rw, enable, d4, d5, d6, d7);
  LiquidCrystal_Test* lcd7 = new LiquidCrystal_Test(rs, enable, d0, d1, d2, d3, d4, d5, d6, d7);
  LiquidCrystal_Test* lcd8 = new LiquidCrystal_Test(rs, rw, enable, d0, d1, d2, d3, d4, d5, d6, d7);
  assertNotNull(lcd5);
  assertNotNull(lcd6);
  assertNotNull(lcd7);
  assertNotNull(lcd8);
}

unittest(init)
{
  state->reset();
  BitCollector enableBits;
  logIndex = 0;
  state->digitalPin[enable].addObserver("lcd", &enableBits);
  LiquidCrystal_Test lcd(rs, enable, d4, d5, d6, d7);
  state->digitalPin[enable].removeObserver("lcd");
  /*     rs rw  d7 to d0
     48 : 0  0  00110000      set to 8-bit mode (takes three tries)
     48 : 0  0  00110000      set to 8-bit mode
     48 : 0  0  00110000      set to 8-bit mode
     32 : 0  0  00100000      set to 4-bit mode, 1 line, 8-bit font
     32 : 0  0  0010          \
      0 : 0  0      0000       set to 4-bit mode, 1 line, 8-bit font
      0 : 0  0  0000          \
    192 : 0  0      1100       display on, cursor off, blink off
      0 : 0  0  0000          \
    016 : 0  0      0001       clear display
      0 : 0  0  0000          \
     96 : 0  0      0110       increment cursor position, no display shift
   */
  int expected[12] = {48, 48, 48, 32, 32, 0, 0, 192, 0, 16, 0, 96};
  assertEqual(12, logIndex);
  for (int i = 0; i < logIndex; ++i) {
    assertEqual(expected[i], pinLog[i]);
  }
}

unittest(begin_16_02)
{
  state->reset();
  BitCollector enableBits;
  logIndex = 0;
  LiquidCrystal_Test lcd(rs, enable, d4, d5, d6, d7);
  state->digitalPin[enable].addObserver("lcd", &enableBits);
  lcd.begin(16, 2);
  state->digitalPin[enable].removeObserver("lcd");
  /*     rs rw  d7 to d0
     48 : 0  0  00110000      set to 8-bit mode (takes three tries)
     48 : 0  0  00110000      set to 8-bit mode
     48 : 0  0  00110000      set to 8-bit mode
     32 : 0  0  00100000      set to 4-bit mode, 1 line, 8-bit font
     32 : 0  0  0010          \
    128 : 0  0      1000       set to 4-bit mode, 2 lines, 8-bit font
      0 : 0  0  0000          \
    192 : 0  0      1100       display on, cursor off, blink off
      0 : 0  0  0000          \
    016 : 0  0      0001       clear display
      0 : 0  0  0000          \
     96 : 0  0      0110       increment cursor position, no display shift
   */
  int expected[12] = {48, 48, 48, 32, 32, 128, 0, 192, 0, 16, 0, 96};
  assertEqual(12, logIndex);
  for (int i = 0; i < logIndex; ++i) {
    assertEqual(expected[i], pinLog[i]);
  }
}
