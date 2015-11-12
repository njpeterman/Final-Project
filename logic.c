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
      (*impulse_counter)++;
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

  if(*posY < 0) // if we hit the top of the screen
    {
      posY = 0;
      *velY = 0;
    } else if(*posY > BOTTOM_BOUND) // if we hit the bottom
    {
      *posY = BOTTOM_BOUND;
      *velY = 0;
    }
}

void determineVelX(double * velX, int keycode)
{

  switch(keycode)
    {
    case 0x07: // if right key (D) has been pressed
      *velX = HORIZONTAL_VELOCITY;
      break;
    case 0x04: //if left key (A) has been pressed
    	*velX = -1 * HORIZONTAL_VELOCITY;
      break;
    default:
      *velX = 0;
      break;
    }
}

void determinePosX(double * posX, double * velX)
{
  /* xf = x0 + at */
  *posX = *posX + (*velX * TIME_STEP);

  if(*posX < LEFT_BOUND)
    {
      *posX = LEFT_BOUND;
      *velX = 0;
    } else if(*posX > RIGHT_BOUND)
    {
      *posX = RIGHT_BOUND;
      *velX = 0;
    }
}
