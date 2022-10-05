/*!*****************************************************************************
\file    grid.cpp
\author  Anthon Reid
\par     DP email:  anthon.reid@digipen.edu
\par     Course: CS120
\par     Assignment #2
\date    01-31-2022

\brief
    This uses a class and performs various tasks on grid via several
    separate functions to create, mark and destroy a grid.

*******************************************************************************/
#include <iostream> // cout
#include <iomanip> 
#include <cstdlib>  // atoi

#include "grid.h"
namespace CS170
{

    /*!*****************************************************************************
    \brief
        A constructor that creates a world grid

    \param int
        The horizontal offset (positive direction is left to right)
        of the grid.

    \param int
        The vertical offset (positive direction is top to bottom).

    \return
        none
    *******************************************************************************/
    Grid::Grid(int x, int y)
    {
        /* initialize a new grid instance */
        x_max = x;
        y_max = y;

        /* creates the rows of the grid */
        data = new int[x * y]();
    }


    /*!*****************************************************************************
    \brief
       A destructor that destroys a previously created world grid.

    \return
        None
    *******************************************************************************/
    Grid::~Grid()
    {
        delete[] data;
    }

     /*!*****************************************************************************
    \brief
       Checks is a given location is inside the grid.

    \param int
      The horizontal offset (positive direction is left to right)
      of the grid.

    \param int
      The vertical offset (positive direction is top to bottom).

    \return
       True if (x, y) is inside grid; false
       otherwise.
    *******************************************************************************/
    bool Grid::Inside(int x, int y)
    {
        /* if the position is inside the grid */
        if ((x >= 0 && x < x_max &&
            (y >= 0 && y < y_max)))
        {
            /* return false */
            return true;
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
    void Grid::Mark(int x, int y)
    {
        data[x_max*y+x] = 1;
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
    bool Grid::Marked(int x, int y)
    {
        /* if the position is inside the grid */
        if ((x >= 0 && x < x_max) &&
            (y >= 0 && y < y_max))
        {
            /* if its been marked */
            if (data[x_max * y + x] == 1)
            {
                /* return true */
                return true;
            }
        }

        /* otherwise return false */
        return false;
    }
}