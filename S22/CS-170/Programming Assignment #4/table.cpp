/*!*****************************************************************************
\file    table.cpp
\author  Anthon Reid
\par     DP email:  anthon.reid@digipen.edu
\par     Course: CS170
\par     Assignment #4
\date    01-31-2022

\brief
This uses a class and performs various tasks on string table via several
separate functions to create, concatenate and destroy the table.

*******************************************************************************/

#include "table.h"
#include <iomanip>
#include <algorithm>
namespace CS170 {

    /*!*****************************************************************************

     \brief
     Default Constructor

     \param Rational
     reference to a contant table object

     \return
     none
     *******************************************************************************/
    Table::Table()
    {
        //set row and column to 1
        Rows_ = 1;
        Cols_ = 1;

        // creates a basic table of row 1 col 1
        createArray(Rows_, Cols_);  // rows with data
       
    }
    /*!*****************************************************************************

     \brief
     Default Constructor that set the table to to the desired dimensions

     \param int
     reference to a number of rows
     
     \param int
     reference to a number of columns

     \return
     none
     *******************************************************************************/
    Table::Table(unsigned int r, unsigned int c)
    {
        //set rows and columns to the desired dimensions
        Rows_ = r;
        Cols_ = c;

        // creates a table based on those criteria
        createArray(Rows_, Cols_);
    }

    /*!*****************************************************************************

    \brief
    Destructor

    \return
    None
    *******************************************************************************/
    Table::~Table()
    {
        deleteArray();
    }
     /*!*****************************************************************************

     \brief
     Default copy Constructor

     \param Table
     reference to a constant table object

     \return
     none
     *******************************************************************************/
    Table::Table(Table const& rhs)
    {
        //sets the copy's row and column to that of the original table.
        Rows_ = rhs.Rows_;
        Cols_ = rhs.Cols_;

        //create a new array
        createArray(Rows_, Cols_);

        //transfer the data from the original array to the copy.
        copyArray(Rows_, Cols_, rhs);


    }

    /*!*****************************************************************************

    \brief
    Default assignment Constructor

    \param Table
    reference to a constant table object

    \return
    A table instance
    *******************************************************************************/
    Table& Table::operator=(Table const& rhs)
    {
        //if the table are the same return
        if (string_ == rhs.string_)
        {
            return *this;
        }
        
        else
        {
            //delete the  old array
            deleteArray();

            //set its new size to the new table
            Rows_ = rhs.Rows_;
            Cols_ = rhs.Cols_;


            //copy the values over to the string
            string_ = new std::string * [Rows_]; // pointers to rows
            for (unsigned int r = 0; r < Rows_; ++r)
            {
                string_[r] = new std::string[Cols_]();  // rows with data

                for (unsigned int c = 0; c < Cols_; ++c)
                {
                    string_[r][c] = rhs.string_[r][c];
                }
            }

            //return the string
            return *this;
        }   
    }


    /*!*****************************************************************************

    \brief
     Operator that gets a [row][column] position on the table

    \param Table
    reference to a constant table object

    \return
    A position on the table
    *******************************************************************************/
    std::string& Table::operator()(unsigned int r, unsigned int c) {
        return string_[r][c];
    }

    /*!*****************************************************************************

    \brief
     Operator that gets a [row][column] position on the table

    \param Table
    reference to a constant table object

    \return
    A position on the table
    *******************************************************************************/
    std::string const& Table::operator()(unsigned int r, unsigned int c) const {
        return string_[r][c];
    }

    
    /*!*****************************************************************************

    \brief
     Reverses a string at a certain position on the table.

    \param int
     reference to a number of rows
     
     \param int
     reference to a number of columns

    \return
    none
    *******************************************************************************/
    void Table::Reverse(unsigned int r, unsigned int c)
    {
        //create a temp string
        std::string temp = string_[r][c];

        //swap the string using std reverse
        std::reverse(temp.begin(), temp.end());

        //set the string value to temp
        string_[r][c] = temp;
    }

    /*!*****************************************************************************

    \brief
     Reverses the rows of the table.

    \param int
     reference to a number of rows

    \return
    none
    *******************************************************************************/
    void Table::Reverse(unsigned int r)
    {
        //allocate memory to a temp string and copy the old string to it 
        std::string** temp = new std::string * [Rows_]; // pointers to rows
        for (unsigned int r = 0; r < Rows_; ++r)
        {
            temp[r] = new std::string[Cols_]();  // rows with data

            for (unsigned int c = 0; c < Cols_; ++c)
            {
                temp[r][c] = string_[r][c];
            }
        }

        //swaps the values of the string using temp
        int c = Cols_ - 1;
        for (unsigned int j = 0; j <  Cols_; ++j)
        {
            string_[r][j] = temp[r][c];
            --c;
        }

        //delete the temporary string
        for (unsigned int r = 0; r < Rows_; ++r)
        {
            delete[] temp[r];
        }
        delete[] temp;

    }

    /*!*****************************************************************************

    \brief
     Transposes the table.

    \return
    none
    *******************************************************************************/
    void Table::Reverse()
    {
        //allocate memory to a temp string and copy the string 
        std::string ** temp = new std::string * [Cols_]; // pointers to rows
        for (unsigned int c = 0; c < Cols_; ++c)
        {
            temp[c] = new std::string[Rows_]();  // rows with data

            for (unsigned int r = 0; r < Rows_; ++r) {

                temp[c][r] = string_[r][c];
            }
        }

        //delete the old string
        deleteArray();

        //swap the rows and columns
        int temporaire = Rows_;
        Rows_ = Cols_;
        Cols_ = temporaire;

        //add the temp to the string
        string_ = temp;


    }


