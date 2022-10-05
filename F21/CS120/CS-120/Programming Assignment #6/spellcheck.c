/******************************************************************************
filename    spellcheck.c
author      Anthon Reid
DP email    anthon.reid@digipen.edu
course      CS120
section     A
Assingment  6
due date    12/2/2021

Brief Description:
  This program count the number of words that start with certain letters,
  looks up words in a dictionary, counts the number of words of a certain length,
  checks the spelling of words.
  
******************************************************************************/
#include <string.h> /* To be completed by the student       */
#include <stdio.h>  /* FILE (To be completed by the student */

/* FILE_OK, FILE_ERR_OPEN, WORD_OK, WORD_BAD, LONGEST_WORD */
#include "spellcheck.h"


/******************************************************************************
   Function: mystrlen

Description: Given a string count its length 

     Inputs: string -  a pointer to a character that 
                        holds the sentence to be analyzed
             
    Outputs: returns length of the string
             
******************************************************************************/
static int mystrlen(const char *string)
{
  int length = 0; /* The number of characters in the string */
  
    /* Count the characters (not including the NUL)         */  
  while (*string++)
    length++;

  return length;
}

/******************************************************************************
   Function: spell_check

Description: Given the string and a word, replaces new line with
            NUL pointer.

     Inputs: buffer -  a pointer to a character that 
                        holds the sentence to be analyzed
             
    Outputs: NONE
             
******************************************************************************/

static void replace_new_line(char *buffer)
{
     /* replaces new line with NUl pointer */
    *(buffer + mystrlen(buffer) - 1) = '\0';

}

/******************************************************************************
   Function: mystrupr

Description: Given a string, convert all lowercase letters to uppercase. 

     Inputs: string -  a pointer to a character that 
                        holds the sentence to be analyzed
             
    Outputs: Returns a pointer to the first character of the string.
     
******************************************************************************/
char *mystrupr(char *string)
{
  /* while string is not null               */
  while(*string && *string != 0)
  {
    /* if string is lowercase               */
    if(*string >='a' && *string <='z')
    {
      /* make it uppercase                  */
      *string = *string - 32;
    }
    string++; /* increments string          */
  }
 
 return string; /* returns string           */
}

/******************************************************************************
   Function: words_starting_with

Description: Given the filename of a dictionary, count the number of 
             words that start with letter.

     Inputs: dictionary -  a pointer to a character that 
                        holds the name of the file
             letter     - a pointer to a character that holds the
                          first letter of the word
             
    Outputs:  return the number of words that start with letter. 
              If the file can't be opened, return FILE_ERR_OPEN
             
******************************************************************************/
int words_starting_with(const char *dictionary, char letter)
{
  FILE* file; /* create the file                             */
  int word_count = 0; /* count the number of words in buffer */
  char buffer[LONGEST_WORD]; /* holds the string             */
  
  
  file = fopen(dictionary, "r"); /* open the file            */
 
  if (file) /* if the file is opened successfully            */
  {
   while (fgets(buffer, LONGEST_WORD, file))
    {
      /* if the word is passed in the dictionary             */
      if(buffer[0] == letter+1) 
      {
        fclose(file);
        return word_count;
      }
      if (buffer[0] == letter)
      {
        word_count++; /* increments word_count                */
      }
      
      if( buffer[0]-32 == letter) /* if uppercase             */
      {
        word_count++;
      }
    }
    

    fclose(file); /* close the file                          */
  }
  else
  {
    return FILE_ERR_OPEN;
  }
  
  return word_count;
}

/******************************************************************************
   Function: word_lengths

Description: Given the filename of a dictionary, count the number of 
             words that have length 1 to count and store them in the 
             array lengths at the appropriate index

     Inputs: dictionary -  a pointer to a character that 
                           holds the name of the file
             lengths    - an array of integers that holds the different
                          word sizes
             count      - interger holding word sizes
             
    Outputs: If the file can't be opened, return FILE_ERR_OPEN, 
             otherwise return FILE_OK.
             
******************************************************************************/
int word_lengths(const char *dictionary, int lengths[], int count)
{
  FILE* file; /*create the file                             */
  int i;  /* iterator                                       */
  char buffer[LONGEST_WORD]; /* holds the string            */
  int word_length = 0;
  int word_count;
  

  
  file = fopen(dictionary, "r");
 
  if (file)
  {
   while (fgets(buffer, LONGEST_WORD, file))
    {
      mystrupr(buffer); /* make buffer uppercase                  */
      word_length = mystrlen(buffer); /* length of the string     */
      word_count = 0; /* resets word count for each line          */

      /* every size in count                                      */
      for (i = 1; i <= count + 1; i++)
      {
        if (word_length == i) /* if the length is equal to count  */
        {
          word_count++; /* increments word_count                  */
          lengths[i-1] += word_count; /* add word count to lenght */
        }
      }
      
    }
    fclose(file); /* close file                                   */
  }
  else
  {
    return FILE_ERR_OPEN;
  }
  
  return FILE_OK;
}



