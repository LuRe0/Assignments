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


#include "matrix.h"
#include <stdlib.h>
#include <stdio.h>


/* allocate 2-dimentional array with the specified dimensions */
Matrix matrix_create( int num_rows, int num_columns )
{
    Matrix matrix =  NULL;
    int i = 0;
    matrix = malloc(num_rows * sizeof(Matrix));

    if (matrix)
    {
        for (i = 0; i < num_rows; i++)
        {
            matrix[i] = malloc(num_columns * sizeof(num_columns));
        }
        

        return matrix;
    }
}


/* matrix addition, assume result matrix is already allocated */
void matrix_add( Matrix m1, Matrix m2, Matrix result, int num_rows, int num_columns )
{
    int i = 0;
    int j = 0;

    for (i = 0; i < num_rows; i++)
    {
        for (j = 0; j < num_columns; j++)
        {
            result[i][j] = m1[i][j] + m2[i][j];
        }
    }
}


/* matrix transposition, returns a new matrix, does not delete the original */
Matrix matrix_transpose( Matrix m, int num_rows, int num_columns )
{
    int i = 0;
    int j = 0;

    	Matrix newMatrix = matrix_create(num_columns, num_rows);
		for (i = 0; i < num_columns; i++)
		{
			for (j = 0; j < num_rows; j++)
			{
				newMatrix[i][j] = m[j][i];
			}
		}

        return newMatrix;
}


/* deallocate matrix */
void   matrix_delete( Matrix m, int num_rows )
{
    int i = 0;
    for (i = 0; i < num_rows; i++)
    {
        free(m[i]);
    }
    if (m)
    {
        free(m);
    }
}


/* delete one row (index r) from matrix */
void   matrix_delete_row( Matrix m, int r, int num_rows )
{
    int i = 0;
    if (m)
    {
        for (i = 0; i < num_rows; i++)
        {
            if (i >= r)
            {
                if (m[i + 1] != NULL)
                {
                    m[i] = m[i + 1];
                }
            }
        }
    }
}


/* delete one column (index c) from matrix */
void   matrix_delete_column( Matrix m, int c, int num_rows, int num_columns )
{
    int i = 0;
    int j = 0;

    for (i = 0; i < num_rows; i++)
    {
        for (j = 0; j < num_columns; j++)
        {
            if (j >= c)
            {
               m[i][j] = m[i][j+1];
            }
        }
    }
}


void  matrix_print( Matrix m, int num_rows, int num_columns ) {
    int i, j;
    for ( i=0; i<num_rows; ++i ) {
        for ( j=0; j<num_columns; ++j ) {
            printf( "%4i ", m[i][j] );
        }
        printf( "\n" );
    }
}
