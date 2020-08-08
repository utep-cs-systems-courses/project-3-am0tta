
#include <msp430.h>
#include <libTimer.h>
#include <lcdutils.h>
#include <lcddraw.h>
#include "p2switches.h"
#include "buzzer.h"
#include "stateMachines.h"
#include "stateAssembly.h"
#include "led.h"

#define GREEN_LED BIT6
void pacMan();


u_int bgColor = COLOR_BLUE;
int redrawScreen = 1;

void main()
{

  P1DIR |= GREEN_LED;/**< Green led on when CPU on */
  P1OUT |= GREEN_LED;
  configureClocks();
  lcd_init();
  led_init();
  p2sw_init(15);
  clearScreen(COLOR_BLUE);
  (p2sw_read());
  buzzer_init();

  drawString11x16(10,10, "THE CAKE", COLOR_GREEN, COLOR_RED);
  drawString11x16(10, 30, "IS A LIE!", COLOR_GREEN, COLOR_RED);

  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);              /**< GIE (enable interrupts) */
  
  for (int i = 0; i< 1000; i++){
    P1OUT = LED_RED;
    __delay_cycles(10000);
    P1OUT = LED_GREEN;
    __delay_cycles(10000);
    P1OUT = !LED_RED;
    __delay_cycles(10000);
    P1OUT = !LED_GREEN;
    __delay_cycles(10000);
    }
  for(;;) {

    while (!redrawScreen) { /**< Pause CPU if screen doesn't need updating */
      P1OUT &= ~GREEN_LED;    /**< Green led off witHo CPU */
      or_sr(0x10);      /**< CPU OFF */
    }
    P1OUT |= GREEN_LED;       /**< Green led on when CPU on */
 
    __delay_cycles(250000);       
    redrawScreen = 0;        // Turn CPU OFF whenever there is no need to redraw
  }

}
/** Watchdog timer interrupt handler. 15 interrupts/sec */
void wdt_c_handler()
{
  u_int switches = p2sw_read();
  static short count = 0;
  P1OUT |= GREEN_LED;      /**< Green LED on when cpu on */
  count++;
  static short flag =0;
  while(count == 15){

    //advance_assembly_lang();
    u_int switches = p2sw_read();
    if(~switches & SW1){
      for(int i = 1200;i<20000/2;i++){
	for(int j = 800;j<2000/2; j++){
	  buzzer_set_period(i);

	}

      }

      buzzer_set_period(0);

    }
    else if(~switches & SW2){
      pacMan();

    }
    else if(~switches & SW3){
      buzzer_set_period(1000);

    }
    else if(~switches & SW4){
      buzzer_set_period(0);

    }
    else
      if (p2sw_read())
	redrawScreen = 1;
    count = 0;

  }

  P1OUT &= ~GREEN_LED;    /**< Green LED off when cpu off */

}

void pacMan(){
  int i;

  drawPixel(50,50,COLOR_BLACK);
  drawPixel(51,50,COLOR_BLACK);
  drawPixel(52,50,COLOR_BLACK);
  drawPixel(53,50,COLOR_BLACK);

  drawPixel(49,51,COLOR_BLACK);
  drawPixel(48,51,COLOR_BLACK);
  drawPixel(54,51,COLOR_BLACK);
  drawPixel(55,51,COLOR_BLACK);
  drawPixel(50,51,COLOR_YELLOW);
  drawPixel(51,51,COLOR_YELLOW);
  drawPixel(52,51,COLOR_YELLOW);
  drawPixel(53,51,COLOR_YELLOW);

  drawPixel(47,52,COLOR_BLACK);
  drawPixel(56,52,COLOR_BLACK);
  for(i =48; i<56;i++)
    drawPixel(i,52, COLOR_YELLOW);

  drawPixel(46,53,COLOR_BLACK);
  drawPixel(57,53,COLOR_BLACK);
  for(i =47; i<57;i++)
    drawPixel(i,53, COLOR_YELLOW);

  drawPixel(45,54,COLOR_BLACK);
  drawPixel(58,54,COLOR_BLACK);
  for(i =46; i<58;i++)
    drawPixel(i,54, COLOR_YELLOW);


  drawPixel(45,55,COLOR_BLACK);
  drawPixel(56,55,COLOR_BLACK);
  drawPixel(57,55,COLOR_BLACK);
  for(i =46; i<56;i++)
    drawPixel(i,55, COLOR_YELLOW);


  drawPixel(44,56,COLOR_BLACK);
  drawPixel(53,56,COLOR_BLACK);
  drawPixel(54,56,COLOR_BLACK);
  drawPixel(55,56,COLOR_BLACK);
  for(i =45; i<53;i++)
    drawPixel(i,56, COLOR_YELLOW);

  drawPixel(44,57,COLOR_BLACK);
  drawPixel(50,57,COLOR_BLACK);
  drawPixel(51,57,COLOR_BLACK);
  drawPixel(52,57,COLOR_BLACK);

  for(i =45; i<50;i++)
    drawPixel(i,57, COLOR_YELLOW);


  drawPixel(44,58,COLOR_BLACK);
  drawPixel(52,58,COLOR_BLACK);
  for(i =45; i<52;i++)
    drawPixel(i,58, COLOR_YELLOW);

  drawPixel(44,59,COLOR_BLACK);
  drawPixel(53,59,COLOR_BLACK);
  drawPixel(54,59,COLOR_BLACK);
  drawPixel(55,59,COLOR_BLACK);
  for(i =45; i<53;i++)
    drawPixel(i,59, COLOR_YELLOW);

  
  drawPixel(45,60,COLOR_BLACK);
  drawPixel(56,60,COLOR_BLACK);
  drawPixel(57,60,COLOR_BLACK);
  for(i =46; i<56;i++)
    drawPixel(i,60, COLOR_YELLOW);


  drawPixel(45,61,COLOR_BLACK);
  drawPixel(58,61,COLOR_BLACK);
  for(i =46; i<58;i++)
    drawPixel(i,61, COLOR_YELLOW);


  drawPixel(46,62,COLOR_BLACK);
  drawPixel(57,62,COLOR_BLACK);

  for(i =47; i<57;i++)
    drawPixel(i,62, COLOR_YELLOW);

  drawPixel(47,63,COLOR_BLACK);
  drawPixel(56,63,COLOR_BLACK);
  for(i =48; i<56;i++)
    drawPixel(i,63, COLOR_YELLOW);

  drawPixel(48,64,COLOR_BLACK);
  drawPixel(49,64,COLOR_BLACK);
  drawPixel(54,64,COLOR_BLACK);
  drawPixel(55,64,COLOR_BLACK);
  for(i =50; i<54;i++)
    drawPixel(i,64, COLOR_YELLOW);


  drawPixel(50,65,COLOR_BLACK);
  drawPixel(51,65,COLOR_BLACK);
  drawPixel(52,65,COLOR_BLACK);
  drawPixel(53,65,COLOR_BLACK);
  
}
