
/******************************************************************************
filename    list.c
author      Anthon Reid
DP email    anthon.reid@digipen.edu
course      CS120
section     A
lab week    12
due date    12/4/2021

Brief Description:
  This program calculates the distance to the moon using only a compass
  and a straight-edge. 
  
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void add_front(struct Node **list, int value)
{
  struct Node *new_list = malloc(sizeof(struct Node));
  new_list->number = value;
  new_list->next = *(list);

  *(list) = new_list;
}
void add_back(struct Node **list, int value)
{
  struct Node *new_list = malloc(sizeof(struct Node));
  new_list->number = value;
  new_list->next = NULL;


  if (*list == NULL)
  {
    *list = new_list;
  }
  else
  {
    struct Node *temp = *list;
    while (temp->next)
    {
        temp = temp->next;
    }
    temp->next = new_list;
  }
}
void free_list(struct Node *list)
{
  while (list)
  {
    struct Node *temp = list->next;
    free(list);
    list = temp;
  }
}
void print_list(const struct Node *list)
{
  while (list)
  {
    printf("%3i", list->number);
    list = list->next;
  }
  printf("\n");
}

void remove_item(struct Node **list, int value)
{
  struct Node *current_list;
  struct Node *next_list;
  if(*list == NULL)
  {
    return;
  }
  current_list = *(list);
  next_list = current_list->next;
  
  if(current_list->number == value)
  {
    *list = next_list;
    free(current_list);
  }
  else
  {
    while (next_list != NULL)
    {
      if(next_list->number == value)
      {
          if(current_list->next->next != NULL)
          {
            current_list->next = (current_list->next->next);
            free(next_list);
            next_list = current_list->next;
            return;
          }
          else
          {
            current_list->next = NULL;
            free(next_list);
            return;
          }
      }
      current_list = next_list;
      next_list = current_list->next;
    }
  }
}

int size_list(const struct Node *list)
{
int size = 0;
  while (list && list != NULL)
  {
    size ++;
    list = list->next;
  }
  
return size;
}

int sum_list(const struct Node *list)
{
  int sum = 0;
    while (list)
  {
    sum += list->number;
    list = list->next;
  }
return sum;
}
