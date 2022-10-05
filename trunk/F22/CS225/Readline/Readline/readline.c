/*!*****************************************************************************
\file    readline.c
\author  Anthon Reid
\par     DP email:  anthon.reid@digipen.edu
\par     Course: CS170
\par     Lab #1
\date    09-09-2022

\brief
    readline accepts an open file stream and has to read ALL characters from the 
    stream upto not including new line or new line character. The return value
    is a pointer to a C-style string, therefore NULL-terminated. The return 
    string should not have new line character.  

*******************************************************************************/
#include "readline.h"
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_LENGTH 100


static int mystrlen(const char *string)
{
  int length = 0; /* The number of characters in the string */
  
    /* Count the characters (not including the NUL) */  
  while (*string++)
    length++;

  return length;
}

static void replaceNewLine(char *buffer)
{
    int i;
    int length = mystrlen(buffer);
    for (i = 0; i < length; i++)
    { 
        if(buffer[i] == '\n')/*if we encounter a tab       */
        {
            buffer[i] = '\0';
        }

        //if (buffer[mystrlen(buffer) - 1] != '\0')
        //{
        //    buffer[mystrlen(buffer) - 1] = '\0';
        //}
    }
}

/* returns a pointer to an array of character contatining the string */
char * readline( FILE * fp )
{
    int size = 0;
    int readSize = 2;
    int capacity = 2;
    char *buffer = NULL;  
    
    if (fp)
    {
        buffer = (char *) calloc(capacity, sizeof(char));
         
         if (buffer)
         {
            while (fgets(buffer + size, readSize, fp))
            {   

                size = mystrlen(buffer);
                capacity *= 2;     
                readSize = capacity - size;       

                buffer =  (char *)realloc(buffer, capacity);
            }

                replaceNewLine(buffer);

                return buffer;
         }
    }
    
    return NULL;
}
