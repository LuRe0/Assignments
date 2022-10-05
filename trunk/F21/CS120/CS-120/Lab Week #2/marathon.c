/******************************************************************************
filename    marathon.c
author      Anthon Reid
DP email    anthon.reid@digipen.edu
course      CS120
section     A
lab week    2
due date    09/25/2021

Brief Description:
  This program converts the distance of a marathon from miles to kilometers.
  
******************************************************************************/

#include <stdio.h> /* printf */

/* Convenient definitions */
#define YARDS_PER_MILE 1760
#define KILOS_PER_MILE 1.609

/* A marathon is 26 miles, 385 yards               */
/* Prints the distance of a marathon in kilometers */
int main(void)
{
  int miles = 26;    /* Miles in a marathon                 */
  int yards = 385;   /* Yards in a marathon                 */
  double kilometers; /* Calculated kilometers in a marathon */
  
    /* Convert miles and yards into kilometers */
  kilometers = (miles + (double)yards / YARDS_PER_MILE) * KILOS_PER_MILE;

    /* Display the result on the screen */
  printf("A marathon is %f kilometers\n", kilometers);
  
    /* Return successful value to OS */
  return 0;
}
