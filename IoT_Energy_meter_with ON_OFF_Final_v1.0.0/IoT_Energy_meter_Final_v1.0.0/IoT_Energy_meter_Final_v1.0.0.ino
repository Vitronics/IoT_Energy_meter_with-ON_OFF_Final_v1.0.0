
// Blynk and WiFi credentials
const char auth[] = "MYdsKEbxuY68mPuTH3sByCSQgSmNVVU8";

const char ssid[] = "Redmi";
const char pass[] = "27414152";
#define BLYNK_TEMPLATE_ID "TMPL2DxyP7Gwf"
#define BLYNK_TEMPLATE_NAME "IoT Energy Meter"
#define BLYNK_PRINT Serial

#include "EmonLib.h"
#include <EEPROM.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

// Constants for calibration
const float vCalibration = 41.5;
const float currCalibration = 0.15;
// Set your LED and physical button pins here
const int ledPin = 13;
const int btnPin = 12;


// EnergyMonitor instance
EnergyMonitor emon;
 
// Timer for regular updates
BlynkTimer timer;
 void checkPhysicalButton();

int ledState = LOW;
int btnState = HIGH;

// Every time we connect to the cloud...
BLYNK_CONNECTED() {
  // Request the latest state from the server
  Blynk.syncVirtual(V5);

  // Alternatively, you could override server state using:
  //Blynk.virtualWrite(V2, ledState);
}

// When App button is pushed - switch the state
BLYNK_WRITE(V5) {
  ledState = param.asInt();
  digitalWrite(ledPin, ledState);
}

void checkPhysicalButton()
{
  if (digitalRead(btnPin) == LOW) {
    // btnState is used to avoid sequential toggles
    if (btnState != LOW) {

      // Toggle LED state
      ledState = !ledState;
      digitalWrite(ledPin, ledState);

      // Update Button Widget
      Blynk.virtualWrite(V5, ledState);
    }
    btnState = LOW;
  } else {
    btnState = HIGH;
  }
}
// Variables for energy calculation
float kWh = 0.0;
unsigned long lastMillis = millis();
 
// EEPROM addresses for each variable
const int addrVrms = 0;
const int addrIrms = 4;
const int addrPower = 8;
const int addrKWh = 12;
 
// Function prototypes
void sendEnergyDataToBlynk();
void readEnergyDataFromEEPROM();
void saveEnergyDataToEEPROM();
 
 
void setup()
{
  Serial.begin(115200);

 
  // Initialize the LCD
  lcd.init();
  lcd.backlight();
   Blynk.begin(auth, ssid, pass);
 lcd.print("IoT Meter INITIALISED");
 delay(2000);
 lcd.clear();
pinMode(ledPin, OUTPUT);
  pinMode(btnPin, INPUT_PULLUP);
  digitalWrite(ledPin, ledState);
  // Initialize EEPROM with the size of the data to be stored
  EEPROM.begin(32); // Allocate 32 bytes for float values (4 bytes each) and some extra space
 
  // Read the stored energy data from EEPROM
  readEnergyDataFromEEPROM();
 
  // Setup voltage and current inputs
  emon.voltage(35, vCalibration, 1.7); // Voltage: input pin, calibration, phase_shift
  emon.current(34, currCalibration);    // Current: input pin, calibration
 
  // Setup a timer for sending data every 5 seconds
  timer.setInterval(5000L, sendEnergyDataToBlynk);
 timer.setInterval(100L, checkPhysicalButton);
  // A small delay for system to stabilize
  delay(1000);
}
 
 
void loop()
{
  Blynk.run();
  timer.run();
}
 
 
void sendEnergyDataToBlynk()
{
  emon.calcVI(20, 2000); // Calculate all. No.of half wavelengths (crossings), time-out
 
  // Calculate energy consumed in kWh
  unsigned long currentMillis = millis();
  kWh += emon.apparentPower * (currentMillis - lastMillis) / 3600000000.0;
  lastMillis = currentMillis;
 
  // Print data to Serial for debugging
  Serial.printf("Vrms: %.2fV\tIrms: %.4fA\tPower: %.4fW\tkWh: %.5fkWh\n",
                emon.Vrms, emon.Irms, emon.apparentPower, kWh);
 
  // Save the latest values to EEPROM
  saveEnergyDataToEEPROM();
 
  // Send data to Blynk
  Blynk.virtualWrite(V0, emon.Vrms);
  Blynk.virtualWrite(V1, emon.Irms);
  Blynk.virtualWrite(V2, emon.apparentPower);
  Blynk.virtualWrite(V3, kWh);
 
  // Update the LCD with the new values
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Vrms: ");
  lcd.print(emon.Vrms, 2);
  lcd.print(" V");
 
  lcd.setCursor(0, 1);
  lcd.print("Irms: ");
  lcd.print(emon.Irms, 4);
  lcd.print(" A");
 
  lcd.setCursor(0, 2);
  lcd.print("Power: ");
  lcd.print(emon.apparentPower, 4);
  lcd.print(" W");
 
  lcd.setCursor(0, 3);
  lcd.print("kWh: ");
  lcd.print(kWh, 5);
  lcd.print(" kWh");
}
 
 
void readEnergyDataFromEEPROM()
{
  // Read the stored kWh value from EEPROM
  EEPROM.get(addrKWh, kWh);
 
  // Check if the read value is a valid float. If not, initialize it to zero
  if (isnan(kWh))
  {
    kWh = 0.0;
    saveEnergyDataToEEPROM(); // Save initialized value to EEPROM
  }
}

void saveEnergyDataToEEPROM()
{
  // Write the current kWh value to EEPROM
  EEPROM.put(addrKWh, kWh);
 
  // Commit changes to EEPROM
  EEPROM.commit();
}

