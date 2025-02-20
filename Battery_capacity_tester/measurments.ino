int16_t adc0, adc1;
float volts0, volts1;

float getVoltage(bool range5) {
  adc1 = ads.readADC_SingleEnded(1);
  voltage = ads.computeVolts(adc1);
  float voltage_calc = (14000*voltage)/13000;
  Serial.print("Voltage is: ");
  Serial.println(voltage);
  return voltage_calc;  // Return the calculated voltage
}

float getCurrent() {
  adc0 = ads.readADC_SingleEnded(0);
  current = ads.computeVolts(adc0);
  Serial.print("Current is: ");
  Serial.println(current);
  return current*2;  // Return current in Amps (A)
}