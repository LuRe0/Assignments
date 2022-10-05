#include "fuse.h"
#include <stdio.h>    /* fopen/fclose/fread/fwrite */
#include <stdlib.h>   /* malloc/free */
#include <string.h>   /* strlen */

#define xDEBUG

static void addSpace(char* buffer)
{
	int length = strlen(buffer);

	*(buffer + length) = '\0';

}


int fuse( char const ** filenames, int num_files, char const * output)
{
  int BUFFER_SIZE = 1<<16; /* 65 Kb */

  FILE* inputFile = NULL;
  FILE* outputFile = NULL;
  char* buffer = NULL;
  int size = 0;
  int bytes = 0;
  int i = 0;
  outputFile = fopen(output, "wb");


  for (i = 0; i < num_files; ++i)
  {	  
	  if (filenames[i])
	  {
		  inputFile = fopen(filenames[i], "rb");

		  if (inputFile && outputFile)
		  {
			int capacity = strlen(filenames[i]);

			buffer = (char*)calloc(BUFFER_SIZE, sizeof(char));
			strncpy(buffer, filenames[i], capacity);
			addSpace(buffer);
			fwrite(buffer, sizeof(char), capacity+1, outputFile);
			do {
	
				if (bytes >= BUFFER_SIZE)
				{
					BUFFER_SIZE *= 2;
					buffer = (char*)realloc(buffer, BUFFER_SIZE);
				}
				size = fread(buffer + bytes, sizeof(char), BUFFER_SIZE - bytes, inputFile);

				bytes += size;
			} while (size > 0);

			fwrite(&bytes, sizeof(int), 1, outputFile);

			fwrite(buffer, sizeof(char), bytes, outputFile);
		  }

		  free(buffer);
		  buffer = NULL;
		  bytes = 0;
		  fclose(inputFile);
	  }
  }

  fclose(outputFile);

  return 0;
}

int unfuse( char const * filename  )
{
	FILE* inputFile = NULL;
	FILE* outputFile = NULL;
	char* buffer = NULL;
	int bytes = 0;
	int i = 0;

	if (filename)
	{
		inputFile = fopen(filename, "rb");

		if (inputFile)
		{
			while (!feof(inputFile))
			{
				char nameChar = '\0';
				buffer = (char*)calloc(256, sizeof(char));
				if (buffer)
				{

		
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
							outputFile = fopen(buffer, "wb");
						}
					if (outputFile)
					{
						free(buffer);
						

						fread(&bytes, sizeof(int), 1, inputFile);

						buffer = (char*)calloc(bytes, sizeof(char));

						fread(buffer, sizeof(char), bytes, inputFile);

						fwrite(buffer, sizeof(char), bytes, outputFile);

					}
					if (outputFile)
					{
						fclose(outputFile);
						outputFile = NULL;
					}
					if (buffer != NULL)
					{
						free(buffer);
						buffer = NULL;
					}

					bytes = 0;
				}
			}
			if (inputFile)
			{
				fclose(inputFile);
				inputFile = NULL;
			}
		}
	}

	return 0;
}
