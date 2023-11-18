

#include <ACS712.h>
#include "EmonLib.h"                                                                                      // Include Emon Library
EnergyMonitor emon1;                                                                                      // Create an instance
#include <LiquidCrystal_I2C.h>

//-----------------------------------------------Pins---------------------------------------------------------------------------//
#define SOL_ADC 2                                                                                        // Solar panel side voltage divider is connected to pin 2 
#define BAT_ADC 4                                                                                        // Battery side voltage divider is connected to pin 4
#define LOAD_CURRENT_ADC 5                                                                               // ACS 712 current sensor is connected to pin 19 for load curremt
#define SOL_CURRENT_ADC 19                                                                               // ACS 712 current sensor is connected to pin 21 for solar current
#define AVG_NUM 2                                                                                       // number of iterations of the adc routine to average the adc readings

LiquidCrystal_I2C lcd(0x27, 20, 4);         
const int buttonUp = 15;
const int buttonDown = 18;                                                                                           //Down button
//const int buttonOk = 27;
int buttonStateOk = 0;
int buttonStateUp = 0;
int buttonStateDown = 0;
int currentScreen = 0;
int currentMenu = 0;                                                      
float kWh = 0.0;                                                                                          // Variables for energy calculation
unsigned long lastMillis = millis();                                                                                 
unsigned long previousMillis = 0;                                                                         //Variables for autorreturn
unsigned long interval = 100;                                                                             //Desired wait time
//long panelVolts = 0;          // Solar panel Voltage (deci Volts)
//long batteryVolts = 120;      // Battery Voltage (deci Volts)
float solar_volt=0;
float bat_volt=0;
float load_current=0;
float solar_current=0;
float offsetVoltage = 2.5;                                                                                // for ACS712 sensor
float Sensitivity =0.66;                                                                                  // 185mV/A for ACS712-5A variant,66mV/A for 30A
float last_time = 0;
float current_time = 0;
long unsigned msec=0;
long unsigned last_msec=0;
long unsigned elasped_msec=0;
long unsigned elasped_time=0;
float load_ampSecs = 0;
float load_ampHours=0;
float load_watts=0;
float load_wattSecs = 0;
float load_wattHours=0;
float solar_ampSecs = 0;
float solar_ampHours=0;
float solar_watts=0;
float solar_wattSecs = 0;
float solar_wattHours=0;



/*int sensitivity = 185; // use 100 for 20A Module and 66 for 30A Module 
int adcvalue= 0; 
int offsetvoltage = 2500;  //Sensor Callibration
double solar_volt = 0; //voltage measuring 
double solar_current = 0;// Current measuring 
*/
void setup()
{  
  Serial.begin(9600);
   emon1.voltage(34, 137.5, 1.7);  // Voltage: input pin, calibration, phase_shift
  emon1.current(35, 1.1);       // Current: input pin, calibration.                                                                               
  lcd.init();
  lcd.backlight();
  pinMode(buttonUp, INPUT_PULLUP);
  pinMode(buttonDown, INPUT_PULLUP);
  delay(10);
  lcd.setCursor(0, 0);
  lcd.print("   IoT METER "); 
  lcd.setCursor(0, 1 );
  lcd.print("   INITIALISE ");
  lcd.setCursor(0, 2 );
  lcd.print("   SUCCESS!!! ");
    lcd.setCursor(0, 3 );
  lcd.print("By  Vitronics Tech ");
  delay(3000);
  lcd.clear();
}

void loop()
{
  read_data();                                                                                            // read different sensors data from analog pin of esp32
  printScreen();
  temp1();
  delay(100);
}
        
  

