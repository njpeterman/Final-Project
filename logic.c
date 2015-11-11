#include "logic.h"
#include <stdio.h>
#include <math.h>


/* ****************************************
 * determineVelY
 * The purpose of this function is to determine the 
 * velocity with given gravity. 
 * 
 * The way we do this is by defining an impulse acceleration,
 * which activates every single time the character tries to jump.
 * 
 * 
 * 
 * 
 *
 *
 *
 *
 *
 * *************************************** */
void determineVelY(double * velY, int keycode, int canJump, int * impulse_counter)
{
  switch(keycode)
    {
    case 0x20: // if space bar has been pressed
      if(canJump) // check if we can jump, ie, we may already be in the air
	{
	  *impulse_counter = 1; // start the impulse counter
	}
      break;
    default: break;
    }

  // here we apply the impulse acceleration if we have previously jumped
  if(*impulse_counter > 0 && *impulse_counter <= IMPULSE_TIME_LIMIT) 
    {
      *velY = *velY + (IMPULSE * TIME_STEP);
      *impulse_counter++;
    } else
    { // reset the counter
      *impulse_counter = 0;
    }  
  
  /* Vf = Vo - at */
  *velY = *velY - (GRAVITY * TIME_STEP);
}


void determinePosY(double * posY, double * velY)
{
  /* xf = x0 + at */
  *posY = *posY + (*velY * TIME_STEP);

  if(*posY < 0)
    {
      posY = 0;
    } else if(*posY > BOTTOM_BOUND)
    {
      *posY = BOTTOM_BOUND;
    }
}
