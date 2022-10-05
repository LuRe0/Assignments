#include <stdio.h>  /* printf              */
#include <string.h> /* strlen              */
#include <stdlib.h> /* atoi                */
#include <time.h>   /* time                */
#include "PRNG.h"   /* RandomInt, ut_srand */

/* Prototypes */
const char *find_byte(const char *from, const char *to, char byte);
const char *find_any_byte(const char *from, const char *to, const char *bytes, int count);
int count_bytes(const char *from, const char *to, char byte);
int count_any_bytes(const char *from, const char *to, const char *bytes, int count);
int compare_bytes(const char *location1, const char *location2, int count);
void exchange_bytes(char *location1, char *location2, int count);
void copy_bytes(char *from, char *to, int count);

void test1(void)
{
  const char *string = "abcdefghijklmnopqrstuvwxyz";
  int length = strlen(string);
  const char *bytes = "aimzX1";
  const char *found;

  printf("============ test1 ============\n");
  printf("01234567890123456789012345\n");
  printf("%s\n", string);

  while (*bytes)
  {
    found = find_byte(string, string + length, *bytes);
    if (found)
      printf("Found '%c' at offset %li\n", *bytes, (long int)(found - string));
    else
      printf("Didn't find byte: %c\n", *bytes);

    bytes++;
  }

  found = find_byte(string + 10, string + 20, 'z');
  if (found)
    printf("Found z at offset %li\n", (long int)(found - string));
  else
    printf("Didn't find z\n");

  found = find_byte(string + 10, string + 20, 'p');
  if (found)
    printf("Found p at offset %li\n", (long int)(found - string));
  else
    printf("Didn't find p\n");

  found = find_byte(string, string, 'a');
  if (found)
    printf("Found a at offset %li\n", (long int)(found - string));
  else
    printf("Didn't find a\n");

  found = find_byte(string, string, 'b');
  if (found)
    printf("Found b at offset %li\n", (long int)(found - string));
  else
    printf("Didn't find b\n");
}

void test2(void)
{
  const char *string = "There's a fine line between clever and stupid.";
  int length = strlen(string);
  const char *bytes = "gjkqxyz";
  const char *found;

  printf("============ test2 ============\n");
  printf("012345678901234567890123456789012345678901234567890\n");
  printf("%s\n", string);

  found = find_any_byte(string, string + length, bytes, strlen(bytes));
  if (found)
    printf("Found '%c' at offset %li\n", *found, (long int)(found - string));
  else
    printf("Didn't find any bytes: %s\n", bytes);

  bytes = "gjkqxybz";
  found = find_any_byte(string, string + length, bytes, strlen(bytes));
  if (found)
    printf("Found '%c' at offset %li\n", *found, (long int)(found - string));
  else
    printf("Didn't find any bytes: %s\n", bytes);

}

void test3(void)
{
  const char *string = "There's a fine line between clever and stupid.";
  int length = strlen(string);
  const char *bytes = "aeiou";

  printf("============ test3 ============\n");
  printf("012345678901234567890123456789012345678901234567890\n");
  printf("%s\n", string);

  while (*bytes)
  {
    int count = count_bytes(string, string + length, *bytes);
    printf("Found %i occurrences of '%c'\n", count, *bytes);    
    bytes++;
  }
}

void test4(void)
{
  const char *string = "There's a fine line between clever and stupid.";
  int length = strlen(string);
  const char *bytes = "aeiou";
  int count;

  printf("============ test4 ============\n");
  printf("012345678901234567890123456789012345678901234567890\n");
  printf("%s\n", string);

  count = count_any_bytes(string, string + length, bytes, strlen(bytes));
  printf("Found %i occurrences from the set '%s'\n", count, bytes);
}

void scanner(const char *loc1, const char *loc2, int count)
{
  int result;
  int i;
  const char *bytes;

  bytes = loc1;
  for (i = 0; i < count; i++)
    printf("%c", *bytes++);
  printf("\n");

  bytes = loc2;
  for (i = 0; i < count; i++)
    printf("%c", *bytes++);
  printf("\n");
  
 result = compare_bytes(loc1, loc2, count);

  if (result == 0)
    printf("The bytes are the same.\n");
  else if (result < 0)
    printf("The first bytes are less than the second bytes.\n");
  else
    printf("The first bytes are greater than the second bytes.\n");
}

void test5(void)
{
  /*                    0123456789012345678901234567890 */
  const char *bytes1 = "abccefghijklmnopqrstuvwxyzxxxxx";
  const char *bytes2 = "abcdefxxxxxghijklpqwxyzabcdefxx";

  printf("============ test5 ============\n");

  scanner(bytes1, bytes2, 3);
  scanner(bytes1, bytes2, 4);
  scanner(bytes1 + 12, bytes2 + 11, 6);
  scanner(bytes1 + 22, bytes2 + 14, 4);
  scanner(bytes1 + 10, bytes2 + 15, 1);
  scanner(bytes1 +  6, bytes2 + 11, 6);

  while (*bytes1 && *bytes2)
    scanner(bytes1++, bytes2++, 1);
}

void test6(void)
{
  /*               0123456789.123456789.123456789.  */
  /*                         1         2            */
  char string[] = "Four score and seven years ago.";

  printf("============ test6 ============\n");

  printf("BEFORE: %s\n", string);
  exchange_bytes(string + 5, string + 15, 5);
  printf(" AFTER: %s\n", string);
  exchange_bytes(string + 0, string + 27, 4);
  printf(" AFTER: %s\n", string);
  exchange_bytes(string + 7, string + 19, 9);
  printf(" AFTER: %s\n", string);
}

