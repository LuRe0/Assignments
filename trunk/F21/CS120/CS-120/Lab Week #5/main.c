/******************************************************************************
filename    triple_cubes.c
author      Anthon Reid
DP email    anthon.reid@digipen.edu
course      CS120
section     A
lab week    2
due date    10/16/2021

Brief Description:
  Main fuction to a program that finds every 3-digit integers in a range
  that have the cube property. 
******************************************************************************/
/* Function declarations */
void print_cubes(void);
void print_pythagorean_triples(int low, int high);

int main(void)
{
    /* Print all of the integers with the cube property */
  print_cubes();

    /* Print all of the triples from 1 up to 100        */
    /* but not including 100  [1, 100)                  */
  print_pythagorean_triples(1, 100);

  return 0;
}
