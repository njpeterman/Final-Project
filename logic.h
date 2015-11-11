#ifndef LOGIC_H_
#define LOGIC_H_

#define GRAVITY 9.81
#define IMPULSE 30
#define IMPULSE_TIME_LIMIT 1000
#define JUMP_STEP 5
#define TIME_STEP 0.1
#define RIGHT_BOUND 639
#define BOTTOM_BOUND 439
#define LEFT_BOUND 239

// insert functions implemented here

void determineVelY(double * velY, int keycode, int canJump, int * impulse_counter);
void determinePosY(double * posY, double * velY);
void determineVelX(double * velX, int keycode);
void determinePosX(double * posX, double * velX);
#endif
