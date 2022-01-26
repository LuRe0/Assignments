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
        case CS170::Robot::UNDEF: return '?';
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

bool InitRobot(const CS170::Grid::Instance& field, CS170::Robot::Instance& robot, std::string& plan) {
    char new_robot;
    int rx,ry;
    char ch_o;
    std::cout << "create a robot? ";
    std::cin >> new_robot;
    //std::cout << "using robot data " << rx << " " << ry << " " << ch_o << " " << plan << std::endl;
    if (new_robot == 'n') return false;

    std::cout << "enter robot position: ";
    std::cin >> rx >> ry;
    std::cout << "enter robot orientation: ";
    std::cin >> ch_o;
    std::cout << "enter robot instructions: ";
    std::cin >> plan;
    robot = CS170::Robot::Create(rx,ry,Char2orientation(ch_o),field);
    return true;
}

int main () {
    std::cout << "enter field dimensions: ";
    int dim1, dim2;
    std::cin >> dim1 >> dim2;
    int * last_positions = new int[ dim1*dim2 ]; // flat array
    CS170::Grid::Instance field = CS170::Grid::Create( dim1, dim2 );
    for ( int i=0; i<dim1; ++i ) { // horisontal offset (to the right)
        for ( int j=0; j<dim2; ++j ) { // vertical offset (down)
            last_positions[ i*dim2 + j ] = -1; // // -1 means unoccupied
        }
    }
    CS170::Robot::Instance robot;
    std::string plan;
    int counter = 1;
    while ( InitRobot(field,robot,plan) ) {
        int x=-1,y=-1;
        CS170::Robot::Orientation o;
        int plan_size = plan.size();
        for (int i=0;i<plan_size;++i) {
            //uncomment for testing
            //bool alive = QueryPosition(robot,&x,&y,&o);
            //std::cout << "robot position is " << x << " " << y << " " << Orientation2char(o);
            //if (!alive)  std::cout << " lost";
            //std::cout << std::endl << "moving " << plan[i] << std::endl;
            ///////////////////
            Move(robot,plan[i]);
        }
        bool alive = QueryPosition(robot,&x,&y,&o);
        std::cout << "robot final position " << x << " " << y << " " << Orientation2char(o);
        if (!alive) { 
            std::cout << " lost";
        } else {
            last_positions[ x*dim2 + y ] = counter; // record last robot's position
            ++counter;
        }
        std::cout << std::endl;
        Destroy(robot);
    };

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
            if ( Marked( field, i, j ) ) {
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


    Destroy(field);
    delete [] last_positions;
    return 0;
}
