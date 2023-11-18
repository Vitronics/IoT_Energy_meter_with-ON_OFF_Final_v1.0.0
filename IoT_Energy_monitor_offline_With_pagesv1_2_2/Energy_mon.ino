void temp1(){
emon1.calcVI(20,2000);                                                                                    // Calculate all. No.of half wavelengths (crossings), time-out
  emon1.serialprint();                                                                                      // Print out all variables (realpower, apparent power, Vrms, Irms, power factor)
  // Calculate energy consumed in kWh
  unsigned long currentMillis = millis();
  kWh += emon1.apparentPower * (currentMillis - lastMillis) / 3600000000.0;
  lastMillis = currentMillis;
  float realPower       = emon1.realPower;                                                                  //extract Real Power into variable
  float apparentPower   = emon1.apparentPower;                                                              //extract Apparent Power into variable
  float powerFActor     = emon1.powerFactor;                                                                //extract Power Factor into Variable
  float supplyVoltage   = emon1.Vrms;                                                                       //extract Vrms into Variable
  float Irms            = emon1.Irms;                                                                       //extract Irms into Variable
                                                                      
  Serial.printf("Vrms: %.2fV\tIrms: %.4fA\tPower: %.4fW\tkWh: %.5fkWh\n",                                    // Print data to Serial for debugging
                emon1.Vrms, emon1.Irms, emon1.apparentPower, kWh);
 //lcd.clear();
  buttonStateUp = digitalRead(buttonUp);
  buttonStateDown = digitalRead(buttonDown);

if(buttonStateDown == LOW){
    currentScreen = currentScreen+1;
    // Serial.println(currentScreen);
    if(currentScreen == 4){
      currentScreen = 0;
    }
        Serial.println(currentScreen);
}

if(buttonStateUp == LOW){
    currentScreen = currentScreen-1;
 

    if(currentScreen < 0){
      currentScreen = 3;
    }
       Serial.println(currentScreen);
}
}