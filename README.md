# smart_forest

## **Installation**

Pour pouvoir faire fonctionner les script de notre prototype il faut 2 librairies : 
* Liquid Crystal
* DHT

Composants de notre prototype : 
* Ecran LCD 1602
* Une RGB Led
* Elegoo Uno R3
* DHT22
* 5 résistances (4 * 220Ω, 2kΩ )
* BreadBoard
* 1 câble USB
  
## **Schema de notre prototype**

![Infra protoype](https://github.com/quentin-beaufort/smart_forest/blob/main/Schema_Prototype.png)

Infra de notre protype sur **tinkecard**, mais sans des éléments introuvable dessus comme le DHT remplacé par un capteur d'humidité dans le sol.

**Vidéo de notre prototype**
[Prototype Test](https://github.com/quentin-beaufort/smart_forest/blob/main/VID_20250213_145719.mp4)
_Il faut la télécharger car la vidéo est trop lourde_

**Photo de notre prototype**
![Prototype](https://github.com/quentin-beaufort/smart_forest/blob/main/Prototype_IOT.jpeg)
## **Extrait de code**

### Code pour notre prototype avec un DHT22 et Led
[Script](https://github.com/quentin-beaufort/smart_forest/blob/main/main.ino)

### Code pour notre premier prototype avec un capteur DHT11 

``` cpp
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
  lcd.print("H/T:");
}

void loop() {
  // Read humidity
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  
  // Check if reading was successful
  if (isnan(humidity)) {
    lcd.setCursor(0, 1);
    lcd.print("Error reading!");
    delay(2000);
    return;
  }
  if (isnan(temperature)){
    temperature = 0;
  }
  
  // Display humidity on second line
  lcd.setCursor(0, 1);
  lcd.print(humidity, 1);  // Display with 1 decimal place
  lcd.print("% / ");  // Add % symbol and spaces to clear any previous characters
  lcd.print(temperature, 1);
  lcd.print(" C");
  
  // Wait 2 seconds before next reading
  delay(2000);
}
```


