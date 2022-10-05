/******************************************************************************
filename    dumpit.c
author      Anthon Reid
DP email    anthon.reid@digipen.edu
course      CS120
section     A
lab week    11
due date    12/25/2025

Brief Description:
  This program, given an array of characters, formats
  the characters as a line of
  hexadecimal numbers, including file offset and ASCII letters and
  reads in the bytes and prints their hexadecimal values to the screen.
  
******************************************************************************/

#include <stdio.h>  /* <put function names here> */
#include <string.h> /* <put function names here> */

/* Longest formatted line is 75 characters */
#define MAXLEN 75

/* Example: (This example has Unix end-of-line character: 0x0A)
 *
 *  If inbuf contains the first 16 characters from the poem.txt file and outbuf
 *  is an empty array large enough to hold the formatted string, this is how 
 *  you would call the format function:
 *   
 *     format(inbuf, outbuf, 16, 0);
 *  
 *  and this is what outbuf would contain when it returned:
 *  
 * 000000 52 6F 73 65 73 20 61 72  65 20 72 65 64 2E 0A 56   Roses are red..V
 *
 *
 *  The second 16 bytes would be formatted like this:
 *
 *     format(inbuf, outbuf, 16, 16);
 *
 *  and outbuf would look like this:
 *
 * 000010 69 6F 6C 65 74 73 20 61  72 65 20 62 6C 75 65 2E   iolets are blue.
 *
 */
 
/*******************************************************************************
   Function: format

Description: Given an array of characters, format the characters as a line of
             hexadecimal numbers, including file offset and ASCII letters. Only
             the printable ASCII characters are displayed. Non-printable 
             characters are displayed as a period. The file offset is shown
             as a hexadecimal number.

     Inputs:  inbuf - The array of characters to format.
             outbuf - The formatted array, including offset and ASCII letters. 
              count - The number of characters in the input array.
             offset - The value of the 6-digit offset.

    Outputs: None. However, the outbuf parameter has been modified for the
             client.
*******************************************************************************/
void format(const char* inbuf, char *outbuf, int count, int offset)
{
  int i;  /* loop variable */
  char buffer[16];
    /* e.g. 000010 */
   sprintf(outbuf, "%06X ", (unsigned int)offset);

   /* e.g. 52 6F 73 65 73 20 61 72  65 20 72 65 64 2E 0A 56 */
  for (i = 0; i < count; i++)
  {
    /* Format each byte as a hex number using sprintf              */  
    sprintf(buffer, "%02X ", (unsigned char)*(inbuf+i));
    /* Add the hex number to the end of buffer using strcat        */  
    strcat(outbuf, buffer);
    /* Don't forget the extra space between the 8th and 9th number */     
    if (i == 7)
    {
      strcat (outbuf, " ");
    }
    
       if (i == 15)
    {
      strcat (outbuf, "  ");
    }
    
  }
   strcat (outbuf, "\0");
  while((int)strlen(outbuf) < MAXLEN - 17)
  {
    strcat(outbuf, " ");
  }
  
  for (i = 0; i < count; i++)
  {
   
    if((*(inbuf+i) > 31 && *(inbuf+i) < 127) || (*(inbuf+i) == ' '))
    {
      sprintf(buffer, "%c", (unsigned char)*(inbuf+i));
      strcat(outbuf, buffer);
    }
    else
    { 
      sprintf(buffer, ".");
      strcat(outbuf, buffer);
    }
 }

  /* If you didn't get 16 characters, you have to add extra spaces */  

  /* Using another loop, append the ASCII representation of the characters */  
}

/*******************************************************************************
   Function: dump

Description: Given a filename, read in the bytes and print their hexadecimal
             values to the screen. If the character is printable, print the
             character as well.
             
     Inputs: filename - The name of the file to dump in hex.

    Outputs: N/A
*******************************************************************************/
void dump(const char *filename)
{
    /* Variable declarations */
    FILE* file;
    int size = 0;
    char buffer[16];
    char string[MAXLEN];
    int offset = 0;
    /* Open the file for read/binary, "rb"  (Text mode will not work) */
    file = fopen(filename, "rb");
    /* If the file couldn't be opened, print error message and return */
  if(file)
  {
    /* Print the filename to the screen followed by a colon */
    printf("\n%s:\n", filename);
    /* Print the first header line (offsets in hexadecimal) */
    printf("       00 01 02 03 04 05 06 07  08 09 0A 0B 0C 0D 0E 0F\n");
    /* Print the second header line (dashes)                */
    printf("------------------------------------------------------%s",
     "--------------------\n");
    size = fread(buffer, 1, 16, file);
    /* For all bytes in the file */
    while (size)
    {
    /* Read in bytes (16 at a time) using fread     */

    /* Format bytes using the format function above */
      format(buffer, string, size, offset); 
    /* Print formatted string using printf or puts  */
      printf("%s\n",string);
      offset += size;
      size = fread(buffer, 1, 16, file);
    }
  }
    else
    {
      printf("Can't open %s for binary read.\n", filename);
    }
    Si


    /* Close the file */
    fclose(file);
}
