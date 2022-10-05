
/******************************************************************************
filename    dates.c
author      Anthon Reid
DP email    anthon.reid@digipen.edu
course      CS120
section     A
lab week    4
due date    10/09/2021

Brief Description:
  This program compares two sets of dates 
  and determines which comes first.
  
******************************************************************************/
#include <stdio.h>


  
int main(void)
{
  /* 1. Declare the necessary variables.                                 */
  int first_month;
  int first_day;
  int first_year;
  int second_month;
  int second_day;
  int second_year; 
  /* 2. Display the prompt and accept the user input (first date).       */
  printf("Enter the first date: (mm/dd/yyyy) ");
  scanf("%d/%d/%d",&first_month,&first_day,&first_year);
  /* 3. Display the prompt and accept the user input (second date).      */
  printf("Enter the second date: (mm/dd/yyyy) ");
  scanf("%d/%d/%d",&second_month,&second_day,&second_year);
  /* 4. Figure out which date comes first and print appropriate message. */

/* Checks which year comes first regardless of day or month */  
if (first_year != second_year 
    && first_month != second_month 
    && first_day != second_day)
{
  if(first_year < second_year)
  {
    printf("%2.2d/%2.2d/%2.2d comes before %2.2d/%2.2d/%2.2d.\n",
    first_month,first_day,first_year,
    second_month,second_day,second_year );
  }
  else if (first_year > second_year)
  {
    printf("%2.2d/%2.2d/%2.2d comes after %2.2d/%2.2d/%2.2d.\n",
    first_month,first_day,first_year,
    second_month,second_day,second_year);
  }
}

if (first_year != second_year 
    && first_month == second_month 
    && first_day != second_day)
{
  if(first_year < second_year)
  {
    printf("%2.2d/%2.2d/%2.2d comes before %2.2d/%2.2d/%2.2d.\n",
    first_month,first_day,first_year,
    second_month,second_day,second_year);
  }
  else if (first_year > second_year)
  {
    printf("%2.2d/%2.2d/%2.2d comes after %2.2d/%2.2d/%2.2d.\n",
    first_month,first_day,first_year,
    second_month,second_day,second_year);
  }
}

if (first_year != second_year 
    && first_month != second_month 
    && first_day == second_day)
{
  if(first_year < second_year)
  {
    printf("%2.2d/%2.2d/%2.2d comes before %2.2d/%2.2d/%2.2d.\n",
    first_month,first_day,first_year,
    second_month,second_day,second_year);
  }
  else if (first_year > second_year)
  {
    printf("%2.2d/%2.2d/%2.2d comes after %2.2d/%2.2d/%2.2d.\n",
    first_month,first_day,first_year,
    second_month,second_day,second_year);
  }
}

if (first_year != second_year 
    && first_month == second_month 
    && first_day == second_day)
{
  if(first_year < second_year)
  {
    printf("%2.2d/%2.2d/%2.2d comes before %2.2d/%2.2d/%2.2d.\n",
    first_month,first_day,first_year,
    second_month,second_day,second_year );
  }
  else if (first_year > second_year)
  {
    printf("%2.2d/%2.2d/%2.2d comes after %2.2d/%2.2d/%2.2d.\n",
    first_month,first_day,first_year,
    second_month,second_day,second_year);
  }
}

/* Checks which month comes first while the years or days are equal */  
if (first_year == second_year
    && first_month != second_month
    && first_day != second_day)
{
  if(first_month < second_month)
  {
    printf("%2.2d/%2.2d/%2.2d comes before %2.2d/%2.2d/%2.2d.\n",
    first_month,first_day,first_year,
    second_month,second_day,second_year );
  }
  else if (first_month > second_month)
  {
    printf("%2.2d/%2.2d/%2.2d comes after %2.2d/%2.2d/%2.2d.\n",
    first_month,first_day,first_year,
    second_month,second_day,second_year);
  }
}

if (first_year == second_year
    && first_month != second_month
    && first_day == second_day)
{
  if(first_month < second_month)
  {
    printf("%2.2d/%2.2d/%2.2d comes before %2.2d/%2.2d/%2.2d.\n",
    first_month,first_day,first_year,
    second_month,second_day,second_year);
  }
  else if (first_month > second_month)
  {
    printf("%2.2d/%2.2d/%2.2d comes after %2.2d/%2.2d/%2.2d.\n",
    first_month,first_day,first_year,
    second_month,second_day,second_year);
  }
}


/* Checks which day comes first while the years and months are equal */ 
if (first_year == second_year
    && first_month == second_month
    && first_day != second_day)
{
  if(first_day < second_day)
  {
    printf("%2.2d/%2.2d/%2.2d comes before %2.2d/%2.2d/%2.2d.\n",
    first_month,first_day,first_year,
    second_month,second_day,second_year);
  }
  else if (first_day > second_day)
  {
    printf("%2.2d/%2.2d/%2.2d comes after %2.2d/%2.2d/%2.2d.\n",
    first_month,first_day,first_year,
    second_month,second_day,second_year);
  }
}

/* Checks which month, days and years are equal */ 
if(first_year == second_year
   && first_month == second_month 
   && first_day == second_day)
{
  printf("%2.2d/%2.2d/%2.2d and %2.2d/%2.2d/%2.2d are the same date.\n",
  first_month,first_day,first_year,
  second_month,second_day,second_year);   
}


  return 0; /* Return success to the OS. */
}
