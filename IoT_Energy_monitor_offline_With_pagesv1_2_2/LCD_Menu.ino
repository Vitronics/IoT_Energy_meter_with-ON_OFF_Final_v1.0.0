void printScreen() {                                    //START SCREEN ENERGY

   if (currentScreen == 0) {
    lcd.clear();
   lcd.setCursor(0, 0);
  lcd.print("Vrms: ");
  lcd.print(emon1.Vrms, 3);
  lcd.print("   V");
 
  lcd.setCursor(0, 1);
  lcd.print("Irms: ");
  lcd.print(emon1.Irms, 3);
  lcd.print("    A");
 
  lcd.setCursor(0, 2);
  lcd.print("Pwat: ");
  lcd.print(emon1.apparentPower, 3);
  lcd.print("    W");
 
  lcd.setCursor(0, 3);
  lcd.print("kWh : ");
  lcd.print(kWh, 4);
  lcd.print("   kWh");
   }

  if (currentScreen == 1) {                            //SOLAR PARAMETERS
    lcd.clear(); 
       lcd.setCursor(0, 0);
    lcd.print("  SOLAR PARAMETER");
 lcd.setCursor(0, 1);
 lcd.print("SOL Volts ");
 lcd.print(   solar_volt, 1);
 lcd.print("   V");
 lcd.setCursor(0, 2);
  lcd.print("SOL Amps  ");
 lcd.print(   solar_current, 1);
 lcd.print("    A");
 lcd.setCursor(0,3);
  lcd.print("SOL Watts ");
 lcd.print(   bat_volt, 1 );
 lcd.print("    W ");
  }
  if (currentScreen == 2) {                                     //LOAD PARAMETERS
    lcd.clear();
 lcd.setCursor(0, 0);
    lcd.print("  LOAD PARAMETER");
    lcd.setCursor(0,1);
     lcd.print("LOAD Amps  ");
 lcd.print(load_current,1);
 lcd.print("A");
 lcd.setCursor(0,2);
 lcd.print("LOAD Watts ");
 lcd.print(load_watts,1); 
 lcd.print("W");
  } 

 if (currentScreen == 3) {                               ///SOLAR ENERGY PARAMETERS
    lcd.clear();
     lcd.setCursor(0, 0);
    lcd.print("ENERGY PARAMETER");  
    lcd.setCursor(0,1);
    lcd.print("SOL  Wh ");
 lcd.print(solar_wattHours,1);
 lcd.print("Wh");  
 lcd.setCursor(0,2);
   lcd.print("LOAD Wh ");
 lcd.print(load_wattHours,1);
 lcd.print("Wh"); 
 }
}