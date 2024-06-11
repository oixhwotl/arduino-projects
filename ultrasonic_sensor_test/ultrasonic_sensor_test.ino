#include "pitches.h"

#define PIN_TRIGGER 7
#define PIN_ECHO  8

#define RANGE_MIN 2
#define RANGE_MAX 400

#define PIN_BUZZER 4
#define PIN_LED 3

#define USE_SERIAL 1

void setup() {
  #if USE_SERIAL
  Serial.begin(9600);
  Serial.println("\nUltrasonic Sensor Test");
  #endif

  pinMode(PIN_TRIGGER, OUTPUT);
  pinMode(PIN_ECHO, INPUT);

  pinMode(PIN_BUZZER, OUTPUT);
  pinMode(PIN_LED, OUTPUT);
}

double measure_distance(int pin_trigger = PIN_TRIGGER, int pin_echo = PIN_ECHO) {
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
}

void loop() {
  int tone_delay = 100;
  int loop_delay = tone_delay;

  const int scale[] = {262, 294, 330, 349, 392, 440, 494, 524, 0 };

  double distanceInCm = measure_distance();

  int note_index = (int)(distanceInCm / 7.0); // 2-50, 0-7
  if (note_index > 7) {
    note_index = 8;
  }

  int tone_value = scale[note_index];

  #if USE_SERIAL
  Serial.print(", ToneIndex: ");
  Serial.print(note_index);
  Serial.print(", Tone: ");
  Serial.print(tone_value);
  Serial.println("");
  #endif

  if (tone_value == 0) {
    noTone(PIN_BUZZER);
  } else {
    tone(PIN_BUZZER, tone_value, tone_delay);
  }
  
  delay(loop_delay);
}
