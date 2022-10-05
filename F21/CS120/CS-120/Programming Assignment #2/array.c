/******************************************************************************
filename    array.c
author      Anthon Reid
DP email    anthon.reid@digipen.edu
course      CS120
section     A
Assignment  2
due date    10/21/2021

Brief Description:
  The program will manipulate arrays by reversing 
  the order of its elements, adding its elements,
  multiplying each element by a given multiplier,
  and determining their dot and cross products. 
  
******************************************************************************/

/******************************************************************************
   Function: reverse_array

Description: This will reverse the order of a given array..

     Inputs: a - an array of integers that will be reversed.
             size - integer that will be used to hold the size of the arrays.
             
    Outputs: none
******************************************************************************/
void reverse_array(int a[], int size)
{
    int i;   /* iterator for the loop */
    int temp;/* temporary variable to hold the array indexes */
    int back = size - 1; /* integer iterator that holds the indexes
                            starting from the end */

    for (i = 0; i < (size / 2); i++) /*loos until the halfway point*/
    {
        temp = a[i]; /* stores the value of a in the temporary integer */
        a[i] = a[back]; /*replaces the first value with the last one */
        a[back] = temp; /*places the first integer in the last index of the array */
        back--; /* decrements the back index integer */
    }
}


/******************************************************************************
   Function: add_arrays

Description: This will calculate a third array by adding two arrays together.

     Inputs: a - an array of integers that will be used in the addition calculation
             b - an array of integers that will be used in the addition calculation
             c - an array of integers that will be used to hold the resulting third arrays.
             size - integer that will be used to hold the size of the arrays.
             
    Outputs: none
******************************************************************************/
void add_arrays(const int a[], const int b[], int c[], int size)
{
int i;/* iterator for the loop */
for( i = 0; i < size; i++)
  {
    c[i] = a[i] + b[i];  /*adds each matching index of the two arrays */	
  }
}


/******************************************************************************
   Function: scalar_multiply

Description: This will calculate a new array by multiplying
             a scalar by an initial array.

     Inputs: a - an array of integers that will be used in the dot product calculation
             size - integer that will be used to hold the size of the arrays.
             multiplier - integer that will be used to be muti[plied by the array.
             
    Outputs: none
******************************************************************************/
void scalar_multiply(int a[], int size, int multiplier)
{
  int i; /* iterator for the loop */
  for(i = 0; i < size; i++)
  {
    a[i] = multiplier * a[i]; /* mutliply each index of the array 
                                 by the scalar mutliplier. */
  }

}


/******************************************************************************
   Function: dot_product

Description: This will calculate the dot product of two arrays.
             Returns the resuling scalar.

     Inputs: a - an array of integers that will be used in the dot product calculation
             b - an array of integers that will be used in the dot product calculation
             size - integer that will be used to hold the size of the arrays.
             
    Outputs: The scalar result of the dot product of the arrays.  
******************************************************************************/
int dot_product(const int a[], const int b[], int size)
{
  int i; /* iterator for the loop */
  int scalar = 0; /* Scalar that will hold the result of the dot product */
  for ( i = 0; i < size; i++)
  {
    scalar += a[i] * b[i];  /* multiplies the matching index values
                               of the two arrays and adds the results */
  }

  return scalar; /* returns the scalar result of the dot product */
}


/******************************************************************************
   Function: cross_product

Description: This will calculate the the cross product of two arrays.

     Inputs: a - an array of integers that will be used in the cross product calculation
             b - an array of integers that will be used in the cross product calculation
             c - an array of integers that will be used to the resulting third array.
             
    Outputs: none
******************************************************************************/
void cross_product(const int a[], const int b[], int c[])
{
  /* Cross Product Formula */
  c[0] = a[1]*b[2] - a[2]*b[1];
  c[1] = a[2]*b[0] - a[0]*b[2];
  c[2] = a[0]*b[1] - a[1]*b[0];

}
