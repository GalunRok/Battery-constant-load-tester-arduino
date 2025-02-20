#include <Adafruit_ADS1X15.h>

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

Adafruit_ADS1115 ads;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int lastCLKState;
volatile int encoderValue = 0;

int voltageSens = A0;
int currentSens = A1;
int relayPin = 3;
int timeDischarging = 0; 
float cutOffVoltage = 2.7;
bool btnPressed = false;
unsigned long discharging_last = 0;

int encoderPinA = 6;  // CLK pin
int encoderPinB = 5; // DT pin
int encoderBtn = 13;
int count = 0;
int encoderPinA_prev;
int encoderPinA_value;
boolean bool_CW;
float voltage = 0;
float current = 0;
bool range5 = false;
float average_current = 0;
float sum_current = 0;
int meas_count = 0;
float battery_capacity = 0;


void setup()
{
  Serial.begin(9600);
  pinMode(voltageSens, INPUT);
  pinMode(currentSens, INPUT);
  pinMode(relayPin, OUTPUT);
  pinMode (encoderPinA, INPUT);
  pinMode (encoderPinB, INPUT);
  pinMode(encoderBtn, INPUT_PULLUP);
  encoderPinA_prev = digitalRead(encoderPinA);

  if (!ads.begin()) {
    Serial.println("Failed to initialize ADS.");
    while (1);
  }
 
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) 
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }
  display.display();
  // Clear the buffer
  display.clearDisplay();
  digitalWrite(relayPin, HIGH);
}

int measurmentDelay = 2000;
unsigned long lastMillis = millis();
bool running = false;
bool first = true;
bool measurmentFinished = false;

void loop() 
{
  while(running){
    if(current > 0.01){
      if(millis() - lastMillis > measurmentDelay){
        voltage = getVoltage(range5);
        current = getCurrent();
        sum_current = sum_current + current;
        meas_count++;
        displayMeasurementActive(current, voltage, timeDischarging);
        lastMillis = millis();
      }
      sec_timer();
    }
    else{
      discharging_last = millis();
    }
    if(voltage < cutOffVoltage){
      measurmentFinished = true;
      digitalWrite(relayPin, LOW);
      running = false;
      count = 0;
    }
    checkEncoder();
  }
  if(measurmentFinished){
    if (meas_count != 0){
      average_current = sum_current / meas_count;
    }
    battery_capacity = (average_current * timeDischarging) / 3600;
    Serial.print(battery_capacity);
    displayCapacity(battery_capacity);
  }
  else{
    discharging_last = millis();
    if(millis()- lastMillis > measurmentDelay){
      voltage = getVoltage(range5);
      current = getCurrent();
      displayMeasurement(current, voltage);
      lastMillis = millis();
    }
  }
  checkEncoder();
  if(count == 10){
    running = true;
    timeDischarging = 0;
    count = 0;
  }
}
