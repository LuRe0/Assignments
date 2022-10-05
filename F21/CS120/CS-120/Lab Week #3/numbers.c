/******************************************************************************
filename    numbers.c
author      Anthon Reid 
DP email    anthon.reid@digipen.edu
course      CS120
section     A
lab week    3
due date    10/02/2021

Brief Description:
This program calculates in radians 
* the value of any 3 inputted numbers between 0 and 9.999
*  using trigonometric functions. 
  
*******************************************************************************/


#include <stdio.h> 
#include <math.h>

float input1;
float input2;
float input3;


int main(void){
     /*This prints a message asking the user to 
      * provide 3 numbers between 0 and 9.999 */
     printf("Enter 3 numbers between 0 and 9.999: \n");
     /*This receives the user's inputs */
     scanf("%f %f %f", &input1, &input2, &input3);
     /*This prints the table of the value of the 3 inputted numbers
      *  in radians using trigonometric functions */
     printf("Number      sin      cos      tan      atan\n");
     printf("-------------------------------------------\n");
     printf("%.5f%9.3f%9.3f%9.3f%9.3f\n", 
     input1, sin(input1), cos(input1), tan(input1), atan(input1));
     printf("%.5f%9.3f%9.3f%9.3f%9.3f\n",
     input2, sin(input2), cos(input2), tan(input2), atan(input2));
     printf("%.5f%9.3f%9.3f%9.3f%9.3f\n",
     input3, sin(input3), cos(input3), tan(input3), atan(input3));
return 0;
}

