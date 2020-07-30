#include <msp430.h>
#include "led.h"
#include "dim.h"

static enum {off = 0, dim = 1, bright = 2} ledMode;
static char pwmCount = 0;

void
sm_slow_clock(){
  
  ledMode = (ledMode + 1) % 3;
  
}

void
sm_fast_clock(){
  
  pwmCount = (pwmCount + 1) & 3;

}

void
sm_update_led(){
  char new_red_on;
  switch (ledMode){
  case off:
    new_red_on = 0;
    break;
  case bright:
    new_red_on =1;
    break;
  case dim:
    new_red_on = (pwmCount <1);
    break;
  }
  if (red_on != new_red_on){
    red_on = new_red_on;
    led_changed = 1;
  }
}
