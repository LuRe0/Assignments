/*!*****************************************************************************
\file    robot.cpp
\author  Anthon Reid
\par     DP email:  anthon.reid@digipen.edu
\par     Course: CS120
\par     Assignment #2
\date    01-31-2022

\brief
This uses a class and performs various tasks on robot via several
separate functions to create, move and destroy a robot.

*******************************************************************************/


#include <iostream> // cout
#include <iomanip> 
#include <cstdlib>  // atoi

#include "robot.h"
#include "grid.h"

namespace CS170
{

    /*!*****************************************************************************
    \brief
    A pointer to an incomplete structure, or opaque pointer.
    creates robot on the grid.


    \param Grid
    A pointer the grid class.

    \param int
    The horizontal position (positive direction is left to right)
    of the robot.

    \param int
    The vertical position (positive direction is top to bottom).

    \param orientation
    An enumerated type for a valid robot orientations.


    \return
    None
    *******************************************************************************/
    Robot::Robot(Grid& _grid, int _x, int _y, Orientation orientation):grid (_grid)
    {
        /*initializing the robot position and orientation on the grid */
        grid = _grid;
        x = _x;
        y = _y;
        heading = orientation;
    }

    /*!*****************************************************************************

    \brief
    Destroys a previously created robot.

    \param instance
    A pointer the robot structure to be destroyed.

    \return
    None
    *******************************************************************************/
    Robot::~Robot()
    {
       
    }


    /*!*****************************************************************************
    \brief
    This gives robot a single command.

    \param char
    A character that holds the input of the user
    which moves the robot.

    \return
    None
    *******************************************************************************/
    void Robot::Move(char cmd)
    {
            /* if the robot is inside the grid at an unmarked location */
            if (grid.Inside(x,y))
            {
                if (!grid.Marked(x, y))
                {
                    /* checks the user input */
                    switch (cmd)
                    {
                    case 'f':
                        switch (heading)
                        {
                        case(0):
                            /* move the robot north */
                            y -= 1;
                            /* if the robot is no longer inside mark the grid */
                            if (!grid.Inside(x,y))
                            {
                                grid.Mark(x, y + 1);
                            }
                            break;
                        case(1):
                            /* move the robot east */
                            x += 1;
                            /* if the robot is no longer inside mark the grid */
                            if (!grid.Inside(x, y))
                            {
                                grid.Mark(x - 1, y);
                            }
                            break;
                        case(2):
                            /* move the robot south */
                            y += 1;
                            /* if the robot is no longer inside mark the grid */
                            if (!grid.Inside(x, y))
                            {
                                grid.Mark(x, y - 1);
                            }
                            break;
                        case(3):
                            /* move the robot west */
                            x -= 1;
                            /* if the robot is no longer inside mark the grid */
                            if (!grid.Inside(x, y))
                            {
                                grid.Mark(x + 1, y);
                            }
                        default:
                            break;
                        }
                        break;
                    case 'l':
                        /* rotate the robot to the left */
                        heading = Orientation((heading + 3) % 4);
                        break;
                    case 'r':
                        /* rotate the robot counter to the right */
                        heading = Orientation((heading + 1) % 4);
                        break;
                    default:
                        break;
                    }
                }
                /* if the robot is on a marked spot */
                else if (grid.Marked( x, y))
                {

                    switch (cmd)
                    {
                    case 'f':
                        switch (heading)
                        {
                        case(0):
                            /* only move if the next spot is inside the grid */
                            if (grid.Inside( x, y - 1))
                            {
                                y -= 1;
                            }
                            break;
                        case(1):
                            /* only move if the next spot is inside the grid */
                            if (grid.Inside( x + 1, y))
                            {
                                x += 1;
                            }
                            break;
                        case(2):
                            /* only move if the next spot is inside the grid */
                            if (grid.Inside( x, y + 1))
                            {
                                y += 1;
                            }
                            break;
                        case(3):
                            /* only move if the next spot is inside the grid */
                            if (grid.Inside( x - 1, y))
                            {
                                x -= 1;
                            }
                        default:
                            break;
                        }
                        break;
                    case 'l':
                        /* rotate the robot counter to the left */
                        heading = Orientation((heading + 3) % 4);
                        break;
                    case 'r':
                        /* rotate the robot counter to the right */
                        heading = Orientation((heading + 1) % 4);
                        break;
                    default:
                        break;
                    }
                }
            }
    }

    /*!*****************************************************************************
    \brief
    Gets the robots x position

    \return
    The robot's x position
    *******************************************************************************/
    int Robot::GetX()
    {
        /*returns x position*/
        return x;
    }

    /*!*****************************************************************************
    \brief
    Gets the robots y position

    \return
    The robot's y position
    *******************************************************************************/
    int Robot::GetY()
    {   
        /*returns y position*/
        return y;
    }
    /*!*****************************************************************************
    \brief
    Gets the robots orientation

    \return
    The robot's orientation
    *******************************************************************************/
    Robot::Orientation Robot::GetO()
    {
        /*returns orientation*/
        return heading;
    }

    /*!*****************************************************************************
    \brief
    Gets the robots status

    \return
    The robot's status
    *******************************************************************************/
    bool Robot::GetStatus()
    {
        if (grid.Inside(x, y))
        {
            /* robot is alive */
            return true;
        }

        return false;
    }
}