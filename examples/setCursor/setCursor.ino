//Display lcd
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 7, 6, 5, 4);

//Fingerprint
#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
SoftwareSerial serial(2, 3);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&serial);

//Variabili
int fingerId;
String nameId = "";

//Leds
const int l_green = 10, l_red = 9;

void setup() {
  //Debug
  Serial.begin(9600);
  
  //Display
  lcd.begin(16, 2);
  lcd.print("Benvenuto");

  //Fingerprint
  finger.begin(57600);
  if(finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor");
  } else {
    Serial.println("Fingerprint sensor not found :/");
    lcd.clear();
    lcd.print("Error");
    while(1) { delay(1); }
  }

  //Leds
  pinMode(l_green, OUTPUT);
  pinMode(l_red, OUTPUT);
}

//Read fingerprint
int ReadFinger() {
  uint8_t p = finger.getImage();
  if(p != FINGERPRINT_OK) { return -1; }
  p = finger.image2Tz();
  if(p != FINGERPRINT_OK) { return -1; }
  p = finger.fingerFastSearch();
  if(p != FINGERPRINT_OK) { return -2; }
  return finger.fingerID;
}

void onSuccess() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Benvenuto");
  lcd.setCursor(0, 1);
  lcd.print(nameId);
  if(nameId == "Sconosciuto") {
    digitalWrite(l_red, HIGH);
  } else {
    digitalWrite(l_green, HIGH);
  }
  delay(1000);
  digitalWrite(l_red, LOW);
  digitalWrite(l_green, LOW);
}

void loop() {
  fingerId = ReadFinger();
  switch(fingerId) {
    case 1:
      nameId = "Andrea Piergiovanni";
      break;
    case 2:
      nameId = "Matteo Coccia";
      break;
    default:
      nameId = "Sconosciuto";
      break;
  }
  if(fingerId != -1) {
    onSuccess();
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Benvenuto");
  delay(100);
}
