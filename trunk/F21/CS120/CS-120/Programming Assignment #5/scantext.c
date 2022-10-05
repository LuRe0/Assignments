/******************************************************************************
filename    scantext.c
author      Anthon Reid
DP email    anthon.reid@digipen.edu
course      CS120
section     A
Assignment  5
due date    11/20/2021

Brief Description:
  This program counts the number of tabs in the string, substitutes
  characters,  calculates the length of the string 
  and the print length of the string, counts the number of words and
  returns the count.
  
******************************************************************************/

/******************************************************************************
   Function: count_tabs

Description: Given a string, count the number of tabs in the string 

     Inputs: string -  a pointer to a character that 
                        holds the sentence to be analyzed
             
    Outputs: Returns the count.
             
******************************************************************************/
int count_tabs(const char *string)
{
int count = 0; /*counts the number of tabs           */

  while(*string)/*while the string is not null       */
  {    
    if(*string == '\t')/*if we encounter a tab       */
    {
      count++; /* increment count                    */
    }
    string++; /* increment string                    */
  }
return count; /* return count                        */
}

/******************************************************************************
   Function: substitute_char

Description: Given a string, substitute old_char with new_char. 

     Inputs:  string -  a pointer to a character that 
                       holds the sentence to be analyzed
             old_char -  a pointer to a character will be replaced 
             
             new_char -  a pointer to a character will be replace an old one. 
             
    Outputs: Returns the number of substitutions.
             
******************************************************************************/
int substitute_char(char *string,
                    char old_char,
                    char new_char)
{
int subs = 0;  /*counts the number of substitution       */
  while (*string && string != 0)/*while the string is not null         */
  {
    if(*string == old_char)/*if we encounter a old_char  */
      {
        *string = new_char;/* replace it                 */
        subs++; /* increment subs                        */
      }
      string++; /* increment string                      */
  }
  return subs; /* return subs                            */
}

/******************************************************************************
   Function: calculate_lengths

Description: Given a string and a tabsize, calculate the length of the 
             string and the print length of the string. 

     Inputs: string -  a pointer to a character that 
                       holds the sentence to be analyzed
             tabsize -  an integer that holds the tabsize
             string_length -  a pointer to a character that 
                        holds the length of the string
             display_length -  a pointer to a character that 
                        holds print size
             
    Outputs: NONE
             
******************************************************************************/
void calculate_lengths(const char *string,
                       int tabsize,
                       int *string_length,
                       int *display_length)
{
/* sends a string to the previous funtion to extract the tabs  */
int tabs = count_tabs(string);
*(string_length) = 0;  /* initializes string_length to zero    */
*(display_length) = 0; /* initializes display_length to zero   */


  while(*string++) /*while the string is not null              */
  {
    *(string_length) += 1; /* increment string_length          */
  }
  
  
   /* removes previous tabs from length and add the new ones.  */
  *display_length = (*string_length - tabs) + (tabs * tabsize);
}

/******************************************************************************
   Function: count_words

Description: Given a string, count the number of words and return the count.  

     Inputs: string -  a pointer to a character that 
                       holds the sentence to be analyzed
             
    Outputs: Returns the count
             
******************************************************************************/
int count_words(const char *string)
{
int found = 0; /* bool that check if a word has been found       */
int words = 0; /* counts how many words were found               */

  while(*string++ && *string != 0) /*while the string is not null                */
  {    
    /*if a tab/space/newline is found while on a word            */
    if(found &&
       (*string == '\t' || 
        *string == '\n' ||
        *string == ' '  )) 
    {
      found = 0; /*sets found to false                           */
    }
    /*if anything but  a tab/space/newline is found              */
    if(!found  &&
      (*string != '\t' && 
       *string != '\n' &&
       *string != ' '  ))
    {
      found = 1;/*sets found to false                           */
      words++; /* increment words                               */
    }
  }


return words;  /* return the number of words found              */
}


