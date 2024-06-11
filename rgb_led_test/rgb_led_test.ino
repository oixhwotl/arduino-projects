const int PIN_RED = 6;
const int PIN_GREEN = 5;
const int PIN_BLUE = 3;

void setup() {
  Serial.begin(9600);
  randomSeed(416);

  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE, OUTPUT);
}

void set_rgb(int red, int green, int blue, int de) {
  // Serial.begin(9600); // in void setup()
  const int SERIAL_OUTPUT = 1;

  analogWrite(PIN_RED, red);
  analogWrite(PIN_GREEN, green);
  analogWrite(PIN_BLUE, blue);

  if (SERIAL_OUTPUT == 1) {
    Serial.print("RGB: (");
    Serial.print(red);
    Serial.print(", ");
    Serial.print(green);
    Serial.print(", ");
    Serial.print(blue);
    Serial.print("), Delay: ");
    Serial.println(de);
  }

  delay(de);
}

void loop() {
  // set_rgb(random(255), random(255), random(255), random(200, 1000));
  set_rgb(160, 128, 0, 1000);
  //set_rgb(0, 255, 255, 1000);
  //set_rgb(255, 0, 255, 1000);
  //set_rgb(255, 255, 255, 1000);
}

void loop2() {
  int i = 0, j = 0, k = 0;

  for (i = 0; i < 255; i += 50) {
    for (j = 0; j < 255; j += 50) {
      for (k = 0; k < 255; k += 50) {
        set_rgb(i, j, k, 200);

      }
    }
  }
}

void simple_loop() {
  analogWrite(PIN_RED, 255);
  delay(1000);
  analogWrite(PIN_RED, 0);
  analogWrite(PIN_GREEN, 255);
  delay(1000);
  analogWrite(PIN_GREEN, 0);
  analogWrite(PIN_BLUE, 255);
  delay(1000);
  analogWrite(PIN_BLUE, 0);

  /*
  set_rgb(255, 0, 0);
  delay(1000);
  set_rgb(0, 255, 0);
  delay(1000);
  set_rgb(0, 0, 255);
  delay(1000);
  */
}
