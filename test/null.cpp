#include <ArduinoUnitTests.h>

unittest(equality_as_vars)
{
  int x = 3;
  int y = 3;
  int z = 3;
  assertEqual(x, y);
  assertEqual(x, z);
}

unittest(equality_as_values)
{
  assertEqual(1, 1);
  assertEqual(4, 4);
}

unittest(nothing)
{
}

unittest_main()