/******************************************************************************
   Function: count_tabs

Description: Given the filename of a dictionary, return some information 
             about it (using the DICTIONARY_INFO structure).

     Inputs: dictionary -  a pointer to a character that 
                        holds the name of file
              dinfo     - a pointer to a DICTIONARY_INFO structure
             
    Outputs: If the file can't be opened, return FILE_ERR_OPEN, otherwise 
             return FILE_OK.
             
******************************************************************************/
int info(const char *dictionary, struct DICTIONARY_INFO *dinfo)
{
  FILE* file; /* create the file                             */
  char buffer[LONGEST_WORD]; /* holds the string             */
  int lines=0; /* number of lines in file                    */
  int length = 0; /* The length of line                      */
  int new_longest=0; /* longest line in file                 */
  int new_shortest=10; /* shortest line in file              */
  
  file = fopen(dictionary, "r"); /* open the file            */
 
  if (file)
  {
   while (fgets(buffer, LONGEST_WORD, file))
    {
      replace_new_line(buffer); /* replaces new line at the end of string   */
      mystrupr(buffer); /* make buffer all uppercase                        */
      length = mystrlen(buffer);
      
    if (length > new_longest)
    {
      new_longest = length; /* replaces longest line with length if smaller */
    }
    if (length < new_shortest)
    {
      new_shortest = length; /* replaces short line with length if greater  */
    }
    lines++;
    }  
    
    dinfo->count = lines; /* stores line in difo count                      */
    dinfo->shortest = new_shortest; /* stores new_shortest in difo shortest */
    dinfo->longest = new_longest; /* stores new_longest in difo longest     */
  }
  else
  {
    return FILE_ERR_OPEN;
  }
  
  fclose(file); /* close file                                                */
  return FILE_OK;
}


/******************************************************************************
   Function: spell_check

Description: Given the filename of a dictionary and a word, lookup the 
             word in the dictionary. 

     Inputs: dictionary -  a pointer to a character that 
                        holds the sentence to be analyzed
             word       - a pointer to a character that holds the
                          word to be analyzed
             
    Outputs: If the word was found, return WORD_OK. 
             If the word was not found, return WORD_BAD. 
             If the dictionary file can't be opened, return 
             FILE_ERR_OPEN.
             
******************************************************************************/

int spell_check(const char *dictionary, const char *word)
{
  FILE* file; /* create file                                                        */
  int i; /* index of word in dictionary                                             */
  char buffer[LONGEST_WORD]; /* holds the string                                    */
  int match; /* bolean thatg checks if word is found                                */
  char curr_word[LONGEST_WORD] = {0}; /* holds the current word in the dictionary   */
  file = fopen(dictionary, "r");
  
  
  strcat(curr_word, word); /* adds the word to current word array                   */
  if (file)
  {
   while (fgets(buffer, LONGEST_WORD, file))
    {
        match = 1; /* match is true                                                    */
        replace_new_line(buffer);
        mystrupr(buffer);
        mystrupr(curr_word);
        /* if the word in buffer is as long as the word being tested                   */
        if(mystrlen(buffer) == mystrlen(curr_word)) 
        {
          /* if the word is passed in the dictionary                                   */
           if ( buffer[0] == curr_word[0] + 1 )
           {
             match = 0; 
             return WORD_BAD;
           }
          for (i = 0; i < mystrlen(buffer); i++)
          {
            /* if the words do not math                                                  */
            if(buffer[i] != *(curr_word+i))
            {
              match = 0;/* match is false                                                 */
            }
         }
        }
        else
        {
            match = 0;
        }
        
        if(match)
        {
          fclose(file);
          return WORD_OK;
        }
    } 
  }
  else
  {
    return FILE_ERR_OPEN;
  }
  fclose(file);
  return WORD_BAD;
}
