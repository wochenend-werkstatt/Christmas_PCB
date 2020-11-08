#include <avr/interrupt.h>
#include <avr/power.h>
#include <avr/sleep.h>

int card = 9;

ISR(WDT_vect) {
  card++;
}

void setup() {
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);

  // prescale timer up to 8s
  WDTCR |= (0 << WDP3 ) | (1 << WDP2 ) | (0 << WDP1) | (0 << WDP0);

  // Enable watchdog timer interrupts
  WDTCR |= (1 << WDTIE);

  sei(); // Enable global interrupts

  ADCSRA &= ~(1 << ADEN); // disable ADC (before power-off)

  // Use the Power Down sleep mode
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  
  for (;;) {
    sleep_enable();
    sleep_mode();   // go to sleep and wait for interrupt...
    sleep_disable();
    power_all_enable();
    switch (card) {
      case 1:
        digitalWrite(4, HIGH);
        break;
      case 2:
        digitalWrite(4, LOW);
        digitalWrite(3, HIGH);
        break;
      case 3:
        digitalWrite(3, LOW);
        digitalWrite(2, HIGH);
        break;
      case 4:
        digitalWrite(2, LOW);
        digitalWrite(1, HIGH);
        break;
      case 5:
        digitalWrite(1, LOW);
        break;
      case 12:
        for (int brightness = 0; brightness < 255; brightness++) {
          analogWrite(0, brightness);
          delay(2);
        }
        break;
      case 20:
        for (int brightness = 255; brightness >= 0; brightness--) {
          analogWrite(0, brightness);
          delay(2);
        }
        break;
      case 26:
        for (int brightness = 0; brightness < 255; brightness++) {
          analogWrite(0, brightness);
          delay(2);
        }
        break;
      case 34:
        for (int brightness = 255; brightness >= 0; brightness--) {
          analogWrite(0, brightness);
          delay(2);
        }
        break;
      case 41:
        digitalWrite(4, HIGH);
        break;
      case 42:
        digitalWrite(4, LOW);
        digitalWrite(3, HIGH);
        break;
      case 43:
        digitalWrite(3, LOW);
        digitalWrite(2, HIGH);
        break;
      case 44:
        digitalWrite(2, LOW);
        digitalWrite(1, HIGH);
        break;
      case 45:
        digitalWrite(1, LOW);
        break;
      case 62:
        card = 0;
        break;
    }
  }
}