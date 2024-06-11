// DEBUG destroy LEDs lighting
#define DEBUG 0

// from debug.ino
void _print(const char *fmt, ...);
void _println(const char *fmt, ...);
void print_status();

// from common.ino
void set_layer(int layer_ind, int highlow);
void set_layer_high(int layer_ind);
void set_layer_low(int layer_ind);
void set_layers_high(int len, int *ind_arr);
void set_layers_low(int len, int *ind_arr);
void set_layers(int len, int *ind_arr, int highlow);
void set_all_layers_high();
void set_all_layers_low();
void set_led(int led_ind, int highlow);
void set_led_high(int led_ind);
void set_led_low(int led_ind);
void set_leds_high(int len, int *ind_arr);
void set_leds_low(int len, int *ind_arr);
void set_all_leds_high();
void set_all_leds_low();
void delay_n(int n = 1);
void turnoff_all();
void turnon_all();

#define PIN_LAYERS_MAX 4
#define PIN_LEDS_MAX 16
#define DELAY_1_TIME_MS 250

int PIN_LAYERS[PIN_LAYERS_MAX] = { A5, A4, A3, A2 };  // +
int PIN_LEDS[PIN_LEDS_MAX] = {                        // -
  // List PIN number according to your setup, As for mine, it's a messed.
  3, 2, 1, 0,
  7, 6, 5, 4,
  8, 9, 10, 11,
  12, 13, A0, A1
};

int g_leds[PIN_LEDS_MAX];
int g_layers[PIN_LAYERS_MAX];


void setup() {

  int i;
  for (i = 0; i < PIN_LAYERS_MAX; i++) {
    pinMode(PIN_LAYERS[i], OUTPUT);
    g_layers[i] = LOW;
  }

  for (i = 0; i < PIN_LEDS_MAX; i++) {
    pinMode(PIN_LEDS[i], OUTPUT);
    g_leds[i] = LOW;
  }

  if (DEBUG) {
    Serial.begin(9600);
  }

  randomSeed(analogRead(A0));
}

void loop() {
  //print_status();

  int pattern = random(4);
  switch (pattern) {
    case 0:
      light_in_order();
      break;
    case 1:
      center_4_light();
      edge_4_light();
      break;
    case 2:
      column_light();
      break;
    case 3:
      random_light();
      break; 
    default:
      blink_all();
      break;
  }

  blink_all();
}



void light_in_order() {
  turnoff_all();

  // set_all_layers_high();

  int i, j;

  set_all_layers_low();

  for (j = 0; j < PIN_LAYERS_MAX; j++) {
    set_layer_low(j-1 + PIN_LAYERS_MAX % PIN_LAYERS_MAX);
    set_layer_high(j);

    for (i = 0; i < PIN_LEDS_MAX; i++) {
      if (g_leds[i] == HIGH) {
        set_led_low(i);
      } else {
        set_led_high(i);
      }
      
      delay_n(1);
    }
  }
}

void blink_all() {

  turnon_all();
  delay_n(1);
  turnoff_all();
  delay_n(1);
}

void center_4_light() {

  const int center_4[4] = { 5, 6, 9, 10 };

  // CLEAR
  turnoff_all();

  // Turn on the 4 center LEDs
  set_leds_low(4, center_4);

  // Turn on the layer 0
  set_layer_low(3);
  set_layer_high(0);

  delay_n(1);

  // Turn on the layer 1
  set_layer_low(0);
  set_layer_high(1);

  delay_n(1);

  // Turn on the layer 2
  set_layer_low(1);
  set_layer_high(2);

  delay_n(1);

  // Turn on the layer 3
  set_layer_low(2);
  set_layer_high(3);

  delay_n(1);

  turnoff_all();
}


