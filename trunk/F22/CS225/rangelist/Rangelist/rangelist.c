/*!
 * @file    matrix.c
 * @author  Anthon Reid
 * @par     email: anthon.reid\@digipen.edu
 * @par     DigiPen login: anthon.reid
 * @par     Course: CS180
 * @par     Section: A
 * @par     Lab 2
 * @date    2022-09-18
 * @brief
 *        A simple implementation of 2-dimensional matrix.
 *        Only transpose, addition, and various delete functions are required.
 */

#include "rangelist.h"
#include <stdlib.h> /* NULL/malloc/free */
#include <stdio.h>  /* printf */

#define xDEBUG

/* helper function, prototyped in the implementation file, so NOT available in the main */
void dump_node ( struct RangeNode * p );

/* your implementations: insert_value, get, delete */


/*!
 * @brief
 *  insert a single value in the range
 *
 * @param ppHead
 * the head of the list to be manipulated
 * @param position
 * the position at which the value should be added
 * @param position
 * the value that is to be added to the list
 *
 * @return
 *  return 0 if success or -1 if failure
 */
static void expandNode(struct RangeNode** p, int position, int value)
{
    if (p)
    {
        struct RangeNode* currNode = (*p);
        struct RangeNode* prevNode = NULL;
        if (currNode)
        {

            /* traversed the list*/
            while (currNode)
            {
                /*if there is a next node*/
                if (currNode->next != NULL)
                {
                    /* checks for targer value*/
                    if (currNode->value == currNode->next->value)
                    {
                        if (currNode->end == currNode->next->begin)
                        {
                            if (prevNode != NULL)
                            {
                                /*creates a node and add it in between the two nodes*/
                                struct RangeNode* newNode = (struct RangeNode*)malloc(sizeof(struct RangeNode));
                                if (newNode)
                                {
                                    newNode->begin = currNode->begin;
                                    newNode->end = currNode->next->end;
                                    newNode->value = value;
                                    newNode->next = currNode->next->next;
                                    prevNode->next = newNode;

                                   /* free(currNode->next);
                                    free(currNode);*/

                                    currNode->next = prevNode->next;
                                    currNode = prevNode;
                                }
                                break;

                            }

                            else
                            {
                                /*creates a node and add it in between the two nodes*/
                                struct RangeNode* newNode = (struct RangeNode*)malloc(sizeof(struct RangeNode));
                                if (newNode)
                                {
                                    newNode->begin = currNode->begin;
                                    newNode->end = currNode->next->end;
                                    newNode->value = value;
                                    newNode->next = currNode->next->next;

                                    /*free(currNode->next);
                                    free(currNode);*/

                                    currNode->next = newNode->next;
                                    currNode = newNode;

                                    *p = currNode;
                                }
                                break;

                            }
                        }
                    }
                    else
                    {
                        if (position > currNode->begin && position < currNode->end)
                        {
                            if (currNode->next->begin == position)
                            {
                                if (position + 1 == currNode->end)
                                {
                                    currNode->end = position;
                                }
                                else
                                {
                                    /*creates a node and add it in between the two nodes*/
                                    struct RangeNode* newNode = (struct RangeNode*)malloc(sizeof(struct RangeNode));
                                    if (newNode)
                                    {
                                        newNode->begin = currNode->next->end;
                                        newNode->end = currNode->end;
                                        newNode->value = currNode->value;
                                        newNode->next = currNode->next->next;
                                        currNode->next->next = newNode;
                                    }

                                    currNode->end = position;
                                }
                                break;
                            }
             
                        }
                        else if (position == currNode->begin)
                        {
                            if (position + 1 < currNode->end)
                            {
                                struct RangeNode* newNode = (struct RangeNode*)malloc(sizeof(struct RangeNode));
                                if (newNode)
                                {
                                    newNode->begin = position + 1;
                                    newNode->end = currNode->end;
                                    newNode->value = currNode->value;
                                    newNode->next = currNode->next;
                                    currNode->next = newNode;
                                }
                                currNode->end = position + 1;
                                break;
                            }
                            
                        }
                        else if (position == currNode->end)
                        {
                            if (currNode->value != value)
                            {
                                /*creates a node and add it in between the two nodes*/
                                struct RangeNode* newNode = (struct RangeNode*)malloc(sizeof(struct RangeNode));
                                if (newNode)
                                {
                                    newNode->begin = position;
                                    newNode->end = position + 1;
                                    newNode->value = value;
                                    newNode->next = currNode->next;
                                    currNode->next = newNode;
                                }
                            }
                            else
                            {
                                break;
                            }
                            break;
                        }

                    }
                }
                else
                {
                    if (position == currNode->begin)
                    {
                        if (position + 1 < currNode->end )
                        {
                            struct RangeNode* newNode = (struct RangeNode*)malloc(sizeof(struct RangeNode));
                            if (newNode)
                            {
                                newNode->begin = position + 1;
                                newNode->end = currNode->end;
                                newNode->value = currNode->value;
                                newNode->next = currNode->next;
                                currNode->next = newNode;
                            }

                            currNode->end = position + 1;
                            break;
                        }
                    }
                    else if (position == currNode->end)
                    {
                        if (currNode->value != value)
                        {
                            struct RangeNode* newNode = (struct RangeNode*)malloc(sizeof(struct RangeNode));
                            if (newNode)
                            {
                                newNode->begin = position;
                                newNode->end = position + 1;
                                newNode->value = value;
                                newNode->next = currNode->next;
                                currNode->next = newNode;
                            }
                        }
                        else
                        {
                            break;
                        }
                        break;
                    }
                }
                prevNode = currNode;
                currNode = currNode->next;
            }
        }
    }
}


