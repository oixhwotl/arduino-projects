#include <stdarg.h>
#define SERIAL_PRINTF_MAX_BUFF 256
#define F_PRECISION 6

void _print(const char *fmt, ...);
void _println(const char *fmt, ...);
void print_status();

void _print(const char *fmt, ...) {
  /* buffer for storing the formatted data */
  char buf[SERIAL_PRINTF_MAX_BUFF];
  char *pbuf = buf;

  if (!DEBUG) {
    return;
  }

  /* pointer to the variable arguments list */
  va_list pargs;

  /* Initialise pargs to point to the first optional argument */
  va_start(pargs, fmt);
  /* Iterate through the formatted string to replace all 
  conversion specifiers with the respective values */
  while (*fmt) {
    if (*fmt == '%') {
      switch (*(++fmt)) {
        case 'd':
        case 'i':
          pbuf += sprintf(pbuf, "%d", va_arg(pargs, int));
          break;
        case 'u':
          pbuf += sprintf(pbuf, "%u", va_arg(pargs, unsigned int));
          break;
        case 'l':
          switch (*(++fmt)) {
            case 'd':
            case 'i':
              pbuf += sprintf(pbuf, "%ld", va_arg(pargs, long));
              break;
            case 'u':
              pbuf += sprintf(pbuf, "%lu",
                              va_arg(pargs, unsigned long));
              break;
          }
          break;
        case 'f':
          pbuf += strlen(dtostrf(va_arg(pargs, double),
                                 1, F_PRECISION, pbuf));
          break;

        case 'c':
          *(pbuf++) = (char)va_arg(pargs, int);
          break;
        case 's':
          pbuf += sprintf(pbuf, "%s", va_arg(pargs, char *));
          break;
        case '%':
          *(pbuf++) = '%';
          break;
        default:
          break;
      }
    } else {
      *(pbuf++) = *fmt;
    }

    fmt++;
  }

  *pbuf = '\0';

  va_end(pargs);
  Serial.print(buf);
}

void _println(const char *fmt, ...) {
  /* buffer for storing the formatted data */
  char buf[SERIAL_PRINTF_MAX_BUFF];
  char *pbuf = buf;

  if (!DEBUG) {
    return;
  }

  /* pointer to the variable arguments list */
  va_list pargs;

  /* Initialise pargs to point to the first optional argument */
  va_start(pargs, fmt);
  /* Iterate through the formatted string to replace all 
  conversion specifiers with the respective values */
  while (*fmt) {
    if (*fmt == '%') {
      switch (*(++fmt)) {
        case 'd':
        case 'i':
          pbuf += sprintf(pbuf, "%d", va_arg(pargs, int));
          break;
        case 'u':
          pbuf += sprintf(pbuf, "%u", va_arg(pargs, unsigned int));
          break;
        case 'l':
          switch (*(++fmt)) {
            case 'd':
            case 'i':
              pbuf += sprintf(pbuf, "%ld", va_arg(pargs, long));
              break;
            case 'u':
              pbuf += sprintf(pbuf, "%lu",
                              va_arg(pargs, unsigned long));
              break;
          }
          break;
        case 'f':
          pbuf += strlen(dtostrf(va_arg(pargs, double),
                                 1, F_PRECISION, pbuf));
          break;

        case 'c':
          *(pbuf++) = (char)va_arg(pargs, int);
          break;
        case 's':
          pbuf += sprintf(pbuf, "%s", va_arg(pargs, char *));
          break;
        case '%':
          *(pbuf++) = '%';
          break;
        default:
          break;
      }
    } else {
      *(pbuf++) = *fmt;
    }

    fmt++;
  }

  *pbuf = '\0';

  va_end(pargs);
  Serial.println(buf);
}

void print_status() {
  int i, j;
  for (i = PIN_LAYERS_MAX - 1; i >= 0; i--) {
    if (g_layers[i] == 1) {
      for (j = 3; j >= 0; j--) {
        _println("%d %d\t%d %c %c %c %c",
                 i, j,
                 g_layers[i],
                 (g_leds[j * 4 + 3] == LOW ? '*' : '_'),
                 (g_leds[j * 4 + 2] == LOW ? '*' : '_'),
                 (g_leds[j * 4 + 1] == LOW ? '*' : '_'),
                 (g_leds[j * 4] == LOW ? '*' : '_'));
      }
    } else {
      for (j = 3; j >= 0; j--) {
        _print("%d %d\t%d _ _ _ _", i, j, g_layers[i]);
      }
    }
  }
  _println("");
}