/** \file lcddemo.c
 *  \brief A simple demo that draws a string and square
 */

#include <libTimer.h>
#include "lcdutils.h"
#include "lcddraw.h"

void pacMan();
/** Initializes everything, clears the screen, draws "hello" and a square */
int
main()
{
  
  configureClocks();
  lcd_init();
  u_char width = screenWidth, height = screenHeight;

  clearScreen(COLOR_BLUE);

  drawString5x7(20,20, "hello", COLOR_GREEN, COLOR_RED);

  pacMan();


  
  //fillRectangle(30,30, 60, 60, COLOR_ORANGE);
  /*
  int i;
  for(int j =0; i <=60;){
    int row = j;
    for(int col =j;col<=screenWidth-j;col++)
      drawPixel(row,col,COLOR_PINK);
      }*/
    /*
  signed char c;
  for(c = 0; c<10; c++){
      for(signed char r = -c; r <c; r++)
	drawPixel(c+20, r+20, COLOR_BLACK);
	}*/
    
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
