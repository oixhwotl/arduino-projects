#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define USE_ULTRASONIC_SENSOR 0
#define PIN_TRIGGER 7
#define PIN_ECHO  8

#define USE_CDS 1
#define PIN_CDS A0

#define USE_SERIAL 1

LiquidCrystal_I2C lcd(0x27, 16, 2); // 0x3F

void setup() {
  #if USE_SERIAL
  Serial.begin(9600);
  Serial.println("\nUltrasonic Sensor and LCD Test");
  #endif

  #if USE_ULTRASONIC_SENSOR
  pinMode(PIN_TRIGGER, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  #endif

  #if USE_CDS
  pinMode(PIN_CDS, INPUT);
  #endif

  lcd.init();
  lcd.backlight();
  lcd.clear();
}


void loop() {
  int cds = analogRead(PIN_CDS);

  String lcdStr = "CDS: " + String(cds) + " ";

  lcd.setCursor(1, 0);
  lcd.print(lcdStr);
  delay(500);
}

double measureDistance(int pin_trigger = PIN_TRIGGER, int pin_echo = PIN_ECHO) {
  #if USE_ULTRASONIC_SENSOR

  // before triggering
  digitalWrite(pin_trigger, LOW);
  delayMicroseconds(2);

  // triggering
  digitalWrite(pin_trigger, HIGH);
  delayMicroseconds(10);

  // end triggering
  digitalWrite(pin_trigger, LOW);

  // measuring duration from HIGH to LOW
  long duration = pulseIn(pin_echo, HIGH);
  double durationInSeconds = duration / 1000000.0;
  double distanceInCm = duration * (340.0/10000.0/2.0); // speed of sound: 340 m/s -> cm, miliseconds = 10^-6 ==> 10^-4 

  #if USE_SERIAL
  Serial.print("Duration: ");
  Serial.print(duration);
  Serial.print(" mu s (microseconds)");
  Serial.print(", Distance: ");
  Serial.print(distanceInCm);
  Serial.print(" cm ");
  #endif

  return distanceInCm;

  #else // USE_ULTRASONIC_SENSOR
  
  return 0;
  
  #endif // USE_ULTRASONIC_SENSOR
}

void loop_ultrasonic_sensor() {
  lcd.clear();

  double distance = measureDistance();
  String distanceStr = "Dist: " + String(distance) + " cm";

  lcd.setCursor(1, 0);
  lcd.print(distanceStr);
  delay(500);
}


int a = 0;
void loop_counter() {
  
  lcd.clear();

  lcd.setCursor(1, 0);
  lcd.print("Hello");
  lcd.setCursor(1, 1);
  lcd.print(a);
  a++;
  delay(500);
}

void loop_helloworld() {
  // put your main code here, to run repeatedly:

  lcd.clear();

  lcd.setCursor(1, 0);
  lcd.print("Hello, LCD!");
  lcd.setCursor(1, 1);
  lcd.print("1234567890");

  delay(100);

  lcd.clear();

  lcd.setCursor(1, 0);
  lcd.print("Hello, LCD!");

  delay(100);

}
