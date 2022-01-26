/*!*****************************************************************************
\file    robot.cpp
\author  Anthon Reid
\par     DP email:  anthon.reid@digipen.edu
\par     Course: CS120
\par     Assignment #1
\date    01-17-2022

\brief
This uses a struct and performs various tasks on robot via several
separate functions to create, move and destroy a robot.

*******************************************************************************/

#include <iostream> // cout
#include <iomanip> 
#include <cstdlib>  // atoi

#include "robot.h"
#include "grid.h"

namespace CS170 
{
    namespace Robot
    {
        namespace grid_access = CS170::Grid;

        struct _Robot
        {
            int x_pos;
            int y_pos;
            Orientation direction;
            Grid::Instance grid;
        };

/*!*****************************************************************************
\brief
A pointer to an incomplete structure, or opaque pointer. 
creates robot on the grid.

\param int
The horizontal position (positive direction is left to right) 
of the robot.

\param int
The vertical position (positive direction is top to bottom).

\param orientation
An enumerated type for a valid robot orientations.

\param instance
A pointer the grid structure.

\return 
A valid robot instance.
*******************************************************************************/
Instance Create(int _x, int _y, Orientation orientation,  Grid::Instance _grid)
{
    /*creating a new robot instance */
    Instance robot = new _Robot;

    /*initializing the robot position and orientation on the grid */
    robot->x_pos = _x;
    robot->y_pos = _y;
    robot->direction = orientation;
    robot->grid = _grid;

    /* returs a robot instance */
    return robot;
}

/*!*****************************************************************************
\brief
Destroys a previously created robot.
\param instance
A pointer the robot structure to be destroyed.

\return 
None
*******************************************************************************/
void Destroy(Instance robot)
{
    if (robot)
    {
        /* deletes the robot */
        delete robot;
    }
}

/*!*****************************************************************************
\brief
This gives robot a single command.

\param instance
A pointer the robot structure to be destroyed.

\param char
A character that holds the input of the user
which moves the robot.

\return 
None
*******************************************************************************/

void Move(Instance robot, char cmd)
{
    if (robot && robot->direction != UNDEF)
    {
        /* if the robot is inside the grid at an unmarked location */
        if (grid_access::Inside(robot->grid, robot->x_pos, robot->y_pos))
        {
            if (!grid_access::Marked(robot->grid, robot->x_pos, robot->y_pos))
            {
                /* checks the user input */
                switch (cmd)
                {
                case 'f':
                    switch (robot->direction)
                    {
                    case(0):
                        /* move the robot north */
                        robot->y_pos -= 1;
                        /* if the robot is no longer inside mark the grid */
                        if (!CS170::Grid::Inside(robot->grid, robot->x_pos, robot->y_pos))
                        {
                            grid_access::Mark(robot->grid, robot->x_pos, robot->y_pos + 1);
                        }
                        break;
                    case(1):
                        /* move the robot east */
                        robot->x_pos += 1;
                        /* if the robot is no longer inside mark the grid */
                        if (!grid_access::Inside(robot->grid, robot->x_pos, robot->y_pos))
                        {
                            grid_access::Mark(robot->grid, robot->x_pos - 1, robot->y_pos);
                        }
                        break;
                    case(2):
                        /* move the robot south */
                        robot->y_pos += 1;
                        /* if the robot is no longer inside mark the grid */
                        if (!grid_access::Inside(robot->grid, robot->x_pos, robot->y_pos))
                        {
                            grid_access::Mark(robot->grid, robot->x_pos, robot->y_pos - 1);
                        }
                        break;
                    case(3):
                        /* move the robot west */
                        robot->x_pos -= 1;
                        /* if the robot is no longer inside mark the grid */
                        if (!grid_access::Inside(robot->grid, robot->x_pos, robot->y_pos))
                        {
                            grid_access::Mark(robot->grid, robot->x_pos + 1, robot->y_pos);
                        }
                    default:
                        break;
                    }
                    break;
                case 'l':
                    /* rotate the robot to the left */
                    robot->direction = Orientation((robot->direction + 3) % 4);
                    break;
                case 'r':
                    /* rotate the robot counter to the right */
                    robot->direction = Orientation((robot->direction + 1) % 4);
                    break;
                default:
                    break;
                }
            }
            /* if the robot is on a marked spot */
            else if (grid_access::Marked(robot->grid, robot->x_pos, robot->y_pos))
            {

                switch (cmd)
                {
                case 'f':
                    switch (robot->direction)
                    {
                    case(0):
                        /* only move if the next spot is inside the grid */
                        if (grid_access::Inside(robot->grid, robot->x_pos, robot->y_pos-1))
                        {
                            robot->y_pos -= 1;
                        }
                        break;
                    case(1):
                        /* only move if the next spot is inside the grid */
                        if (grid_access::Inside(robot->grid, robot->x_pos + 1, robot->y_pos))
                        {
                            robot->x_pos += 1;
                        }
                        break;
                    case(2):
                        /* only move if the next spot is inside the grid */
                        if (grid_access::Inside(robot->grid, robot->x_pos, robot->y_pos + 1))
                        {
                            robot->y_pos += 1;
                        }
                        break;
                    case(3):
                        /* only move if the next spot is inside the grid */
                        if (grid_access::Inside(robot->grid, robot->x_pos-1, robot->y_pos))
                        {
                            robot->x_pos -= 1;
                        }
                    default:
                        break;
                    }
                    break;
                case 'l':
                    /* rotate the robot counter to the left */
                    robot->direction = Orientation((robot->direction + 3) % 4);
                    break;
                case 'r':
                    /* rotate the robot counter to the right */
                    robot->direction = Orientation((robot->direction + 1) % 4);
                    break;
                default:
                    break;
                }
            }
        }
    }
}

/*!*****************************************************************************
\brief
This gives robot a single command.

\param instance
A pointer the robot structure to be destroyed.

\param int
The horizontal position (positive direction is left to right) 
of the robot.

\param int
The vertical position (positive direction is top to bottom).

\param orientation
An enumerated type for a valid robot orientations.

\return 
True if robot is on the grid, false if it is lost.
*******************************************************************************/
    bool QueryPosition(Instance robot, int* x, int* y, Orientation *o)
    {
        if (robot)
        {
            /* checks where the robot is on the map */
            *x = robot->x_pos;
            *y = robot->y_pos;
            *o = robot->direction;

            /* if the robot is inside the grid */
            if (Inside(robot->grid, robot->x_pos, robot->y_pos))
            {
                /* robot is alive */
                return true;
            } 
        }

        return false;
    }      
  }   
}