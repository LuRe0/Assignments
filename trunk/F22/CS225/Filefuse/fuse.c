/*!
 * @file    fuse.c
 * @author  Anthon Reid
 * @par     email: anthon.reid\@digipen.edu
 * @par     DigiPen login: anthon.reid
 * @par     Course: CS180
 * @par     Section: A
 * @par     Assignment 1
 * @date    2022-09-13
 * @brief 
 *        given a list of files (an array of C-style strings) merge the files into
 *        a SINGLE file and given a merged file be able to extract the original
 *        file.
 */


#include "fuse.h"
#include <stdio.h>    /* fopen/fclose/fread/fwrite */
#include <stdlib.h>   /* malloc/free */
#include <string.h>   /* strlen */

#define xDEBUG

/*!
 * @brief
 *  Brief decription of the function
 *
 * @param filenames
 *  The buffer at the end of which
 *  a nul character will be added
 *
 * @return
 *  return none
 */
static void addNulPtr(char* buffer)
{
    /* The lenght of the buffer                                       */
    int length = strlen(buffer);

    /* Add a nul character at the end of the buffer                   */
    *(buffer + length) = '\0';
}

/*!
 * @brief
 *  This merges the files into a SINGLE file with the following structure:
 *  for each provided file, first save the name of the file, 
 *  then the size of the file, then the file data, repeat as many time as there are files.
 *
 * @param filenames
 *  The array containing the file to be opened
 * 
 * @param num_files
 *  Integer holding the number of files to be read
 *
 *  @param output
 *  Char array holding the name of the destination file.
 * 
 * @return
 *  return 0
 */
int fuse( char const ** filenames, int num_files, char const * output)
{
  int BUFFER_SIZE = 1<<16; /* 65 Kb */


  /* The file pointers                                              */
  FILE* inputFile = NULL;
  FILE* outputFile = NULL;

  /* The buffer to hold the content of the files                    */
  char* buffer = NULL;

  /* The integers to hold the size of the files                     */
  int size = 0;
  int bytes = 0;

  /* iterator for data transfer                                     */
  int i = 0;

  /* Open the file that is to receive the fused information         */
  outputFile = fopen(output, "wb");

 /* Loop that will apply the process for as many files are present  */
  for (i = 0; i < num_files; ++i)
  {	  
      if (filenames[i])
      {
          /* Open the file that is to contains information          */
          inputFile = fopen(filenames[i], "rb");

          if (inputFile && outputFile)
          {
            int capacity = strlen(filenames[i]);

            /* Initializes the buffer, copies the name in the buffer, 
               adds a nul character at its end and writes it to
               the file.                                             */
            buffer = (char*)calloc(BUFFER_SIZE, sizeof(char));
            strncpy(buffer, filenames[i], capacity);
            addNulPtr(buffer);
            fwrite(buffer, sizeof(char), capacity+1, outputFile);


            /* A loop that will repeat so long as there is data to be 
               read from the start.                                  */
            do {
                
                /* if the size of the file is bigger than the buffer,
                   increase the buffer size and realloc the buffer   */
                if (bytes >= BUFFER_SIZE)
                {
                    BUFFER_SIZE *= 2;
                    buffer = (char*)realloc(buffer, BUFFER_SIZE);
                }

                /* read the size of the file and log its total size  */
                size = fread(buffer + bytes, sizeof(char), BUFFER_SIZE - bytes, inputFile);

                bytes += size;
            } while (size > 0);

            /* write the size and the content of the file to the 
               output file                                          */
            fwrite(&bytes, sizeof(int), 1, outputFile);

            fwrite(buffer, sizeof(char), bytes, outputFile);
          }

          /* free the buffer and close the target file              */
          free(buffer);
          buffer = NULL;
          bytes = 0;
          fclose(inputFile);
      }
  }

  /* close the fused file                                           */
  fclose(outputFile);

  return 0;
}


/*!
 * @brief
 *  This reads in the information (name, size and content)
 *  of a file and recreates it.
 *
 * @param filenames
 *  The array containing the name of the fused file.
 * 
 * @return
 *  return 0
 */
int unfuse( char const * filename  )
{
  /* The file pointers                                              */
  FILE* inputFile = NULL;
  FILE* outputFile = NULL;

  /* The buffer to hold the content of the files                    */
  char* buffer = NULL;

  /* The integers to hold the size of the files                     */
  int bytes = 0;


  /* iterator for data transfer                                     */
  int i = 0;

    if (filename)
    {
        /* Open the file that is to contains information            */
        inputFile = fopen(filename, "rb");

        if (inputFile)
        {
            /* loops to the end of the file                         */
            while (!feof(inputFile))
            {

                /* character to hold filename                       */
                char nameChar = '\0';

                /* allocate space for the buffer                    */
                buffer = (char*)calloc(256, sizeof(char));
                if (buffer)
                {

                        /* reads charcters until it reaches EOF or
                           encounters and nul character             */
                        do {
                            nameChar = fgetc(inputFile);
                            if (nameChar == '\0')
                            {
                                buffer[i] = nameChar;
                                i = 0;
                                break;
                            }
                            if (nameChar == EOF)
                            {
                                free(buffer);
                                  buffer = NULL;
                                nameChar = '\0';
                                break;
                            }
                            buffer[i] = nameChar;
                            ++i;

                        } while (nameChar != EOF);

                        if (buffer != NULL)
                        {
                            /* open/create a file with the 
                              retrieved name                          */
                            outputFile = fopen(buffer, "wb");
                        }

                    if (outputFile)
                    {
                        /* free the buffer to prepare for 
                           reallocation                              */
                        free(buffer);
                        

                        /* reads in the size of the information 
                           in the file                               */
                        fread(&bytes, sizeof(int), 1, inputFile);

                        /* reallocate buffer with required size      */
                        buffer = (char*)calloc(bytes, sizeof(char));

                        /* read in the wanted information            */
                        fread(buffer, sizeof(char), bytes, inputFile);
                        
                        /* write it to the output file               */
                        fwrite(buffer, sizeof(char), bytes, outputFile);

                    }
                    /* close the file                                */
                    if (outputFile)
                    {
                        fclose(outputFile);
                        outputFile = NULL;
                    }

                    /* free the buffer                               */
                    if (buffer != NULL)
                    {
                        free(buffer);
                        buffer = NULL;
                    }

                    bytes = 0;
                }
            }

            /* close the initial file                                */
            if (inputFile)
            {
                fclose(inputFile);
                inputFile = NULL;
            }
        }
    }

    return 0;
}
