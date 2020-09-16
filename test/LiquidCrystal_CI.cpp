
#define LiquidCrystal_Test LiquidCrystal
#include "LiquidCrystalTest.cpp"

unittest(getRows)
{
    LiquidCrystal_Test lcd(rs, enable, d4, d5, d6, d7);
    assertEqual(1, lcd.getRows());
    lcd.begin(16, 2);
    assertEqual(2, lcd.getRows());
}

unittest_main()