/*!
 * @brief
 *  insert a single value in the range
 *
 * @param ppHead
 * the head of the list to be manipulated
 * @param position
 * the position at which the value should be added
 * @param position
 * the value that is to be added to the list
 *
 * @return
 *  return 0 if success or -1 if failure
 */
int insert_value(struct RangeNode** ppHead, int position, int value)
{

    /* if the list is empty create a node and add it to the list*/
    if (*ppHead == NULL)
    {
        if (value != 0)
        {

            struct RangeNode* newNode = (struct RangeNode*)malloc(sizeof(struct RangeNode));
            if (newNode)
            {
                newNode->begin = position;
                newNode->end = position + 1;
                newNode->value = value;
                newNode->next = NULL;
                *ppHead = newNode;
            }
            return 0;
        }
        else
        {
            return 0;
        }
    }
    /* if the list is not empty */
    if (*ppHead != NULL)
    {
        struct RangeNode * curr = *ppHead;
        struct RangeNode * prev = NULL;

        if (curr)
        {
   
            /* we loop traverse the linked list*/
            while (curr)
            {
                /* if the value is not 0 we proceed*/
                if (value != 0)
                {
                    /* if the position lies inside or at the edge a node's range*/
                    if (position >= curr->begin && position <= curr->end)
                    {
                        /* if its not at the end of the range*/
                        if (position >= curr->begin && position != curr->end)
                        {
                            /*if its at the begining of the range*/
                            if (position == curr->begin)
                            {
                                /* we maipulate the list and update the node's value*/
                                expandNode(&curr, position, value);
                                curr->value = value;
                                return 0;
                            }
                            /* if its not at the beginning of the range*/
                            else
                            {   
                                /*we create a new node and and manipulte the list to insert it*/
                                struct RangeNode* newNode = (struct RangeNode*)malloc(sizeof(struct RangeNode));
                                if (newNode)
                                {
                                    newNode->begin = position;
                                    newNode->end = position + 1;
                                    newNode->value = value;
                                    newNode->next = curr->next;
                                    curr->next = newNode;
                                }
                                expandNode(&curr, position, value);
                                return 0;
                            }
                        }
                        /*if it is at the end of the range*/
                        else if (position == curr->end)
                        {
                            /* if the value matches the*/
                            if (curr->value == value)
                            {
                                /* increase the list's range*/
                                curr->end = curr->end + 1;
                                curr->value = value;

                                if (curr->next)
                                {

                                    if (position == curr->next->begin - 1)
                                    {
                                        if (curr->next->value == value)
                                        {
                                            curr->end = curr->next->end;
                                            free(curr->next);
                                            curr->next = NULL;
                                            return 0;
                                        }
                                    }
                                }
                             /*   else
                                {
                                    expandNode(&curr, curr->end, value);
                                }*/

                                if (prev == NULL)
                                {
                                    *ppHead = curr;
                                }
                                return 0;
                            }
                            /* otherwise splite the range into new nodes*/
                            else
                            {
                                expandNode(&curr, curr->end, value);
                                return 0;
                            }
                        }
                    }
                    /*if the position is is not at the edge of the node's range*/
                    else
                    {
                        /* if there is no next node*/
                        if (curr->next != NULL)
                        {
                            /* if the position is not at the end of the range*/
                            if (position >= curr->end && position < curr->next->begin)
                            {
                                if (value != curr->value && curr->next->value != value)
                                {
                                    /*create a new node*/
                                    struct RangeNode* newNode = (struct RangeNode*)malloc(sizeof(struct RangeNode));
                                    if (newNode)
                                    {
                                        newNode->begin = position;
                                        newNode->end = position + 1;
                                        newNode->value = value;
                                        newNode->next = curr->next;
                                        curr->next = newNode;
                                    }
                                    return 0;
                                }
          
                                else
                                {
                                    if (position == curr->next->begin - 1 )
                                    {
                                        if (curr->next->value == value)
                                        {
                                            curr->next->begin = position;
                                            return 0;
                                        }
                                    }
                                    else if(position == curr->begin - 1)
                                    {
                                        if (curr->value == value)
                                        {
                                            curr->begin = position;
                                            return 0;
                                        }
                                    }
                                    else
                                    {
                                        /*create a new node*/
                                        struct RangeNode* newNode = (struct RangeNode*)malloc(sizeof(struct RangeNode));
                                        if (newNode)
                                        {
                                            newNode->begin = position;
                                            newNode->end = position + 1;
                                            newNode->value = value;
                                            newNode->next = curr->next;
                                            curr->next = newNode;
                                        }
                                        if (newNode->end == newNode->next->begin)
                                        {
                                            newNode->end = newNode->next->end;
                                            free(newNode->next);
                                            newNode->next = NULL;
                                        }
                                        return 0;
                                    }
                                }
                            }
                            /*if this is the first node and the position is before the range*/
                            if (prev == NULL && position < curr->begin)
                            {
                                if (position == curr->next->begin - 1)
                                {
                                    if (curr->next->value == value)
                                    {
                                        curr->next->begin = position;
                                        return 0;
                                    }
                                }
                                else if (position == curr->begin - 1)
                                {
                                    if (curr->value == value)
                                    {
                                        curr->begin = position;
                                        return 0;
                                    }
                                }
                                else
                                {
                                    /* create a new node and add it at the head of the list*/
                                    struct RangeNode* newNode = (struct RangeNode*)malloc(sizeof(struct RangeNode));
                                    if (newNode)
                                    {
                                        newNode->begin = position;
                                        newNode->end = position + 1;
                                        newNode->value = value;
                                        newNode->next = *ppHead;

                                        *ppHead = newNode;

                                        curr = *ppHead;
                                    }
                                    expandNode(&curr, curr->end, value);
                                    *ppHead = curr;
                                    return 0;
                                }
                            }
                
                        }
                        /*if there is a next node*/
                        else
                        {
                            /*if the position is before the begigning of the range*/
                            if (position < curr->begin)
                            {
                                if (prev != NULL)
                                {
                                    /*add a new node*/
                                    struct RangeNode* newNode = (struct RangeNode*)malloc(sizeof(struct RangeNode));
                                    if (newNode)
                                    {
                                        newNode->begin = position;
                                        newNode->end = position + 1;
                                        newNode->value = value;
                                        prev->next = newNode;
                                        newNode->next = curr;
                                    }
                     
                                }
                                else
                                {
                                    /*add a new node*/
                                    struct RangeNode* newNode = (struct RangeNode*)malloc(sizeof(struct RangeNode));
                                    if (newNode)
                                    {
                                        newNode->begin = position;
                                        newNode->end = position + 1;
                                        newNode->value = value;
                                        newNode->next = *ppHead;

                                        *ppHead = newNode;
                                    }
                                }
                                return 0;
                            }
                            else if (position > curr->end)
                            {
                                struct RangeNode* newNode = (struct RangeNode*)malloc(sizeof(struct RangeNode));
                                if (newNode)
                                {
                                    newNode->begin = position;
                                    newNode->end = position + 1;
                                    newNode->value = value;
                                    newNode->next = curr->next;
                                    curr->next = newNode;
                                }
                                return 0;
                            }
                        }
                    }
               
                }
                /* otherwise if the value is zero we delete the list*/
                else
                {
                    if (position >= curr->begin && position <= curr->end)
                    { 
                        if (curr == NULL)
                        {
                            return 0;
                        }

                        if (prev == NULL)
                        {
                            *ppHead = (*ppHead)->next;
                        }
                        else
                        {
                            prev->next = curr->next;
                        }

                        free(curr);

                        return 0;
                    }
                }

                prev = curr; 
                curr = curr->next;
            }
            
        }
    }



 


    return -1;
}


