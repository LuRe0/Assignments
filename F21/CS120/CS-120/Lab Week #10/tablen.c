#include <stdio.h>
#define MAX_LINE_LENGTH 1000

static int mystrlen(const char *string)
{
  int length = 0; /* The number of characters in the string */
  
    /* Count the characters (not including the NUL) */  
  while (*string++)
    length++;

  return length;
}

static void replace_new_line(char *buffer)
{

    *(buffer + mystrlen(buffer) - 1) = '\0';

}


static void check_tabs(FILE* fp, const char* filename)
{
int tabs; /*counts the number of tabs           */
int tabs_in_file = 0;
char buffer[MAX_LINE_LENGTH];
int line = 1;
int i;

 fp = fopen(filename, "r");
  if (fp)
  {
   while (fgets(buffer, MAX_LINE_LENGTH, fp))
    {
      replace_new_line(buffer);
      tabs = 0;
        for (i = 0; i < mystrlen(buffer); i++)
        { 
           if(buffer[i] == '\t')/*if we encounter a tab       */
           {
              tabs++; /* increment count                    */
           } 
        }
        if(tabs > 0)
        {
          printf("#%3i: (tabs:%2i) |%s|\n", line, tabs, buffer);
        }
     line++;
     tabs_in_file += tabs;
    }
    if(tabs_in_file > 0)
    {
     printf("*****  TABS IN USE  *****: Number of tabs in the file is %i.\n", 
            tabs_in_file);
    }
    
    fclose(fp);
  }
   else
  {
   printf("Can't open %s for read.\n", filename);
  }
  
} 

static void count_lines(FILE* fp, const char* filename)
{
char buffer[MAX_LINE_LENGTH];
int current_length = 0;
int new_length = 0;
int line = 1;
int longest_line = 0;
int illegal_line = 0;


 fp = fopen(filename, "r");
  if (fp)
  {
   while (fgets(buffer, MAX_LINE_LENGTH, fp))
    {
     replace_new_line(buffer);
     current_length = mystrlen(buffer);
      if(current_length > 80)
      {
        illegal_line++; 
        printf("#%3i: (%3i) |%s|\n", line, current_length, buffer);
      }
      if (current_length > new_length)
      {
        new_length = current_length;
        longest_line = line;
      }  
      line++;
    }
    
    if(illegal_line > 0)
    {
     printf("%s %i lines longer than 80. Longest line is %i at %i chars.\n",
            "***** LINE TOO LONG *****:",
            illegal_line, longest_line, new_length );
    }
  }
  else
  {
   printf("Can't open %s for read.\n", filename);
  }
    fclose(fp);
}  




void tablen(const char *filename)
{
FILE *fp;
 
  fp = fopen(filename, "r");
  if(fp)
  {
    fclose(fp);
    check_tabs(fp, filename);
    count_lines(fp, filename);
  }
  else
  {
   printf("Can't open %s for read.\n", filename);
  }

}
