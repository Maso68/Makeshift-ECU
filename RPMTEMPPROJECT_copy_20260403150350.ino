/* 
benjamin lust
rpm/temp Project
*/

// oled libraries
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// temp sensor libraries
#include <OneWire.h>
#include <DallasTemperature.h>

// temp sensor objects and variables 
OneWire TheObject(4);
DallasTemperature sensors(&TheObject);
float reading = 0;

// oled screen object and screen dimensions
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 screen(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// magnet sensor variables and set up
int hallPin = 2; 

// time and rpm variables setup
unsigned long last_time = 0;
int rpm = 0;
volatile int pulsecount = 0;

void setup() {
  Serial.begin(9600);
  
  pinMode(hallPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), pulse_update, FALLING);
  
  // oled setup, screen is the object name
  screen.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  screen.clearDisplay();
  screen.setTextSize(1);
  screen.setTextColor(WHITE);
  
  //sensor start up
  sensors.begin();
}

void pulse_update(){
pulsecount++;
}

void loop() {
  
  // rpm calcs
  if(millis() - last_time >= 1000){
    rpm = (pulsecount * 60);
    pulsecount = 0; 
    last_time = millis();

    Serial.print(reading);
    Serial.print(",");
    Serial.println(rpm);
  }

  // get temp sensor data
  sensors.requestTemperatures();
  reading = sensors.getTempFByIndex(0);
  
  // print data
  screen.setCursor(0, 0);
  screen.setTextSize(1);
  screen.print("Temperature: ");
  
  screen.setCursor(0, 20);
  screen.setTextSize(2);
  if(reading > 80){
    screen.setCursor(0, 30);
    screen.setTextSize(1);
    screen.println("!! TOO HOT !!");
  }
  screen.print(reading);
  
  screen.setCursor(0, 48);
  screen.print("RPM");
  screen.setCursor(40, 48);
  screen.print(rpm);


  screen.display();
  delay(200);
  screen.clearDisplay();
}