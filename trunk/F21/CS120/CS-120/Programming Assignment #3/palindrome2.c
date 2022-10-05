/******************************************************************************
filename    palidrome2.c
author      Anthon Reid
DP email    anthon.reid@digipen.edu
course      CS120
section     A
Assignment  3
due date    11/04/2025

Brief Description:
  This checks if a word or sentence is a palindrome using pointers.  
  
******************************************************************************/


/******************************************************************************
   Function: is_palindrome2

Description: Given an array of characters, Thus will determine if it's a 
             palindrome using array subscripting. 

     Inputs: phase - a pointer that points to the charcters that will 
             be analyzed to determine if its a palidrome
             lenght - integer that will be used to hold 
             the length of the array of characters.
             
    Outputs: Returns 1 (true) if the phrase is a palindrome
             and 0 (false) if not.
******************************************************************************/
int is_palindrome2(const char *phrase, int length)
{
int i;                       /* iterator for loop                  */
int last_char = length - 1;  /* Last character of the pointer      */
int return_val = 1;          /* integer to be returned by function */

  /* Loops until halfway while condition for plaindrome holds      */
  for (i = 0; (i < (length / 2)) && (return_val == 1); i++)
  {  
  /* first half not equal to second half                           */
    if (*(phrase + i) != *(phrase + last_char))
    {
      return_val = 0;       /* return false                        */
    }
    last_char --;           /* decrement last index value          */
  }
  return return_val;        /* returns true                        */
}


