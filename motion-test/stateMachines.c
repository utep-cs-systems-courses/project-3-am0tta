#include <msp430.h>
#include <libTimer.h>
#include <lcdutils.h>
#include <lcddraw.h>
#include <p2switches.h>
#include <shape.h>
#include "buzzer.h"
#include "stateMachines.h"


void stateAdvance(){

  switch(state){
  case 1:
    for(int i = 1200;i<20000/2;i++){
      for(int j = 800;j<2000/2; j++){
	buzzer_set_period(i);

      }
    }
    state = 1;
    break;
  case 2:
    pacman();
    state = 2;
    break;
  case 3:
    buzzer_set_period(1000);
    state = 3;
    break;
  case 4:
    buzzer_set_period(0);
    state = 4;
    break;
  }
}