/* return value at position (index) */
/*!
 * @brief
 *   return value at position (index)
 *
 * @param p
 * the head of the list to be manipulated
 * @param position
 * the position at which the value should be added
 *
 * @return
 *  return 0 if success or -1 if failure
 */
int get(struct RangeNode const* p, int position)
{
    if (p)
    {
        /*traverses the list*/
        while (p)
        {
            /*if the postion is in the range*/
            if (position >= p->begin && position <= p->end)
            {
                if (position >= p->begin && position != p->end)
                {
                    /*return the value*/
                    return p->value;
                }
                else if(position == p->end)
                {
                    return 0;
                }
            }
            p = p->next;
        }
    }
    return 0;
}


/*!
 * @brief
 *   deallocated the list
 * @param p
 * the head of the list to be manipulated
 */
void delete(struct RangeNode* p)
{
    /*traverses the list and frees the nodes*/
    while (p)
    {
        struct RangeNode* temp = p->next; 
        free(p);                   
        p = temp;                  
    }
}




































/* implementations - DO NOT MODIFY*/
void dump_node ( struct RangeNode * p )
{
  printf( "+--------------------------\n" );
  printf( "| %p | %i [ %i, %i ) --> %p\n", (void*)p, p->value, p->begin, p->end, (void*)p->next );
  printf( "+--------------------------\n" );
}

