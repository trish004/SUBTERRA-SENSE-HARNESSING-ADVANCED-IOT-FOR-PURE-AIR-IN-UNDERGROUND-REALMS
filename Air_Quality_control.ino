#include "arduino_secrets.h"

#include <DHT.h>
#include <LiquidCrystal.h>   

// Initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Define DHT sensor type and pin
#define DHTPIN 7          // Pin connected to DHT11
#define DHTTYPE DHT11     // DHT11 sensor type

// Define pins for LEDs and Buzzer
#define GREEN_LED 8       // Green LED for good air quality
#define YELLOW_LED 9      // Yellow LED for temperature/humidity status
#define RED_LED 10        // Red LED for bad air quality
#define BUZZER 11         // Buzzer for alarm

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);

// Air quality sensor pin
int airQualityPin = A0;

void setup() {
  // Initialize LCD, DHT, and pins
  lcd.begin(16, 2);
  dht.begin();

  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  // Display initial message
  lcd.print("Air Quality Mon");
  delay(1000);
  lcd.clear();
}

void loop() {
  // Read air quality value
  int airQuality = analogRead(airQualityPin);

  // Read temperature and humidity from DHT11
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Display temperature and humidity on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print(" C");

  lcd.setCursor(0, 1);
  lcd.print("Hum: ");
  lcd.print(humidity);
  lcd.print(" %");

  delay(1000);

  // Control LEDs and buzzer based on air quality
  if (airQuality < 200) {
    // Good air quality
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);
    digitalWrite(BUZZER, LOW); // Buzzer off
  } else {
    // Poor air quality
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);
    digitalWrite(BUZZER, HIGH); // Buzzer on
  }

  // Control yellow LED for temperature/humidity status
  if ((temperature > 18 && temperature < 30) && (humidity > 30 && humidity < 60)) {
    // Good temperature and humidity
    digitalWrite(YELLOW_LED, HIGH);  // Steady yellow LED
  } else {
    // Bad temperature or humidity
    digitalWrite(YELLOW_LED, HIGH);
    delay(500);
    digitalWrite(YELLOW_LED, LOW);
    delay(500);  // Blinking yellow LED
    digitalWrite(BUZZER, HIGH); // Buzzer on for warning
  }

  delay(2000); 
}
