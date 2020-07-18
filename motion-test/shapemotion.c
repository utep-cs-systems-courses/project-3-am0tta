/** \file shapemotion.c
 *  \brief This is a simple shape motion demo.
 *  This demo creates two layers containing shapes.
 *  One layer contains a rectangle and the other a circle.
 *  While the CPU is running the green LED is on, and
 *  when the screen does not need to be redrawn the CPU
 *  is turned off along with the green LED.
 */  
#include <msp430.h>
#include <libTimer.h>
#include <lcdutils.h>
#include <lcddraw.h>
#include "p2switches.h"
#include <shape.h>
#include <abCircle.h>
#include "buzzer.h"

#define GREEN_LED BIT6
void pacMan();


AbRect rect10 = {abRectGetBounds, abRectCheck, {10,10}}; /**< 10x10 rectangle */
AbRArrow rightArrow = {abRArrowGetBounds, abRArrowCheck, 30};

AbRectOutline fieldOutline = {	/* playing field */
  abRectOutlineGetBounds, abRectOutlineCheck,   
  {screenWidth/2 - 10, screenHeight/2 - 10}
};

Layer layer4 = {
  (AbShape *)&rightArrow,
  {(screenWidth/2)+10, (screenHeight/2)+5}, /**< bit below & right of center */
  {0,0}, {0,0},				    /* last & next pos */
  COLOR_PINK,
  0
};
  

Layer layer3 = {		/**< Layer with an orange circle */
  (AbShape *)&circle8,
  {(screenWidth/2)+10, (screenHeight/2)+5}, /**< bit below & right of center */
  {0,0}, {0,0},				    /* last & next pos */
  COLOR_VIOLET,
  &layer4,
};


Layer fieldLayer = {		/* playing field as a layer */
  (AbShape *) &fieldOutline,
  {screenWidth/2, screenHeight/2},/**< center */
  {0,0}, {0,0},				    /* last & next pos */
  COLOR_BLACK,
  &layer3
};

Layer layer1 = {		/**< Layer with a red square */
  (AbShape *)&rect10,
  {screenWidth/2, screenHeight/2}, /**< center */
  {0,0}, {0,0},				    /* last & next pos */
  COLOR_RED,
  &fieldLayer,
};

Layer layer0 = {		/**< Layer with an orange circle */
  (AbShape *)&circle14,
  {(screenWidth/2)+10, (screenHeight/2)+5}, /**< bit below & right of center */
  {0,0}, {0,0},				    /* last & next pos */
  COLOR_ORANGE,
  &layer1,
};

/** Moving Layer
 *  Linked list of layer references
 *  Velocity represents one iteration of change (direction & magnitude)
 */
typedef struct MovLayer_s {
  Layer *layer;
  Vec2 velocity;
  struct MovLayer_s *next;
} MovLayer;

/* initial value of {0,0} will be overwritten */
MovLayer ml3 = { &layer3, {1,1}, 0 }; /**< not all layers move */
MovLayer ml1 = { &layer1, {1,2}, &ml3 }; 
MovLayer ml0 = { &layer0, {2,1}, &ml1 }; 

void movLayerDraw(MovLayer *movLayers, Layer *layers)
{
  int row, col;
  MovLayer *movLayer;

  and_sr(~8);			/**< disable interrupts (GIE off) */
  for (movLayer = movLayers; movLayer; movLayer = movLayer->next) { /* for each moving layer */
    Layer *l = movLayer->layer;
    l->posLast = l->pos;
    l->pos = l->posNext;
  }
  or_sr(8);			/**< disable interrupts (GIE on) */


  for (movLayer = movLayers; movLayer; movLayer = movLayer->next) { /* for each moving layer */
    Region bounds;
    layerGetBounds(movLayer->layer, &bounds);
    lcd_setArea(bounds.topLeft.axes[0], bounds.topLeft.axes[1], 
		bounds.botRight.axes[0], bounds.botRight.axes[1]);
    for (row = bounds.topLeft.axes[1]; row <= bounds.botRight.axes[1]; row++) {
      for (col = bounds.topLeft.axes[0]; col <= bounds.botRight.axes[0]; col++) {
	Vec2 pixelPos = {col, row};
	u_int color = bgColor;
	Layer *probeLayer;
	for (probeLayer = layers; probeLayer; 
	     probeLayer = probeLayer->next) { /* probe all layers, in order */
	  if (abShapeCheck(probeLayer->abShape, &probeLayer->pos, &pixelPos)) {
	    color = probeLayer->color;
	    break; 
	  } /* if probe check */
	} // for checking all layers at col, row
	lcd_writeColor(color); 
      } // for col
    } // for row
  } // for moving layer being updated
}	  



