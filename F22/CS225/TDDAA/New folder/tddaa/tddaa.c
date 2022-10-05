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
    /* d1 = slices, d2 = rows, d3 = element */
    int* element = (int*)malloc(d1 * d2  * d3 * sizeof(int));
    int** row = (int**)malloc(d1 * d2 * sizeof(int*));
    int*** slices = (int***)malloc(d1 * sizeof(int**));


    for (i = 0; i < d1; ++i)
    {
        slices[i] = row + (i * d2);

        for (j = 0; j < d2; ++j)
        {
            slices[i][j] = element + (j * d3) + (i*d2*d3); 
        }
    }
    
    return slices;
}

void deallocate( int *** ppp ) 
{
    free(ppp[0][0]);
    free(ppp[0]);
    free(ppp);
}


