/*******************************************************************************
filename    driver-stress.c
author      Artie Fufkin
DP email    afufkin2@digipen.edu
course      CS120
assignment  15
due date    12/24/2046

Brief Description:
  This file contains the stress-test functions for the scan text program.

*******************************************************************************/
#include <stdio.h>  /* printf, fopen, fgets, fclose */
#include <stdlib.h> /* calloc, free                 */
#include <string.h> /* strcat, strlen               */

/* Prototypes */
int count_words(const char *string);
int count_tabs(const char *string);
int substitute_char(char *string, char old_char, char new_char);
void calculate_lengths(const char *string, int tabsize, int *string_length, 
                       int *display_length);

#define MAX_LINE_LENGTH 200

int mystrlen(const char *string)
{
  int length = 0;
  while (*string++)
    length++;

  printf("This should not be called.\n");
  return length;
}

void test1(void)
{
  const char *filename = "decl80j-lf.txt"; /* For Windows, decl80j-crlf.txt */
  char *string;
  int count;
  FILE *fp;

  string = calloc(20000, sizeof(char)); /* The file is 10,034 bytes    */
  if (!string)
  {
    printf("calloc failed\n");
    return;
  }
  
  fp = fopen(filename, "r");
  if (!fp)
  {
    printf("Can't open %s for read/text.\n", filename);
    free(string);
    return;
  }

  printf("Reading...\n");
  while (!feof(fp))
  {
    char buffer[MAX_LINE_LENGTH]; /* Lines in this file are 80 chars max */
    if (!fgets(buffer, MAX_LINE_LENGTH, fp))
      break;

    strcat(string, buffer);
  }

  fclose(fp);

  printf("\n== test1 ======================================================\n");
  /*printf("|%s|\n", string);*/
  count = count_words(string);
  printf("Word count is %i\n", count);
  free(string);
}

void test2(void)
{
  const char *filename = "big100-lf.txt"; /* For Windows, big100-crlf.txt */
  char *string;
  int count;
  FILE *fp;

  string = calloc(1000 * 1000 * 8, sizeof(char)); /* The file is about 6 MBs */
  if (!string)
  {
    printf("calloc failed\n");
    return;
  }
  
  fp = fopen(filename, "r");
  if (!fp)
  {
    printf("Can't open %s for read/text.\n", filename);
    free(string);
    return;
  }

  printf("Reading...\n");
  while (!feof(fp))
  {
    char buffer[MAX_LINE_LENGTH]; /* Lines in this file are 100 chars max */
    if (!fgets(buffer, MAX_LINE_LENGTH, fp))
      break;

    strcat(string, buffer);
  }

  fclose(fp);

  printf("\n== test2 ======================================================\n");
  count = count_words(string);
  printf("Word count is %i\n", count);
  free(string);
}

int main(void)
{
  test1(); /* Word count is 1499   */
  /*test2();*/ /* Word count is 991170 */

  return 0;
}