//Region fence = {{10,30}, {SHORT_EDGE_PIXELS-10, LONG_EDGE_PIXELS-10}}; /**< Create a fence region */

/** Advances a moving shape within a fence
 *  
 *  \param ml The moving shape to be advanced
 *  \param fence The region which will serve as a boundary for ml
 */
void mlAdvance(MovLayer *ml, Region *fence)
{
  Vec2 newPos;
  u_char axis;
  Region shapeBoundary;
  for (; ml; ml = ml->next) {
    vec2Add(&newPos, &ml->layer->posNext, &ml->velocity);
    abShapeGetBounds(ml->layer->abShape, &newPos, &shapeBoundary);
    for (axis = 0; axis < 2; axis ++) {
      if ((shapeBoundary.topLeft.axes[axis] < fence->topLeft.axes[axis]) ||
	  (shapeBoundary.botRight.axes[axis] > fence->botRight.axes[axis]) ) {
	int velocity = ml->velocity.axes[axis] = -ml->velocity.axes[axis];
	newPos.axes[axis] += (2*velocity);
      }	/**< if outside of fence */
    } /**< for axis */
    ml->layer->posNext = newPos;
  } /**< for ml */
}


u_int bgColor = COLOR_BLUE;     /**< The background color */
int redrawScreen = 1;           /**< Boolean for whether screen needs to be redrawn */

Region fieldFence;		/**< fence around playing field  */


/** Initializes everything, enables interrupts and green LED, 
 *  and handles the rendering for the screen
 */
void main()
{
  P1DIR |= GREEN_LED;		/**< Green led on when CPU on */		
  P1OUT |= GREEN_LED;

  configureClocks();
  lcd_init();
  shapeInit();
  p2sw_init(15);

  (p2sw_read());
  
  shapeInit();

  layerInit(&layer0);
  layerDraw(&layer0);


  layerGetBounds(&fieldLayer, &fieldFence);
  pacMan();
  buzzer_init();
  for(int i =1200 ;i<20000/2;i++){                //Plays a tune before the game starts



    for(int j =800 ; j<2000/2; j++){

      buzzer_set_period(i);



    }

  }
  buzzer_set_period(0);                       //stops the tone

  

  enableWDTInterrupts();      /**< enable periodic interrupt */
  or_sr(0x8);	              /**< GIE (enable interrupts) */


  for(;;) { 
    while (!redrawScreen) { /**< Pause CPU if screen doesn't need updating */
      P1OUT &= ~GREEN_LED;    /**< Green led off witHo CPU */
      or_sr(0x10);	      /**< CPU OFF */
    }
    P1OUT |= GREEN_LED;       /**< Green led on when CPU on */
    redrawScreen = 0;
    movLayerDraw(&ml0, &layer0);
  }

  if(~SWITCHES & SW1){



    for(int i = 1200;i<20000/2;i++){



      for(int j = 800;j<2000/2; j++){



	buzzer_set_period(i);



      }



    }



  }



  else if(~SWITCHES & SW2){



    buzzer_set_period(100);


    //led_changed = changed;



    // led_update();



  }

  else if(~SWITCHES & SW3)



    buzzer_set_period(150);





  else if(~SWITCHES & SW4)



    buzzer_set_period(650);
}

/** Watchdog timer interrupt handler. 15 interrupts/sec */
void wdt_c_handler()
{
  static short count = 0;
  P1OUT |= GREEN_LED;		      /**< Green LED on when cpu on */
  count ++;
  if (count == 15) {
    mlAdvance(&ml0, &fieldFence);
    if (p2sw_read())
      redrawScreen = 1;
    count = 0;
  } 
  P1OUT &= ~GREEN_LED;		    /**< Green LED off when cpu off */
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
