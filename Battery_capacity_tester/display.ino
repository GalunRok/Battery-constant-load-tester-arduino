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

void displayMeasurementActive(float current, float voltage, int time)
{
  display.clearDisplay();  // Clear the display
  display.setTextSize(2);  // Bigger text for better readability
  display.setTextColor(SSD1306_WHITE);
  // Display Current
  display.setCursor(25, 0);  
  display.print(current, 3); // 4 decimal places
  display.println(F(" A"));

  display.setTextSize(1); 
  // Display Voltage
  display.setCursor(15, 17);
  display.print(voltage, 2); // 4 decimal places
  display.print(F(" V"));
  display.setCursor(80, 17);
  display.print(time);
  display.print(F(" s"));

  display.display();  // Update OLED display
}

void displayCount(int count){
  display.clearDisplay();  // Clear the display

  display.setTextSize(2);  // Bigger text for better readability
  // Display text
  display.setCursor(25, 0); 
  display.print(F("Count: "));
  display.print(count);
  
  display.display(); 
}

void displayCapacity(float capacity){
  display.clearDisplay();  // Clear the display

  display.setTextSize(2);  // Bigger text for better readability
  display.setTextColor(SSD1306_WHITE);
  // Display text
  display.setCursor(15, 0); 
  display.println(F("Capacity:"));
  display.setCursor(15, 17);  
  display.print(capacity, 3);
  display.println(F(" Ah"));
  
  display.display(); 
}
