#include <stdio.h>

#define TRUE  1
#define FALSE 0

 int is_leapyear(int year)
{
  if((year % 4 == 0 && year % 100 != 0) ||
  (year % 100 == 0 && year % 400 == 0))
  {
   return TRUE;
  }
   return FALSE;
}

int day_of_the_week(int day, int month, int year)
{
  int month_keys[] = {1, 4, 4, 0, 2, 5, 0, 3, 6, 1, 4, 6};
  int year_keys[] = {4, 2, 0, 6};
  int last_digits = year % 100;
  int week_day;

  
  week_day = last_digits / 4;
  week_day += day;
  week_day += month_keys[month - 1];
  
   while(year > 2099)
  {
   year -= 400;
  }
  
  if ((month == 1 || month == 2) && is_leapyear(year))
  {
   week_day -= 1;  
  }
  
  if (year >= 1700 && year <= 1799)
  {
    week_day += year_keys[0];
  }
  if (year >= 1800 && year <= 1899)
  {
    week_day += year_keys[1];
  }
  if (year >= 1900 && year <= 1999)
  {
    week_day += year_keys[2];
  }
  if (year >= 2000 && year <= 2099)
  {
    week_day += year_keys[3];
  }
  week_day += last_digits;
  week_day = week_day % 7; 
  
  if (week_day == 0)
  {
   week_day = 7;
  }

  return week_day;
}


void print_calendar(int month, int year)
{
  int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  char *months[] = {"January",   "February", "March",    "April", 
                    "May",       "June",     "July",     "August",
                    "September", "October",  "November", "December"};
  int i;
  int j;
  
  int current_week = 1;
  int extras = day_of_the_week(1, month, year) - 1;
 


  printf("%s, %i\n", months[month - 1], year);
  printf("Su Mo Tu We Th Fr Sa\n");
  printf("---------------------\n");
  
  if(is_leapyear(year) == TRUE && month == 2 )
  {
    days_in_month[1] = 29;
  }
  
  for(i = 1; i < day_of_the_week(1, month, year) ; i++)
  {
   printf("   ");
  }
   for(j = 1; j <= days_in_month[month - 1]; j++)
  {
      if(j - 1 == 7 * current_week - extras)
      {
        printf("\n");
        current_week++;
      }
      
      printf("%2i ",j);
  }  
  
  printf("\n");
  
} 