void column_light() {
  // 12 13 14 15
  //  8  9 10 11
  //  4  5  6  7
  //  0  1  2  3
  int spiral_out_path[PIN_LEDS_MAX] = {6, 5, 9, 10, 7, 3, 2, 1, 0, 4, 8, 12, 13, 14, 15, 11};
  int quads[4][4] = {
    {6, 7, 2, 3},
    {4, 5, 0, 1},
    {12, 13, 8, 9},
    {14, 15, 10, 11},
  };

  int i, j;

  turnoff_all();

  set_all_layers_high();
  for (i = 0; i < PIN_LEDS_MAX; i++) {
    if (i > 0) {
      set_led_high(spiral_out_path[i-1]);
    }

    set_led_low(spiral_out_path[i]);
    delay_n(1);
  }
  set_led_high(spiral_out_path[i-1]);

  for (i = 0; i < 4; i++) {
    if (i > 0) {
      set_leds_high(4, quads[i-1]);
    }
    set_leds_low(4, quads[i]);
    delay_n(1);
  }
  set_leds_high(4, quads[i-1]);

  for (i = 3; i >= 0; i--) {
    if (i < 3) {
      set_leds_high(4, quads[i+1]);
    }
    set_leds_low(4, quads[i]);
    delay_n(1);
  }
  set_leds_high(4, quads[0]);

  digitalWrite(PIN_LEDS[9], LOW);
  digitalWrite(PIN_LEDS[8], LOW);
  digitalWrite(PIN_LEDS[12], LOW);
  digitalWrite(PIN_LEDS[13], LOW);
  delay_n(1);

  digitalWrite(PIN_LEDS[9], HIGH);
  digitalWrite(PIN_LEDS[8], HIGH);
  digitalWrite(PIN_LEDS[12], HIGH);
  digitalWrite(PIN_LEDS[13], HIGH);
  digitalWrite(PIN_LEDS[5], LOW);
  digitalWrite(PIN_LEDS[4], LOW);
  digitalWrite(PIN_LEDS[0], LOW);
  digitalWrite(PIN_LEDS[1], LOW);
  delay_n(1);

  digitalWrite(PIN_LEDS[5], HIGH);
  digitalWrite(PIN_LEDS[4], HIGH);
  digitalWrite(PIN_LEDS[0], HIGH);
  digitalWrite(PIN_LEDS[1], HIGH);
  digitalWrite(PIN_LEDS[6], LOW);
  digitalWrite(PIN_LEDS[7], LOW);
  digitalWrite(PIN_LEDS[2], LOW);
  digitalWrite(PIN_LEDS[3], LOW);
  delay_n(1);

  digitalWrite(PIN_LEDS[6], HIGH);
  digitalWrite(PIN_LEDS[7], HIGH);
  digitalWrite(PIN_LEDS[2], HIGH);
  digitalWrite(PIN_LEDS[3], HIGH);
  digitalWrite(PIN_LEDS[10], LOW);
  digitalWrite(PIN_LEDS[11], LOW);
  digitalWrite(PIN_LEDS[14], LOW);
  digitalWrite(PIN_LEDS[15], LOW);
  delay_n(1);
}



void edge_4_light() {
  const int edge_4[4] = {0, 3, 12, 15 };

  turnoff_all();

  set_leds_low(4, edge_4);

  set_layer_low(3);
  set_layer_high(0);
  delay_n(1);

  set_layer_low(0);
  set_layer_high(1);
  delay_n(1);

  set_layer_low(1);
  set_layer_high(2);
  delay_n(1);

  set_layer_low(2);
  set_layer_high(3);
  delay_n(1);

  turnoff_all();
}

void random_light() {
  turnoff_all();

  int i, j;
  int random_leds, random_led, random_layer, random_layers, random_delay;
  int leds[PIN_LEDS_MAX], layers[PIN_LAYERS_MAX];
  
  for (i = 0; i < PIN_LEDS_MAX/2; i++) {
    random_delay = random(4);
    random_leds = random(PIN_LEDS_MAX);
    random_layers = random(PIN_LAYERS_MAX);

    for (j = 0; j < random_leds; j++) {
      leds[j] = random(PIN_LEDS_MAX);
    }

    for (j = 0; j < random_layers; j++) {
      layers[j] = random(PIN_LAYERS_MAX);
    }

    set_leds_low(random_leds, leds);
    set_layers_high(random_layers, layers);

    delay_n(random_delay + 1);

    set_leds_high(random_leds, leds);
    set_layers_low(random_layers, layers);

    //delay_n(4 - random_delay + 1);
  }

  turnoff_all();
}

void random_light2() {
  turnoff_all();

  int i, j;
  int random_leds, random_led, random_layer, random_layers, random_delay;
  int leds[PIN_LEDS_MAX], layers[PIN_LAYERS_MAX];
  
  for (i = 0; i < PIN_LEDS_MAX/2; i++) {
    random_delay = random(4);
    random_leds = random(PIN_LEDS_MAX);
    random_layers = random(PIN_LAYERS_MAX);

    for (j = 0; j < random_leds; j++) {
      leds[j] = random(PIN_LEDS_MAX);
    }

    for (j = 0; j < random_layers; j++) {
      layers[j] = random(PIN_LAYERS_MAX);
    }

    set_leds_low(random_leds, leds);
    set_layers_high(random_layers, layers);

    delay_n(1);
    for (j = 0; j < random_delay; j++) {
      if (j % 2 == 0) {
        set_layers(random_layers, layers, HIGH/2);
      } else {
        set_layers_high(random_layers, layers);
      }
      delay_n(1);
    }

    set_leds_high(random_leds, leds);
    set_layers_low(random_layers, layers);

    //delay_n(4 - random_delay + 1);
  }

  turnoff_all();
}