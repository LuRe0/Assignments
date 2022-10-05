/******************************************************************************
filename    bytes.c
author      Anthon Reid
DP email    anthon.reid@digipen.edu
course      CS120
section     A
Lab Week    9
due date    11/13/2021

Brief Description:
  This program scans through bytes and finds, counts, compares, exchange
  or copies them.
  
******************************************************************************/

#include <stdio.h>     /* printf      */
#include <ctype.h>     /* toupper     */
#include <string.h>    /* strlen      */
#include "histogram.h" /* lab defines */

int GetCounts(const char *sentence, int letters[], int *spaces, int *other)
{
int i = 0; /* iterator    */
int j = 0;
int count = 0; /*  The count of individual characters is in the letters array */
int temp = 0; /* Temp storage of sentence value */
int lenght = strlen (sentence);
*spaces = 0;
*other = 0;

for (j = 0; j < NUM_LETTERS; ++j)
{
  letters[j] = 0;
}

for (i = 1; i <= lenght; ++i)
{
   temp = *((sentence + lenght) - i);
   
   temp = toupper(temp);
   
   
     if (temp == SPACE)
   {
     *(spaces) += 1;
   }
   else if(temp >= 'A' && temp <= 'Z')
   {
    letters[temp - 'A'] += 1;
    count++;
   }
   else 
   {
    *other += 1;
   }
  }
  return count;
}

void PrintHistogram(const int letters[])
{
int i = 0;
int j  = 0;
int count = 0;

  for (i = 0; i < NUM_LETTERS; ++i)
  {
    count = letters[i];
    
    printf("%c:", i + 'A');

    for (j = 0; j < count; j++)
    {
      printf("*");
    }
    
    printf("\n");
  }
}

void GetStatistics(const int letters[], double *average, char *max_letter, 
                   int *max_count)
{
int i = 0;
int count = 0;
double points = 0;
double total = 0;
*average = 0;
*max_letter =  0;
*max_count = 0;


  for (i = 0; i < NUM_LETTERS; ++i)
  {

count = letters[i];

     
  if(count > *max_count)
  {
   *max_count = count;
   *max_letter = i + 'A';
  }
    
    points = ((i+1)*count);
    total += points;
    *average = total/NUM_LETTERS; 
  }
}

