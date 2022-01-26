/*!*****************************************************************************
\file    grid.cpp
\author  Anthon Reid
\par     DP email:  anthon.reid@digipen.edu
\par     Course: CS120
\par     Assignment #1
\date    01-17-2022

\brief
    This uses a struct and performs various tasks on grid via several
    separate functions to create, mark and destroy a grid.

*******************************************************************************/

#include <iostream> // cout
#include <iomanip> 
#include <cstdlib>  // atoi

#include "grid.h"

namespace CS170 {
    namespace Grid {

        struct _Grid
        {
            int row;
            int column;
            int** field;
        };

/*!*****************************************************************************
\brief
   A pointer to an incomplete structure, or opaque pointer. 
   creates a world grid

\param int
  The horizontal offset (positive direction is left to right) 
  of the grid.

\param int
  The vertical offset (positive direction is top to bottom).

\return 
  A valid unmarked world grid instance.
*******************************************************************************/

        Instance Create(int x, int y)
        {
            /* initialize a new grid instance */
            Instance new_grid = new _Grid;
            
            new_grid->row = x;
            new_grid->column = y;

            /* creates the rows of the grid */
            new_grid->field = new int*[x];

            /* for each row add a corresponding column */
            for (int i = 0; i < x; i++)
            {
                new_grid->field[i] = new int[y];

                for (int j = 0; j < y; j++)
                {
                    new_grid->field[i][j] = 0;
                }
            }


            /* return the grid */
            return new_grid;
        }

/*!*****************************************************************************
\brief
   Destroys a previously created world grid.

\param instance
  A pointer the grid structure to be destroyed.

\return 
  None
*******************************************************************************/
        void Destroy(Instance grid)
        {   
            /* destroy the rows and column of the grid */
            for (int i = 0; i < grid->row; i++)
            {
                delete[] grid->field[i];
            }

            /* delete the array altogether */
            delete[] grid->field;
            /* delete the grid itself */
            delete grid;
        }

/*!*****************************************************************************
\brief
   Checks is a given location is inside the grid.

\param instance
   A pointer the grid structure.

\param int
  The horizontal offset (positive direction is left to right) 
  of the grid.

\param int
  The vertical offset (positive direction is top to bottom).

\return 
   True if (x, y) is inside grid; false 
   otherwise.
*******************************************************************************/
        bool Inside(Instance grid, int x, int y)
        {
            if (grid)
            {
                /* if the position is inside the grid */
                if( (x >= 0 && x < (grid->row)) && 
                    (y >= 0 && y < (grid->column))) 
                {
                    /* return false */
                    return true;
                }
            }

            /* otherwise return false */
            return false;
        }
/*!*****************************************************************************
\brief
   Places a marker on the world grid;

\param instance
   A pointer the grid structure.
   
\param int
  The horizontal offset (positive direction is left to right) 
  of the grid.

\param int
  The vertical offset (positive direction is top to bottom).

\return 
  None
*******************************************************************************/
        void Mark(Instance grid, int x, int y)
        {
            if(grid)
            {
                /* mark the grid if it exists */
                grid->field[x][y] = 1;   
            }
        }
        
/*!*****************************************************************************
\brief
   Tests for a grid marker

\param instance
   A pointer the grid structure.
   
\param int
  The horizontal offset (positive direction is left to right) 
  of the grid.

\param int
  The vertical offset (positive direction is top to bottom).

\return 
   True if point (x, y) is
   marked; false otherwise.    
*******************************************************************************/
        bool Marked(Instance grid, int x, int y)
        {
            if(grid)
            {   
                
                /* if the position is inside the grid */
                if( (x >= 0 && x < (grid->row)) && 
                    (y >= 0 && y < (grid->column))) 
                {
                    /* if its been marked */
                    if(grid->field[x][y] == 1)
                    {
                        /* return true */
                        return true;
                    }
                }
            }   

            /* otherwise return false */
            return false;
        }
    }
}