void printf_elements( struct RangeNode const * p, char * format, int dimension, int do_sanity_check )
{
  int i, last_pos = 0;
  typedef int boolean;
  boolean zeroes     = 0;
  boolean non_merged = 0;
  boolean overlapping_ranges = 0;
  /* indices */
  for ( i = 0; i < dimension; ++i ) { printf( format, i ); }
  printf( "\n" );
  /* data */
  while ( p ) {
    for ( i = last_pos; i < p->begin; ++i ) { printf( format, 0 ); }          /* print leading zeros */
    if ( p->value == 0 ) { zeroes = 1; } /* sanity check */
    for ( i = p->begin; i < p->end;   ++i ) { printf( format, p->value ); }   /* print value */
    last_pos = p->end;
    if ( p->next && p->end >  p->next->begin ) { overlapping_ranges = 1; }    /* sanity check */
    if ( p->next && p->end == p->next->begin && p->value == p->next->value) { non_merged = 1; } /* sanity check */
    p = p->next;
  }
  for ( i = last_pos ; i < dimension; ++i ) { printf( format, 0 ); }

  /* sanity reporting */
  if ( do_sanity_check && zeroes ) {
    printf( "zero values should not be stored\n" );
  }
  if ( do_sanity_check && overlapping_ranges ) {
    printf( "overlapping ranges\n" );
  }
  if ( do_sanity_check && non_merged ) {
    printf( "ranges with the same value and next to each other - should be merged\n" );
  }
}

void print_raw( struct RangeNode const * p)
{
  while ( p ) {
    printf( "%i [ %i, %i ) --> ", p->value, p->begin, p->end );
    p = p->next;
  }
  printf( "NULL" );
}

int insert_nonoverlapping_range( struct RangeNode ** ppHead, int begin, int end, int value )
{
  struct RangeNode * new_node = (struct RangeNode*) malloc( sizeof( struct RangeNode ) );
  if ( new_node == NULL ) { 
    return 0;
  }

  new_node->begin = begin;
  new_node->end   = end;
  new_node->value = value;

  /* main logic */
  if ( !*ppHead || end < (*ppHead)->begin ) { /* empty or in-front (short circuit) */
    new_node->next = *ppHead;
    *ppHead = new_node;
    return 0;  
  } else { /* insert in the middle or tail */
    struct RangeNode * p = *ppHead;
    while ( p->next && p->next->end <= begin ) { /* find the right place */
      p = p->next;
    }

    if ( !p->next ) { /* insert in the end */
      new_node->next = NULL;
      p->next = new_node; /* make tail */
      return 0; 
    } else { /* insert between p and p->next */
      new_node->next = p->next; 
      p->next = new_node;
    }
  }
  return 0;
}

