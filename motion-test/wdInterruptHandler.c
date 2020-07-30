#include <msp430.h>
#include "led.h"
#include "dim.h"

void
__interrupt_vec(WDT_VECTOR) WD(){  /* 250 interrupts/sec */
  static char blink_count = 100;
  if(++blink_count == 125 ){
    sm_slow_clock();
    blink_count = 0;
  }
  sm_fast_clock();
  sm_update_led();

  led_update();
}
