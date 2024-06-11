#include "DHT.h"
#include <LiquidCrystal_I2C.h>

#define DHTPIN 3     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C mylcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));

  lcd_test_setup();
  lcd_test();

  mylcd.init();
  mylcd.backlight();
  mylcd.clear();

  dht.begin();
}

void loop() {

  // Wait a few seconds between measurements.
  delay(2000);

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  float hic = dht.computeHeatIndex(t, h, false);

  String tempStr = "Temp: " + String(t) + " 'C"; //" °C";
  String humiStr = "Humi: " + String(h) + " %";
  String hicStr = "HI: " + String(hic) + " °C";
  Serial.print(tempStr);
  Serial.print("  ");
  Serial.print(humiStr);
  Serial.print("  ");
  Serial.println(hicStr);

  mylcd.clear();
  mylcd.setCursor(0, 0);
  mylcd.print(tempStr);
  mylcd.setCursor(0, 1);
  mylcd.print(humiStr);
}