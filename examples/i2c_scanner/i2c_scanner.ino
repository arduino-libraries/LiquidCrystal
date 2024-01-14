//----------------------------------------------------------------------------
// I2C_Scanner for Arduino
//
// This sketch scans valid i2c 7-bit addresses
// This does not scan for devices using 10-bit addresses
//
//----------------------------------------------------------------------------
// Version 1
//    This program (or code that looks like it)
//    can be found in many places.
//    For example on the Arduino.cc forum.
//    The original author is not know.
//
// Version 2, Juni 2012, Using Arduino 1.0.1
//     Adapted to be as simple as possible by Arduino.cc user Krodal
//
// Version 3, Feb 26  2013
//    V3 by louarnold
//
// Version 4, March 3, 2013, Using Arduino 1.0.3
//    by Arduino.cc user Krodal.
//    Changes by louarnold removed.
//    Scanning addresses changed from 0...127 to 1...119,
//    according to the i2c scanner by Nick Gammon
//    http://www.gammon.com.au/forum/?id=10896
//
// Version 5, March 28, 2013
//    As version 4, but address scans now to 127.
//    A sensor seems to use address 120.
//
// Version 6, May 21, 2013
//    by Martin Falatic http://www.falatic.com/
//    Works with Arduino 1.0.x and 1.5.x IDEs
//    Behaves more like Linux i2cdetect
//    Valid address range is 0x03 to 0x77 per specs, including:
//        http://www.nxp.com/documents/user_manual/UM10204.pdf
//    Notes on reserved addresses outside this range:
//        0x78-0x7B = 10-bit slave address
//        0x7C-0x7F = device ID
//        0x02-0x03 = reserved for future use, but
//            i2cdetect will still scan 0x03
//
//----------------------------------------------------------------------------
//
// An example of i2cdetect output for reference
//   (blank) = not scanned
//   UU      = system device (if applicable to the platform)
//   nn      = device found at this address
//
//        0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f
//   00:          -- -- -- -- -- -- -- -- -- -- -- -- --
//   10: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
//   20: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
//   30: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
//   40: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
//   50: -- -- 52 -- -- -- -- -- -- -- -- -- -- -- -- --
//   60: -- -- -- -- -- -- -- -- UU -- -- -- -- -- -- --
//   70: -- -- -- -- -- -- -- --
//
//----------------------------------------------------------------------------

#include <Wire.h>

#define VERSION           "6.0"

#define MODE_WRITE_QUICK   true // Takes precedence over read-byte mode
#define MODE_READ_BYTE    false
#define SERIAL_BAUD_RATE   9600
#define REPEAT_DELAY       5000 // milliseconds

// By default use write-quick mode, but for these use read-byte mode
#define SCAN_ADDRESS_START       0x03
#define SCAN_ADDRESS_END         0x77

#define I2C_RANGE_START          0x00
#define I2C_RANGE_END            0x7F
#define READ_HINT_RANGE_1_START  0x30
#define READ_HINT_RANGE_1_END    0x37
#define READ_HINT_RANGE_2_START  0x50
#define READ_HINT_RANGE_2_END    0x5f

uint8_t deviceStatus[128]; // global

void setup()
{
  Serial.begin(SERIAL_BAUD_RATE);

  Serial.println();
  Serial.print("Arduino I2C Bus Scanner v");
  Serial.println(VERSION);

  if (MODE_READ_BYTE || !MODE_WRITE_QUICK) {
    Serial.println();
    Serial.println("Note: Read-byte mode on Arduino may block indefinitely");
    Serial.println("      if a device is not capable of that mode.");
  }

  Wire.begin();
}

void loop()
{
  Serial.println();
  Serial.println("Scanning: ");

  for(uint8_t addr = SCAN_ADDRESS_START; addr <= SCAN_ADDRESS_END; addr++ ) 
  {
    // Address the device
    Wire.beginTransmission(addr);
    
    // Read-byte mode: Request one byte from the device
    if (!MODE_WRITE_QUICK) {
      if ((MODE_READ_BYTE) || 
          (addr >= READ_HINT_RANGE_1_START && addr <= READ_HINT_RANGE_1_END) ||
          (addr >= READ_HINT_RANGE_2_START && addr <= READ_HINT_RANGE_2_END))
      {
        uint8_t throwaway = Wire.requestFrom(addr, (uint8_t)1);
      }
    }

    // Check for ACK (detection of device), NACK or error
    deviceStatus[addr] = Wire.endTransmission();

    Serial.print(".");
  }
  Serial.println();

  displayResults();

  Serial.println();
  Serial.print("Pausing for ");
  Serial.print(REPEAT_DELAY/1000.0, 2);
  Serial.println(" seconds");

  delay(REPEAT_DELAY); // Pause between scans
}

void displayResults()
{
  char textbuffer[128];
  char tmpstr[128];

  Serial.println();

  strcpy(textbuffer, "   ");

  for (int i = 0; i < 0x10; i++)
  {
    sprintf(tmpstr, " %2x", i);
    strcat(textbuffer, tmpstr);
  }

  Serial.println(textbuffer);

  textbuffer[0] = 0; // Clear the buffer

  // Aligning display output to 16 byte intervals via integer math
  for(uint8_t addr = (I2C_RANGE_START) / 0x10 * 0x10;
      addr < (I2C_RANGE_END+1) / 0x10 * 0x10;
      addr++)
  {
    if (!(addr % 0x10)) // Start of a line
    {
      sprintf(textbuffer, "%02x:", addr / 0x10);
    }

    if (addr < SCAN_ADDRESS_START || addr > SCAN_ADDRESS_END)
    {
      sprintf(tmpstr, " %02s", "  ");
    }
    else if (deviceStatus[addr] == 0)
    {
      sprintf(tmpstr, " %02x", addr);
    }
    else if (deviceStatus[addr] == 4)
    {
      sprintf(tmpstr, " %02s", "??");
    }
    else
    {
      sprintf(tmpstr, " %02s", "--");
    }

    strcat(textbuffer, tmpstr);

    if (!((addr+1) % 0x10) && textbuffer[0] != 0)
    {
      Serial.println(textbuffer);
      textbuffer[0] = 0;
    }
  } 
}

