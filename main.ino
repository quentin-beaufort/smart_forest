#include <LiquidCrystal.h>
#include <DHT.h>

// Define pins
#define DHTPIN 8
#define DHTTYPE DHT22
#define RED_PIN 9
#define GREEN_PIN 10
#define BLUE_PIN 6  // Changed from 11 to 6

// Temperature thresholds
#define TEMP_COLD 22.1
#define TEMP_HOT 25.0

// Initialize LCD (pins: RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Set up the LCD's number of columns and rows
  lcd.begin(16, 2);
  
  // Initialize DHT sensor
  dht.begin();
  
  // Initialize RGB LED pins
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  
  // Print static label
  lcd.print("H/T");
}

// Function to set RGB LED color based on temperature
void setTempColor(float temp) {
  int red, blue, green;
  
  if (temp <= TEMP_COLD) {
    // Full blue
    red = 0;
    blue = 255;
    green = 0;
  } 
  else if (temp >= TEMP_HOT) {
    // Full red
    red = 255;
    blue = 0;
    green = 0;
  }
  else {
    // Progressive transition between blue and red
    float ratio = (temp - TEMP_COLD) / (TEMP_HOT - TEMP_COLD);
    red = ratio * 255;
    blue = (1 - ratio) * 255;
    green = 20;
  }
  
  analogWrite(RED_PIN, red);
  analogWrite(BLUE_PIN, blue);
  analogWrite(GREEN_PIN, green);  // Green always off for pure blue-to-red transition
}

void loop() {
  // Read humidity and temperature
  float humidity = dht.readHumidity() - 9.0;
  float temperature = dht.readTemperature() - 4.5;
  
  // Check if reading was successful
  if (isnan(humidity) || isnan(temperature)) {
    lcd.setCursor(0, 1);
    lcd.print("Error reading!");
    delay(2000);
    return;
  }
  
  // Clear second line
  lcd.setCursor(0, 1);
  lcd.print("                "); // 16 spaces to clear the line
  
  // Display humidity and temperature on second line
  lcd.setCursor(0, 1);
  lcd.print(humidity, 1);
  lcd.print("% / ");
  lcd.print(temperature, 1);
  lcd.print("C");
  
  // Update LED color based on temperature
  setTempColor(temperature);
  
  // Wait 2 seconds before next reading
  delay(2000);
}
