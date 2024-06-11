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

void set_layer(int layer_ind, int highlow) {
  if (layer_ind < 0 || layer_ind >= PIN_LAYERS_MAX) {
    _println("ERROR: %s: layer_ind=%d", __func__, layer_ind);
    return;
  }

  if (g_layers[layer_ind] == highlow) {
    return;
  }

  digitalWrite(PIN_LAYERS[layer_ind], highlow);
  g_layers[layer_ind] = highlow;
}

void set_layer_high(int layer_ind) {
  set_layer(layer_ind, HIGH);
}

void set_layer_low(int layer_ind) {
  set_layer(layer_ind, LOW);
}

void set_layers_high(int len, int *ind_arr) {
  int i;
  for (i = 0; i < len; i++) {
    set_layer_high(ind_arr[i]);
  }
}

void set_layers_low(int len, int *ind_arr) {
  int i;
  for (i = 0; i < len; i++) {
    set_layer_low(ind_arr[i]);
  }
}

void set_layers_low(int len, int *ind_arr, int highlow) {
  int i;
  for (i = 0; i < len; i++) {
    set_layer(ind_arr[i], highlow);
  }
}

void set_all_layers_high() {
  int i;
  for (i = 0; i < PIN_LAYERS_MAX; i++) {
    set_layer_high(i);
  }
}

void set_all_layers_low() {
  int i;
  for (i = 0; i < PIN_LAYERS_MAX; i++) {
    set_layer_low(i);
  }
}

void set_led(int led_ind, int highlow) {
  int i;

  if (led_ind < 0 || led_ind >= PIN_LEDS_MAX) {
    _println("ERROR: %s: led_ind=%d", __func__, led_ind);
    return;
  }

  if (g_leds[led_ind] == highlow) {
    return;
  }

  digitalWrite(PIN_LEDS[led_ind], highlow);
  g_leds[led_ind] = highlow;
}

void set_led_high(int led_ind) {
  set_led(led_ind, HIGH);
}

void set_led_low(int led_ind) {
  set_led(led_ind, LOW);
}

void set_leds_high(int len, int *ind_arr) {
  int i;
  for (i = 0; i < len; i++) {
    set_led_high(ind_arr[i]);
  }
}

void set_leds_low(int len, int *ind_arr) {
  int i;
  for (i = 0; i < len; i++) {
    set_led_low(ind_arr[i]);
  }
}

void set_all_leds_high() {
  int i;
  for (i = 0; i < PIN_LEDS_MAX; i++) {
    set_led_high(i);
  }
}

void set_all_leds_low() {
  int i;
  for (i = 0; i < PIN_LEDS_MAX; i++) {
    set_led_low(i);
  }
}

void delay_n(int n = 1) {
  if (n > 0) {
    delay(DELAY_1_TIME_MS * n);
  }
}

void turnoff_all() {
  set_all_layers_low();
  set_all_leds_high();
}

void turnon_all() {
  set_all_layers_high();
  set_all_leds_low();
}