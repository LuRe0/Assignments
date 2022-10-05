#include <iostream>
#include <string>
#include "grid.h"
#include "robot.h"

char Orientation2char(CS170::Robot::Orientation o) {
    switch (o) {
        case CS170::Robot::NORTH: return 'n';
        case CS170::Robot::SOUTH: return 's';
        case CS170::Robot::EAST: return 'e';
        case CS170::Robot::WEST: return 'w';
    }
    return '?';
}

CS170::Robot::Orientation Char2orientation(char ch) {
    switch (ch) {
        case 'n': return CS170::Robot::NORTH;
        case 's': return CS170::Robot::SOUTH;
        case 'e': return CS170::Robot::EAST ;
        case 'w': return CS170::Robot::WEST ;
    }
    return CS170::Robot::NORTH;
}


int main () {
    // grid
    std::cout << "enter field dimensions: ";
    int dim1, dim2;
    std::cin >> dim1 >> dim2;
    CS170::Grid field( dim1, dim2 );

    // statistics
    int * last_positions = new int[ dim1*dim2 ]; // flat array
    for ( int i=0; i<dim1; ++i ) { // horisontal offset (to the right)
        for ( int j=0; j<dim2; ++j ) { // vertical offset (down)
            last_positions[ i*dim2 + j ] = -1; // // -1 means unoccupied
        }
    }
   
    bool go = true;
    while ( go ) {
        // robot
        char new_robot;
        int rx,ry;
        char ch_o;
        int counter = 1;
        std::cout << "create a robot? ";
        std::cin >> new_robot;

        if (new_robot == 'n') { // done
            go = false;
            continue;
        } 

        std::cout << "enter robot position: ";
        std::cin >> rx >> ry;
        std::cout << "enter robot orientation: ";
        std::cin >> ch_o;

        CS170::Robot robot( field, rx, ry, Char2orientation(ch_o) );

        // plan 
        std::string plan;
        std::cout << "enter robot instructions: ";
        std::cin >> plan;

        // execute plan
        int plan_size = plan.size();
        for (int i=0;i<plan_size;++i) {
            //uncomment for testing
            //bool alive = QueryPosition(robot,&x,&y,&o);
            //std::cout << "robot position is " << x << " " << y << " " << Orientation2char(o);
            //if (!alive)  std::cout << " lost";
            //std::cout << std::endl << "moving " << plan[i] << std::endl;
            ///////////////////
            robot.Move( plan[i] );
        }

        // collect statistics
        bool alive = robot.GetStatus();
        int x = robot.GetX();
        int y = robot.GetY();
        CS170::Robot::Orientation orientation = robot.GetO();
        std::cout << "robot final position " << x << " " << y << " " << Orientation2char( orientation );
        if (!alive) { 
            std::cout << " lost";
        } else {
            last_positions[ x*dim2 + y ] = counter; // record last robot's position
            ++counter;
        }
        std::cout << std::endl;
    }

    // Extra output ===========================================================
    // top line
    std::cout << std::endl << "Last robots' positions" << std::endl;
    std::cout << "+";
    for ( int i=0; i<dim1; ++i ) { std::cout << "-"; }
    std::cout << "+" << std::endl;

    // for printing we need to change the order of for-loops
    for ( int j=0; j<dim2; ++j ) { // vertical offset (down)
        std::cout << "|"; // left border
        for ( int i=0; i<dim1; ++i ) { // horisontal offset (to the right)
            if ( last_positions[ i*dim2 + j ] >= 0 ) {
                std::cout << "r";
                //std::cout << last_positions[ i*dim2 + j ];
            } else {
                std::cout << " ";
            }
        }
        std::cout << "|" << std::endl; // right border and new line
    }

    // bottom line
    std::cout << "+";
    for ( int i=0; i<dim1; ++i ) { std::cout << "-"; }
    std::cout << "+" << std::endl;

    std::cout << std::endl << "Marked positions" << std::endl;

    // top line
    std::cout << "+";
    for ( int i=0; i<dim1; ++i ) { std::cout << "-"; }
    std::cout << "+" << std::endl;

    // for printing we need to change the order of for-loops
    for ( int j=0; j<dim2; ++j ) { // vertical offset (down)
        std::cout << "|"; // left border
        for ( int i=0; i<dim1; ++i ) { // horisontal offset (to the right)
            if ( field.Marked( i, j ) ) {
                std::cout << "M";
            } else {
                std::cout << " ";
            }
        }
        std::cout << "|" << std::endl; // right border and new line
    }

    // bottom line
    std::cout << "+";
    for ( int i=0; i<dim1; ++i ) { std::cout << "-"; }
    std::cout << "+" << std::endl;
    // Extra output ends ======================================================

    delete [] last_positions;
    return 0;
}
