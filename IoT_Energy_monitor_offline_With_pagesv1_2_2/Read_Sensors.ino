//-------------------------------------------------------------------------read analog voltages and current from sensors---------------------------------------------------------//
int read_adc(int adc_parameter)
{
  
  int sum = 0;
  int sample ;
  for (int i=0; i<AVG_NUM; i++) 
  {                                                                                                     // loop through reading raw adc values AVG_NUM number of times  
    sample = analogRead(adc_parameter);                                                                 // read the input pin  
    sum += sample;                                                                                      // store sum for averaging
    delayMicroseconds(10);                                                                              // pauses for 50 microseconds  
  }
  return (sum);                                                                                 // divide sum by AVG_NUM to get average and return it
}
//-------------------------------------------------------------------------------------------------------------
////////////////////////////////////////READ THE DATA//////////////////////////////////////////////////////////////
//-------------------------------------------------------------------------------------------------------------
 void read_data(void)                                                                                   //5V = ADC value 1024 => 1 ADC value = (5/1024)Volt= 0.0048828Volt
 {                                                                                                      // Vout=Vin*R2/(R1+R2) => Vin = Vout*(R1+R2)/R2   R1=100 and R2=20
     solar_volt = read_adc(26)*(120/10)*0.000610;//*(120/20);
     solar_watts   = read_adc(27)*0.00488;
     load_current = ((read_adc(5)*0.0048828 - offsetVoltage-2.5)/Sensitivity );            // 2.4V offset when no load is connected
     solar_current = ((read_adc(19)*0.0048828 - offsetVoltage)/ Sensitivity ); 
      if (load_current <0)
     {
      load_current = 0;
     }
     if (solar_current <0)
     {
      solar_current = 0;
     }
    
    /*int sensorValue = analogRead(2);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float solar_volt = (sensorValue *3.3) / 4096.0;

  //float solar_volt = vol * 3.3;


  // Measure The Current ***********************************
  adcvalue = analogRead(2 );//reading the value from the analog pin A0
  solar_volt = (adcvalue / 4096.0) * 3300; // Gets you mV 
  solar_current = ((solar_volt - offsetvoltage) / sensitivity);  
   bat_volt =  analogRead((4)/4096.0)*3300; */
  }