void test7(void)
{
  char string[] = "Any sufficiently advanced technology is indistinguishable from magic.";
  int length = strlen(string);
  int maxsize = length / 3; 
  int count = 100;
  int i;

  #define MAX_EXCHANGES 1000
  int sizes[MAX_EXCHANGES];
  int loffsets[MAX_EXCHANGES];
  int roffsets[MAX_EXCHANGES];

  printf("============ test7 ============\n");
  printf("%s\n", string);
  for (i = 0; i < count; i++)
  {
    int size = RandomInt(1, maxsize);
    int loffset = RandomInt(0, length - 2 * maxsize);

    int roffset = RandomInt(loffset + size, length - maxsize);
    exchange_bytes(string + loffset, string + roffset, size);
    printf("%s\n", string);
    sizes[i] = size;
    loffsets[i] = loffset;
    roffsets[i] = roffset;
  }

  printf("*********************************************************************\n");

  for (i = count - 1; i >= 0; i--)
  {
    exchange_bytes(string + loffsets[i], string + roffsets[i], sizes[i]);
    printf("%s\n", string);
  }
}

void test8(void)
{
  /*               01234567890123456789012345 */
  char string1[] = "abcdefghijklmnopqrstuvwxyz";

  char string2[] = 
  /*           1         2         3         4         5         6        */
  /* 012345678901234567890123456789012345678901234567890123456789012345678*/
    "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

  printf("============ test8 ============\n");

  printf("01234567890123456789012345\n");
  printf("%s\n", string1);

  copy_bytes(string1 + 6, string1 + 11, 10);
  printf("%s\n", string1);

  copy_bytes(string1 + 2, string1 + 5, 15);
  printf("%s\n", string1);


  printf("          1         2         3         4         5         6        \n");
  printf("012345678901234567890123456789012345678901234567890123456789012345678\n");
  printf("%s\n", string2);

  copy_bytes(string2 + 6, string2 + 11, 9);
  printf("%s\n", string2);

  copy_bytes(string2 + 3, string2 + 19, 30);
  printf("%s\n", string2);

  copy_bytes(string2 + 30, string2 + 35, 22);
  printf("%s\n", string2);

  copy_bytes(string2 + 1, string2 + 2, 3);
  printf("%s\n", string2);
}

void testX(void)
{
  char string1[] = "There's a fine line between clever and stupid.";
  const char *string2 = "abcdefghijklm";
  const char *string3 = "abcdehijklmno";
  int length = strlen(string1);
  const char *found;
  const char *bytes;
  int count;

  /* Finds 'b' in the range 'fine line between' and returns a pointer to it */
  found = find_byte(string1 + 10, string1 + 26, 'b');
  printf("Found %c at offset %li\n", *found, (long int)(found - string1));

  /* Doesn't find 'z' in the range 'There's a fi' and returns NULL */
  found = find_byte(string1, string1 + 11, 'z');

  /*
   * Finds the 'l' in the entire range of characters and returns pointer to it.     
   * It first looks for x, then y, then z, and then l. It stops after finding 
   * the l, and doesn't look for a, b, or c.                                  
   */
  bytes = "xyzlabc";
  found = find_any_byte(string1, string1 + length, bytes, 7);
  printf("Found %c at offset %li\n", *found, (long int)(found - string1));

  /* Returns 3, the number of time 'e' is in range 'There's a fine '  */
  count = count_bytes(string1, string1 + 15, 'e');
  printf("count is %i\n", count);

  /* Returns 15, the number of times a vowel appears in the entire string  */
  bytes = "aeiou";
  count = count_any_bytes(string1, string1 + length, bytes, 5);
  printf("count is %i\n", count);

  /* Returns 0 as the ranges 'abcde' and 'abcde' are the same */
  count = compare_bytes(string2, string3, 5);
  printf("count is %i\n", count);

  /* Returns negative number as 'abcdef' is less than 'abcdeh' */
  count = compare_bytes(string2, string3, 6);
  printf("count is %i\n", count);

  /* Returns positive number as 'bcd' is greater than 'abc' */
  count = compare_bytes(string2 + 1, string3, 3);
  printf("count is %i\n", count);

  /* Returns 0 as the ranges 'jklm' and 'jklm' are the same */
  count = compare_bytes(string2 + 9, string3 + 7, 4);
  printf("count is %i\n", count);

  /* Changes string to "There's a line fine between clever and stupid." */
  exchange_bytes(string1 + 10, string1 + 15, 4);
  printf("%s\n", string1);

  /* Changes string to "There's a line fine between stupid and clever." */
  exchange_bytes(string1 + 28, string1 + 39, 6);
  printf("%s\n", string1);

  /* Changes string to "There's a line line fine between stand clever." */
  copy_bytes(string1 + 10, string1 + 15, 20);
  printf("%s\n", string1);
}

int main(int argc, char **argv)
{
  typedef void (*Test)(void);
  Test tests[] = {test1, test2, test3, test4, test5, test6, test7, test8};
  int count = sizeof(tests) / sizeof(*tests);
  int testno = 0;
  int i;

  ut_srand(3, 4);

  if (argc > 1)
    testno = atoi(argv[1]);

 if (testno > count)
   testno = 0;

  if (testno == 0)
  {
    for (i = 0; i < count; i++)
      tests[i]();
  }
  else
    tests[testno - 1]();

  return 0;
}
