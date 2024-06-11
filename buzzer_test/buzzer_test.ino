#define PIN_PBUZZER 8
#define PIN_ABUZZER 11

#include "pitches.h"

#define USE_SERIAL 1

// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

void setup() {
  #if USE_SERIAL
  Serial.begin(9600);
  #endif

  pinMode(PIN_PBUZZER, OUTPUT);
  pinMode(PIN_ABUZZER, OUTPUT);
}

void setToneDuration(int note, int durations, int pin_buzzer = PIN_PBUZZER) {
  #if USE_SERIAL
  Serial.print("freq:");
  Serial.print(note);
  Serial.print(", durations:");
  Serial.println(durations);
  #endif

  int noteDuration = 1000 / duration;

  if (note > 0) {
    tone(pin_buzzer, note, delay_msec);
    delay(delay_msec * 1.3);
  } else {
    noTone(pin_buzzer);
  }
}

void loop() {
  /*
  int melody[7][2] = { // 7x2
     {392, 500},
    {330, 1000},
    {330, 1000},
    {349, 500},
    {294, 1000},
    {294, 1000},
    {0, 10},
  };

  for (int i = 0; i < 7; i++) {
    setTD(melody[i][0], melody[i][1]);
  }
  */
}
