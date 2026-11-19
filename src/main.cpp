
#include <Arduino.h>
#include <Wire.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
    Serial.begin(9600);

    dht.begin();

    lcd.init();
    lcd.backlight();

    lcd.setCursor(0, 0);
    lcd.print("Temp Monitor");
    lcd.setCursor(0, 1);
    lcd.print("Starting...");

    delay(2000);
    lcd.clear();
}

void loop() {
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    if (isnan(temperature) || isnan(humidity)) {
        Serial.println("Sensor Error!");

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Sensor Error!");
    } else {
        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.println(" C");

        Serial.print("Humidity: ");
        Serial.print(humidity);
        Serial.println(" %");

        lcd.clear();

        lcd.setCursor(0, 0);
        lcd.print("Temp: ");
        lcd.print(temperature, 1);
        lcd.print(" C");

        lcd.setCursor(0, 1);
        lcd.print("Humidity: ");
        lcd.print(humidity, 0);
        lcd.print("%");
    }

    delay(2000);
}
