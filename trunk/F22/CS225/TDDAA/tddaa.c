/*!
 * @file    tddaa.c
 * @author  Anthon Reid
 * @par     email: anthon.reid\@digipen.edu
 * @par     DigiPen login: anthon.reid
 * @par     Course: CS225
 * @par     Section: A
 * @par     Lab 3
 * @date    2022-09-24
 * @brief 
 *        A simple implementation of 3-dimensional matrix. 
 */



/*
2x3x4
+----------------------------------------+
|+------------------++------------------+|
||+----++----++----+||+----++----++----+||
|||1234||1234||1234||||1234||1234||1234|||
||+----++----++----+||+----++----++----+||
|+------------------++------------------+|
+----------------------------------------+

+------+
|abcdef| 6 pointers to 1's ( array of row pointers )
+------+

+--+
|mn| 2 pointers to a and d above ( array of pointers to slices )
+--+

a[i][j][k]
i chooses which slice
j chooses which row within the slice
k chooses within element with the row
*/

#include "tddaa.h"
#include <stdlib.h>

int *** allocate( int d1, int d2, int d3 ) 
{
    int i = 0;
    int j = 0;

    int*** Matrix = (int***)malloc(d1 * sizeof(int**));

    if (Matrix)
    {
        for (i = 0; i < d1; i++)
        {
            Matrix[i] =  (int**)malloc(d2 * sizeof(int*));
            if(Matrix[i])
            {
                for(j = 0; i < d2; j++)
                {
                    Matrix[i][j] = (int*)malloc(d3 * sizeof(int));
                }
            }
        }
        
        return Matrix;
    }
    else
    {
        return NULL;
    }
    
}

void deallocate( int *** ppp ) 
{
ppp = NULL;
}