    /*!*****************************************************************************

    \brief
     This method puts one table "over" the other to merge into a larger table.

    \param Table
    reference to a constant table object

    \return
    A table instance
    *******************************************************************************/
    Table Table::operator+(const Table& t) const
    {
        //create a table with a the correct dimensions
        Table table(std::max(Rows_, t.Rows_), std::max(Cols_, t.Cols_));

        //adds the old arrays to the new one 
        table.copyArray(Rows_, Cols_, *this);

        table.copyArray(t.Rows_, t.Cols_, t);
     
       
        //return the new anime
        return table;
    }



    /*!*****************************************************************************

    \brief
     This method multiplies the element of the first table  by the whole second table.

    \param Table
    reference to a constant table object

    \return
    A table instance
    *******************************************************************************/
    Table Table::operator*(const Table& t) const
    {
        //uses the tensor method to delinearte what the operator does
        Table table((Rows_*t.Rows_), (Cols_*t.Cols_));

        for (size_t i = 0; i < Rows_; ++i)
        {
            for (size_t j = 0; j < Cols_; ++j)
            {
                for (size_t k = 0; k < t.Rows_; ++k)
                {
                    for (size_t l = 0; l < t.Cols_; ++l)
                    {
                        table.string_[i * t.Rows_ + k][j * t.Cols_ + l] = string_[i][j] + t.string_[k][l];
                    }
                }
            }
        }

        return table;
    }



    /*!*****************************************************************************

    \brief
     This method displays a simple table

    \param osStream
    reference to the cout

    \return
    none
    *******************************************************************************/

    void Table::Display( std::ostream & os ) const
    {
        for( unsigned int r=0; r<Rows_; ++r ) {
            for( unsigned int c=0; c<Cols_; ++c ) {
                os << string_[r][c] << " ";
            }
            os << std::endl;
        }
    }


    /*!*****************************************************************************

    \brief
     This method displays a fancy table

    \param osStream
    reference to the cout

    \return
    none
    *******************************************************************************/

    void Table::Display2( std::ostream & os ) const
    {
        //allocate an array to hold the max table size
        int* tableSize = new int [Cols_]();
        if (tableSize)
        {
            for (unsigned int c = 0; c < Cols_; ++c)
            {
                for (unsigned int r = 0; r < Rows_; ++r)
                {
                    if (tableSize[c] < (int)string_[r][c].length())
                    {
                        tableSize[c] = (int)string_[r][c].length();
                    }
                }
            }


            //prints the table borders
            for (unsigned int r = 0; r <= Rows_; ++r)
            {

                for (unsigned int c = 0; c <= Cols_; ++c)
                {
                    if (c < Cols_)
                    {
                        os << std::setfill('-');
                        os << "+" << std::setw(tableSize[c] + 3);
                        if (tableSize[c] == 0)
                        {
                            os << std::setfill('-');
                            os << std::setw(0);
                        }
                    }
                }
                os << std::setfill('-');
                os << "+";
                os << std::endl;

                //add the string inside the table borders
                if (r < Rows_)
                {
                    for (unsigned int j = 0; j <= Cols_; ++j)
                    {
                        os << std::setfill(' ') << std::setw(0);
                        os << "|";
                        if (r < Rows_ && j < Cols_)
                        {
                            os << std::right << std::setw(tableSize[j] + 1) << string_[r][j] << " ";
                        }
                    }
                    os << std::endl;
                }
            }
        }

        //delete the array
        delete[] tableSize;
    }

    /*!*****************************************************************************

    \brief
     This method determines what the >> operator does

    \param osStream
    reference to the cout

    \param Table
    reference to a constant table object


    \return
    A ostream instance
    *******************************************************************************/
    std::ostream & operator<<(std::ostream & os, Table const & t)
    {
        //t.Display2( os );   // fancy (see fancy_out* )
        t.Display( os );   // simple (see out* )

        return os;
    }

    //Private Functions:

    /*!*****************************************************************************

    \brief
     This method creates a simple string array

     \param int
     reference to a number of rows

     \param int
     reference to a number of columns

    \return
    none
    *******************************************************************************/
    void Table::createArray(unsigned int rows, unsigned int cols)
    {
        //allocate a 2d array
        string_ = new std::string* [rows]; // pointers to rows
        for (unsigned int r = 0; r < rows; ++r)
        {
            string_[r] = new std::string[cols]();  // rows with data
        }
    }


    /*!*****************************************************************************

    \brief
     This method destroys a simple string array


    \return
    none
    *******************************************************************************/
    void Table::deleteArray()
    {
        //deletes the string array
        for (unsigned int r = 0; r < Rows_; ++r)
        {
            delete[] string_[r];
        }
        delete[] string_;
    }


    /*!*****************************************************************************

     \brief
     This method clones a string array

     \param int
     reference to a number of rows

     \param int
     reference to a number of columns

     \param Table
     reference to a constant table object

    \return
    none
    *******************************************************************************/
    void Table::copyArray(unsigned int rows, unsigned int cols, const Table& original) const
    {
        //transfer the data from the original array to the copy.
        for (unsigned int r = 0; r < rows; ++r) {
            for (unsigned int c = 0; c < cols; ++c) {
                string_[r][c] += original.string_[r][c];
            }
        }

    }
}
