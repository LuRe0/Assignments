/******************************************************************************/
/*!
\file   fuse.c
\author Dong Ta
\par    email: d.ta@digipen.edu
\par    DigiPen login: d.ta
\par    Course: CS225
\par    Section A
\par    Assignment #1
\date   9/10/2022
\brief  
  This is the implementation file for all functions shown in 
  file fuse.h.  
*/
/******************************************************************************/
#include "fuse.h"
#include <stdio.h>    /* fopen/fclose/fread/fwrite */
#include <stdlib.h>   /* malloc/free */
#include <string.h>   /* strlen */

#define xDEBUG
/*!*****************************************************************************
  \brief
      takes a list of file names, and goes through them, putting their name, 
      size, and content into the designated output file.
  \param filenames
      Array containing names of the files to be fused
  \param num_files
      number indicating how many file names are in the filenames array
  \param output
      the designated output file to be written/fused to
  \return
      0 if no errors occured, or a number coresponding to the error 
*******************************************************************************/
int fuse( char const ** filenames, int num_files, char const * output)
{
  int BUFFER_SIZE = 1<<16; /* 65 Kb */
  int i; /*loop counter*/
  /*make a buffer with the given size to store file conent*/
  char * buffer = malloc(BUFFER_SIZE * sizeof(char));
  int size; /*to store file size later*/
  /*open file*/
  FILE *fileToWrite = fopen(output, "wb");
  FILE *fileToRead;
  if (!fileToWrite)
  { 
    perror( output );
    printf( "File %s cannot be opened for reading\n", output );
    return 1; /* or some other error code */
  }
  else
  { /*loop the the array of filenames if file successfully opened*/
    for (i = 0; i < num_files; ++i)
    {

      fileToRead = fopen(filenames[i], "rb");
      if (fileToRead)
      {
        /*determining file size*/
        fseek(fileToRead, 0, SEEK_END); /* set pointer to end of file*/
        size = ftell(fileToRead); /*check how far pointer moved and set size to it*/
        fseek(fileToRead, 0, SEEK_SET); /* set pointer back to beginning*/

        /*write the filename*/
        fwrite(filenames[i], 1, strlen(filenames[i]) + 1, fileToWrite);
        /*write terminator after filename*/
        /*fwrite("\0", sizeof(char), 1, fileToWrite);*/

        /*write the file size*/
        fwrite(&size, sizeof(int), 1, fileToWrite);

        buffer = realloc(buffer, size);
        /*read in content of buffer*/
        fread(buffer, 1, size, fileToRead);
        /*write the content*/
        fwrite(buffer, 1, size, fileToWrite);


        memset(buffer, '\0', size);
        fclose(fileToRead);
      }
      else
      {
        perror( output );
        printf( "File %s cannot be opened for reading\n", output );
      }

    }
    fclose(fileToWrite);    
    free(buffer);
    return 0;
  }
}
/*!*****************************************************************************
  \brief
      takes a file, and separates the contents into multiple files based on the 
      content
  \param filename
      the file to be unfused
  \return
      0 if no errors occured, or a number coresponding to the error 
*******************************************************************************/
int unfuse( char const * filename )
{
  int BUFFER_SIZE = 1<<16; /* 65 Kb */
  FILE *fileToRead = fopen(filename, "rb");
  /*FILE *fileCounter = fopen(filename, "r");*/ /*for counting data size*/
  FILE *fileToWrite; 
  int sizeCounter; /*counter*/
  char character; /*for fgetc*/
  /*int i;*/ 
  /*char *fileBuffer = malloc(BUFFER_SIZE * sizeof(char));
  char * buffer = malloc(BUFFER_SIZE * sizeof(char));
  memset(fileBuffer, '\0', BUFFER_SIZE);
  memset(buffer, '\0', BUFFER_SIZE);*/
  char *fileBuffer = calloc(BUFFER_SIZE, sizeof(char));
  char *buffer = calloc(BUFFER_SIZE, sizeof(char));
  /*loop while fileToRead pointer is not at end of file*/
  if (fileToRead)
  {

    while (!feof(fileToRead))
    {
      sizeCounter = 0;
      /*i = 0;*/
      /*get file name*/
      while (!feof(fileToRead))
      { 
        /*read the character from the file*/
        character = fgetc(fileToRead);

        if(character == '\0')
          break;

        /*concat the character read into the buffer*/ 
        strcat(fileBuffer, &character);
        /*(buffer + i) = character;
        ++i;*/
      }
      
      /*get the size of the line*/
      fread(&sizeCounter, 1, 4, fileToRead);
      /*make a file with the name*/
      fileToWrite = fopen(fileBuffer, "wb");
      if (fileToWrite)
      {
        /*realloc the buffer*/
        buffer = realloc(buffer, sizeCounter);
  
        /*read in the contents from file-to-read to buffer*/
        fread(buffer, 1, sizeCounter, fileToRead);
        
        /*Write the read data*/
        fwrite(buffer, 1, sizeCounter, fileToWrite);
        /*close the new file after writing*/
        fclose(fileToWrite);
      }
      /*clear both buffers*/
      memset(fileBuffer, '\0', BUFFER_SIZE);
      memset(buffer, '\0',  sizeCounter);
    }
    fclose(fileToRead);
    /*fclose(fileCounter);*/
  }
  free(buffer);
  free(fileBuffer);
  return 0;
}
