#include <LiquidCrystal.h>
#include <DHT.h>

// Define DHT pin and type
#define DHTPIN 8
#define DHTTYPE DHT11

// Initialize LCD (pins: RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Set up the LCD's number of columns and rows
  lcd.begin(16, 2);
  
  // Initialize DHT sensor
  dht.begin();
  
  // Print static text
  lcd.print("Humidity:");
}

void loop() {
  // Read humidity
  float humidity = dht.readHumidity();
  
  // Check if reading was successful
  if (isnan(humidity)) {
    lcd.setCursor(0, 1);
    lcd.print("Error reading!");
    delay(2000);
    return;
  }
  
  // Display humidity on second line
  lcd.setCursor(0, 1);
  lcd.print(humidity, 1);  // Display with 1 decimal place
  lcd.print("%   ");  // Add % symbol and spaces to clear any previous characters
  
  // Wait 2 seconds before next reading
  delay(2000);
}