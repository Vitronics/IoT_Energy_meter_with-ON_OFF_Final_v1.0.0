//------------------------------------------------------------------------------------------------------------
/////////////////////////////////POWER AND ENERGY CALCULATION //////////////////////////////////////////////
//------------------------------------------------------------------------------------------------------------
void power(void){
  
msec = millis();
elasped_msec = msec - last_msec;                                                                         //Calculate how long has past since last call of this function
elasped_time = elasped_msec / 1000.0;                                                                    // 1sec=1000 msec
load_watts = load_current * bat_volt;                                                                    //Watts now
solar_watts = solar_current * solar_volt;                                                               //Watts now

load_ampSecs = (load_current*elasped_time);                                                             //AmpSecs since last measurement
solar_ampSecs = (solar_current*elasped_time);                                                           //AmpSecs since last measurement

load_wattSecs = load_ampSecs * bat_volt;                                                                //WattSecs since last measurement
solar_wattSecs = solar_ampSecs * solar_volt;                                                            //WattSecs since last measurement

load_ampHours = load_ampHours + load_ampSecs/3600;                                                      // 1 hour=3600sec //Total ampHours since program started
solar_ampHours = solar_ampHours + solar_ampSecs/3600;                                                   // 1 hour=3600sec //Total ampHours since program started

load_wattHours = load_wattHours + load_wattSecs/3600;                                                   // 1 hour=3600sec //Total wattHours since program started
solar_wattHours = solar_wattHours + solar_wattSecs/3600;                                                // 1 hour=3600sec //Total wattHours since program started

last_msec = msec;                                                                                       //Store 'now' for next time



  
last_time = current_time;
current_time = millis();
load_watts = load_current * bat_volt;                                                                    //load Watts now
solar_watts = solar_current * solar_volt;                                                                //solar Watts now
load_wattHours = load_wattHours +  load_watts*(( current_time -last_time) /3600000.0) ;                  // calculating energy in Watt-Hour
solar_wattHours = solar_wattHours+  solar_watts*(( current_time -last_time) /3600000.0) ;                // calculating energy in Watt-Hour

}