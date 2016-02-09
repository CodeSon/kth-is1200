/* mipslabwork.c

   This file written 2015 by F Lundevall

   This file should be changed by YOU! So add something here:

   This file modified 2015-12-24 by Ture Teknolog 

   Latest update 2015-08-28 by F Lundevall

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

int mytime = 0x5957;

char textstring[] = "text, more text, and even more text!";

/* Interrupt Service Routine */
void user_isr( void )
{
  return;
}

/* Lab-specific initialization goes here */
void labinit( void )
{
  // defining the int pointer, trise, volatile because you 
  //don't want the c compiler to optimise
  volatile int * E = (volatile int *) 0xbf886100;
  // only for the last 8 bits
  * E = * E & 0xFF00;
  // initialising port D as input
  // using the pic32mx system
  TRISD = TRISD & 0x0FE0;
  return;
}

/* This function is called repetitively from the main program */
void labwork( void )
{
  volatile int * portE = (volatile int *) 0xbf886110;
  * portE = 0x0; // for LED outputs
  int BTN;
  int SW;

  while(1) { 
    delay( 1000 ); 
    BTN = getbtns();
    SW = getsw();
    
    //for button 2
    if(BTN == 1 || BTN == 3 || BTN == 5 || BTN == 7){
      mytime = mytime & 0xFF0F;
      mytime = (SW << 4) | mytime;
    }
    // for button 3
    if(BTN == 2 || BTN == 3 || BTN == 6 || BTN == 7){
      mytime = mytime & 0xF0FF;
      mytime = (SW << 8) | mytime;
    }
    // for button 4
    if(BTN == 4 || BTN == 5 || BTN == 6 || BTN == 7){
      mytime = mytime & 0x0FFF;
      mytime = (SW << 12) | mytime;
    }
    
    time2string( textstring, mytime );
    display_string( 3, textstring );
    display_update();
    tick( &mytime );
    display_image(96, icon);
    // for LEDs ticking
     * portE =  * portE + 0x1;
  }
}
