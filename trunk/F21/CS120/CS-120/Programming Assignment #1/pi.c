/******************************************************************************
filename    pi.c
author      Anthon Reid
DP email    anthon.reid@digipen.edu
course      CS120
section     A
lab week    2
due date    10/09/2021

Brief Description:
  This program calculates the value of pi using the The Leibniz Method 
  and The Circle Method. 
  
******************************************************************************/
#include <stdio.h>
#include <math.h>

double circle_pi(int rectangles);  /* Calculates PI using a quarter circle */
double leibniz_pi(int iterations); /* Calculates PI using a series         */

/******************************************************************************
   Function: circle_pi

Description: This will calculate the apporximation of pi using the 
             leibniz series method. Returns the approximation of pi.

     Inputs: rectangles - A integer that receives the number of reactangles
                          in each iterations to apporiximate the value of pi.
             
    Outputs: The approximated value of pi (double). 
******************************************************************************/
double circle_pi(int rectangles)   /* Calculates PI using a quarter circle */
{
  double radius = 2;                  /* Radius of the quarter circle      */
  double width = radius / rectangles; /* Width of each rectangles          */
  double midpoint = 0;                /* Mindpoint of each rectangles      */
  double height = 0;                  /* Heigh of each rectangles          */
  double area = 0;                    /* Area and approximation of pi      */ 
  int i;          /* Integer handling the number of iteration in the loop  */

  for(i = 0; i < rectangles; i++)
  {
    midpoint = (width / 2) + (width * i);
    height = sqrt((radius * radius) - (midpoint * midpoint));
    area += width * height;
  }
  return area;     /* returns the approximated value of pi                 */
}
/******************************************************************************
   Function: leibniz_pi

Description: This will calculate the apporximation of pi using the 
             leibniz series method. Returns the approximation of pi.

     Inputs: iterations - A interger that receives the number of iterations
                          that the series will go throught to apporiximate pi.
             
    Outputs: The approximated value of pi (double). 
******************************************************************************/
double leibniz_pi(int iterations) /* Calculates PI using a series          */
{
  double denominator = 1; /* The denominator of the fraction in the series */
  double numerator = 1;   /* The numerator of the fraction in the series   */
  double pi = 0; /* Holds the the value of the approximation of pi         */
  int i =0; /* Integer handling the number of iteration in the loop        */

  while (i < iterations )
  {
     pi += numerator/denominator ;
     denominator += 2;
     numerator *= -1; 
     i++;
  }
  return pi * 4;   /* returns the approximated value of pi                 */
}
