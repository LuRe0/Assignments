/******************************************************************************
filename    bytes.c
author      Anthon Reid
DP email    anthon.reid@digipen.edu
course      CS120
section     A
Assignment  4
due date    11/11/2021

Brief Description:
  This program scans through bytes and finds, counts, compares, exchange
  or copies them.
  
******************************************************************************/
#include <stddef.h> /* NULL */



/******************************************************************************
   Function: find_byte

Description: Given two pointers (from and to), scan the range looking
             for the first occurrence of byte, returning a pointer to it. 

     Inputs: from - a pointer to a set of characters that is used to tell us
             where the array begin.s
             to - a pointer to a set of characters that is used to tell us
             where the array ends.
             byte - character that is being searcherd for.
             
    Outputs: Returns the byte when it is found or NULL when it is not
             found.
             
******************************************************************************/

const char *find_byte(const char *from, const char *to, char byte)
{
  while (from <= to) /* loops from the char from to char to */
  {
    if(*from == byte)/* when an occurence of byte is found  */ 
    {
      return from;   /* returns the value of from           */
    }
    
    from++;         /* increments from                      */
  }
  
  return NULL;  /*returns NULL if no occurences is found    */
}


/******************************************************************************
   Function: find_any_byte

Description: Given two pointers (from and to), scan the range looking
             for the first occurrence of any byte that is in the bytes array, 
             returning a pointer to it. 

     Inputs: from - a pointer to a set of characters that is used to tell us
             where the array begin.s
             to   - a pointer to a set of characters that is used to tell us
             where the array ends.
             set - array of characters that is being searcherd for.
             count- number of characters are in the set array.
             
    Outputs: Returns the byte when it is found or NULL when it is not
             found.

******************************************************************************/
const char *find_any_byte(const char *from, const char *to, const char *set, 
                          int count)
{
int j; /* iterator                                            */
  
  while ( from <= to) /* loops from the char from to char to  */
  {
    for (j = 0; j < count; j++) /* loops j reaches the set    */
    {
      if ( *(from) == *(set + j) ) /* when any byte is found  */ 
        {
          return from; /* returns the value of from           */
        }
    }
    from++;            /* increments from                     */
  }
  return NULL; /*returns NULL if no occurences is found       */
}


/******************************************************************************
   Function: count_bytes

Description: Given two pointers(from and to), scan the range 
             counting the number of occurrences of byte.

     Inputs: from - a pointer to a set of characters that is used to tell us
             where the array begin.s
             to - a pointer to a set of characters that is used to tell us
             where the array ends.
             byte - character that is being counted for.
             
    Outputs: Returns an integer, the number of occurrences of byte.

******************************************************************************/
int count_bytes(const char *from, const char *to, char byte)
{
int count =  0;      /* integer that counts the occurences  */
  while (from <= to) /* loops from the char from to char to */
  {
    if(*from == byte)/* when an occurence of byte is found  */ 
    {
     count++;        /* increments count                    */ 
    }
    from++;          /* increments from                     */
  }
  
  return count;      /* returns the number of occrences     */ 
}


/******************************************************************************
   Function: count_any_bytes

Description: Given two pointers (from and to), scan the range counting
             occurrences of any character that is in the bytes array. 

     Inputs: from - a pointer to a set of characters that is used to tell us
             where the array begin.s
             to - a pointer to a set of characters that is used to tell us
             where the array ends.
             byte - character that is being counted for.
             count- number of characters are in the bytes array.
             
    Outputs: Returns an integer, the number of times that byte appeared in the range.

******************************************************************************/
int count_any_bytes(const char *from, const char *to, const char *bytes, int count)
{
int j; /* iterator                                            */
int occurrence = 0; /* integer that counts the occurences     */
int sum = 0; /* integer that holds the sum                    */
  while ( from <= to) /* loops from the char from to char to  */
  {
    for (j = 0; j < count; j++) /* loops j reaches the count   */
    {
      if ( *(from) == *(bytes + j) )/* when any byte is found */ 
        {
          occurrence++; /* increments the occurences          */
        }
    }
    from++; /* increments from                                */
  }
  return sum += occurrence; /* returns the sum                */
}


/******************************************************************************
   Function: compare_bytes

Description: Given two pointers(location1 and location2), compare each character
             byte-by-byte to determine if the ranges are the same 

     Inputs: location1 - a pointer to a set of characters that is being compared.
             location2 - a pointer to a set of characters that is being compared.
             count- number of bytes to compare. 
             
    Outputs: Returns 0 if the bytes (characters) are all the same
             Returns -1 if the the bytes pointed to by location1 are 
             less than the bytes pointed to by location2.Otherwise, 
             the function returns 1.
             
******************************************************************************/
int compare_bytes(const char *location1, const char *location2, int count)
{
int i; /* iterator                                            */

  for (i = 0; i < count; i++) /* loops i reaches the count    */
  {
      /* bytes in location1 are less than in by location2     */
      if ( *(location1 + i) < *(location2 + i) )
        {
          return -1;  /* returns -1                           */
        }
      /* bytes in location1 are more than in by location2     */
      if ( *(location1 + i) > *(location2 + i) )
       {
         return 1;   /* returns 1                             */
       }
    }
  return 0; /* returns zero             */
}


/******************************************************************************
   Function: exchange_bytes

Description: Given two pointers(p1 and p2),
             exchange (swap) the bytes from each. 

     Inputs: p1 - a pointer to a set of characters that is used to be swapped
             p2 - a pointer to a set of characters that is to be swapped
             lenght- number of bytes to swap
             
    Outputs: none.
******************************************************************************/
void exchange_bytes(char *p1, char *p2, int length)
{
int i; /* iterator                                            */
char *temp; /* temporary char pointer                         */

  for (i = 0; i < length; i++) /* loops i reaches the length  */
  {
    *(temp + 1) = *(p1 + i); /* stores p1 into temp           */
    *(p1 + i) = *(p2 + i);   /* stores p2 into p1             */
    *(p2 + i) = *(temp + 1); /* stores temp into p2           */
  }
}


/******************************************************************************
   Function: copy_bytes

Description: Given two pointers(from and to), copy count bytes (characters)
             from the from pointer to the to pointer. 

     Inputs: from - a pointer to a set of characters that is used to tell us
             where the array begins
             to   - a pointer to a set of characters that is used to tell us
             where the array ends.
             length- number of characters are to be copied
             
    Outputs: none

******************************************************************************/
void copy_bytes(char *from, char *to, int length)
{
int i; /* iterator                                            */
  if(*from > *to) /* if from ovelaps with to and is greater   */
  {
    for (i = 0; i < length; i++) /* start from the beginning  */
    {
      *(to + i) = *(from + i); /* stores from into to         */
    }
  }
  else /* else if from ovelaps with to and is less            */
  {
      for (i = (length-1); i >= 0; i--) /* start from the end */
    {
      *(to + i) = *(from + i); /* stores from into to         */
    }
  }  
}


