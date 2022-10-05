/******************************************************************************
filename    triple_cubes.c
author      Anthon Reid
DP email    anthon.reid@digipen.edu
course      CS120
section     A
lab week    2
due date    10/16/2021

Brief Description:
  This program finds every 3-digit integers in a range
  that have the cube property. 
  
******************************************************************************/
#include <stdio.h>

/* Function declarations */
void print_cubes(void);
void print_pythagorean_triples(int low, int high);

  int digit1;
  int digit2;
  int digit3;
  int i, j, k;
  int size, size1;
  
  
void print_cubes(void)
{
  /* All code for this function goes here. */ 

  for ( size = 100; size <= 999; size++)
  {
    for (digit1 = size / 100, digit2 = (size / 10) % 10, digit3 = size % 10;
      ((digit1 * digit1 * digit1) +
      (digit2 * digit2 * digit2) + (digit3 * digit3 * digit3)) == size;
      digit1++, digit2++, digit3++)
    {
      printf("%d has the cube property. (%d + %d + %d)\n",
      size, (digit1 * digit1 * digit1),
      (digit2 * digit2 * digit2), (digit3 * digit3 * digit3));
    }
  }  
}

void print_pythagorean_triples(int low, int high)
{
  /* All code for this function goes here. */
    for (i = 0; i < high; i++)
    {
      for (j = 0; j < high; j++)
      {
        for (k = 0; k < high; k++)
        {
          if((i * i) + (j * j) == (k * k) && j < k && i < j)
          {
          printf("Triple #%3i: %3i,%3i,%3i --> %4i + %4i = %4i\n",
          low, i, j, k, (i * i), (j * j), (k * k));
          low++;
          }
        }
      }
    }
}
