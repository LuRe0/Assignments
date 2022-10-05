/******************************************************************************
filename    primes1.c
author      Anthon Reid
DP email    anthon.reid@digipen.edu
course      CS120
section     A
lab week    6
due date    10/23/2021

Brief Description:
  This program checks for prime numbers and 
  determines the sum of two prime numbers
  
******************************************************************************/
#include <stdio.h> /* printf */

  /* For easier readability */
#define FALSE 0
#define TRUE  1

/* Add a proper function header comment */
int is_prime(int number)
{
   int i;
   if ((number == 1) || (number % 2 == 0 && number != 2))
  {
    return FALSE;
  }
  
  for (i = 3; i < number/2; i+=2)
  {
    if (number % i == 0)
    {
      return FALSE;
    }
  }
      return TRUE;
}

/* Add a proper function header comment */
void conjecture(int low, int high)
{
    int sum;
    int first_prime;
    int second_prime;
    int prime_found = 0;
  for( sum = 4; sum <= high; sum += 2)
    {
    for( first_prime = low; first_prime <= high &&
           !prime_found; first_prime++ )
      {
        if (is_prime(first_prime))
        {
          for ( second_prime = low; second_prime <= high &&
                !prime_found; second_prime++)
          {
            if (is_prime(second_prime))
            {
             if((first_prime + second_prime) == sum)
             {
               printf("%3i = %3i + %3i\n", sum,
                     first_prime, second_prime);
              prime_found = 1;
             }
            }
          if (prime_found)
          {
            break;
           }
        }
      }
      if (prime_found)
       {
       break;
      }
        
    }
    prime_found = 0;
  }
}
