void displayMeasurement(float current, float voltage) 
{
  if (current < 0.01){
    current = 0;
  } 
  if (voltage < 0.03){
    voltage = 0;
  }
  display.clearDisplay();  // Clear the display

  display.setTextSize(2);  // Bigger text for better readability
  display.setTextColor(SSD1306_WHITE);

  // Display Current
  display.setCursor(25, 0);  
  display.print(current, 3); // 4 decimal places
  display.println(F(" A"));

  // Display Voltage
  display.setCursor(25, 17);
  display.print(voltage, 3); // 4 decimal places
  display.println(F(" V"));

  display.display();  // Update OLED display
}
