#include <stdio.h> /* printf      */
#include <math.h>  /* sqrt        */
#include "sieve.h" /* TRUE, FALSE */

void sieve(int array[], int size)
{
  int i;
  int j;
  int k;
  for(k =0; k < size; k++)
  {
    array[k] = TRUE;
  }
  
   array[0] = FALSE;
   array[1] = FALSE;
  
  for (i = 2; i < sqrt(size); i++)
  {
    for(j = (i*2); j < size; j+= i)
    {
      if(j % i == 0)
      {
      array[j] = FALSE;
      }
    }
  }
}

int twin_primes(const int primes[], int size)
{
  int i;
  int k = 0;
  for (i =3; i <= size; i++)
  {
      if(primes[i] == TRUE && primes[i + 2] == TRUE)
      {
        k++;
        printf("twin prime #%4i: %4i and %4i\n", k, i, i + 2);
      } 
  }
   return k;
}

double brun_constant(const int primes[], int size)
{
  int i;
  double constant = 0;
  for (i = 3; i <= size; i++)
  {
    if (primes[i] == TRUE && primes[i + 2] == TRUE)
    {
      constant += ((1/(double)i) + (1/((double)i+2)));
    }
  }
  return constant;
}

