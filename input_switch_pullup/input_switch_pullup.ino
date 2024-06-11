const int PIN_LED1 = 8;
const int PIN_LED2 = 9;
const int PIN_LED3 = 10;
const int PIN_SWITCH1 = 5;
const int PIN_SWITCH2 = 6;
const int PIN_SWITCH3 = 7;

const int PIN_LEDS[3] = {8, 9, 10};
const int PIN_SWITCHES[3] = {5, 6, 7};

void setup() {
  pinMode(PIN_LED1, OUTPUT);
  pinMode(PIN_LED2, OUTPUT);
  pinMode(PIN_LED3, OUTPUT);
  pinMode(PIN_SWITCH1, INPUT_PULLUP);
  pinMode(PIN_SWITCH2, INPUT_PULLUP);
  pinMode(PIN_SWITCH3, INPUT_PULLUP);
  Serial.begin(9600);
}

void digitalWrite3(int leds[], int vals[]) {
  int i = 0;
  for (i = 0; i < 3; i++) {
    digitalWrite(leds[i], vals[i]);
  }
  Serial.print("OUT: ");
  Serial.print(vals[0]);
  Serial.print(',');
  Serial.print(vals[1]);
  Serial.print(',');
  Serial.println(vals[2]);
}

void loop() {
  int read_vals[3] = {LOW, LOW, LOW};
  int output_vals[3] = {LOW, LOW, LOW};
  int i = 0, j = 0;

  j = 0;
  for (j = 0, i = 0; i < 3; i++) {
    read_vals[i] = digitalRead(PIN_SWITCHES[i]);
    j += !(read_vals[i] == HIGH);
  }
  Serial.print("READ: ");
  Serial.print(read_vals[0]);
  Serial.print(',');
  Serial.print(read_vals[1]);
  Serial.print(',');
  Serial.print(read_vals[2]);
  Serial.print('-');
  Serial.println(j);

  if (read_vals[0] == LOW) {
    output_vals[0] = HIGH;
  } else if (read_vals[1] == LOW) {
    output_vals[0] = HIGH;
    output_vals[1] = HIGH;
  } else if (read_vals[2] == LOW) {
    output_vals[0] = HIGH;
    output_vals[1] = HIGH;
    output_vals[2] = HIGH;
  }
  digitalWrite3(PIN_LEDS, output_vals);
  /*
  switch (j) {
    case 3:
      digitalWrite(PIN_LEDS[0], HIGH);
      digitalWrite(PIN_LEDS[1], HIGH);
      digitalWrite(PIN_LEDS[2], HIGH);
      break;
    case 2:
      digitalWrite(PIN_LEDS[0], LOW);
      digitalWrite(PIN_LEDS[1], HIGH);
      digitalWrite(PIN_LEDS[2], HIGH);
      break;
    case 1:
      digitalWrite(PIN_LEDS[0], LOW);
      digitalWrite(PIN_LEDS[1], LOW);
      digitalWrite(PIN_LEDS[2], HIGH);
      break;
    case 0:
    default:
      digitalWrite(PIN_LEDS[0], LOW);
      digitalWrite(PIN_LEDS[1], LOW);
      digitalWrite(PIN_LEDS[2], LOW);
      break;
  }
  */
  /*
  for (i = 0; i < 3; i++) {
    if (vals[i] == LOW) {
      digitalWrite(PIN_LEDS[i], HIGH);
    } else {
      digitalWrite(PIN_LEDS[i], LOW);
    }
  }
  */
}
