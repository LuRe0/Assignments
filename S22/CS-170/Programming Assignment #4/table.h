#ifndef TABLE_H
#define TABLE_H

#include <string>
#include <fstream>
#include <iostream>

namespace CS170 {
    class Table {
        // ...

        public:
        // constructor
            Table();
            Table(unsigned int r, unsigned int c);
            ~Table();
            Table(Table const& t);
            Table& operator=(Table const& t);

        // getter and setter (overloaded similar to operator[] from notes)
        std::string       & operator () ( unsigned int r, unsigned int c );
        std::string const & operator () ( unsigned int r, unsigned int c ) const;
        
     
        Table operator+(const Table& t) const;
        Table operator*(const Table& t) const;

        void Reverse(unsigned int r, unsigned int c);
        void Reverse(unsigned int r);
        void Reverse();


        // ...

        void Display( std::ostream & os ) const;    // provided
        void Display2( std::ostream & os ) const;   // fancy    (10% of your grade)


        private:
            std::string** string_;
            unsigned int Rows_;
            unsigned int Cols_;

            void createArray(unsigned int rows, unsigned int cols);
            void deleteArray();
            void copyArray(unsigned int rows, unsigned int cols, const Table& original) const;
    };

    std::ostream & operator<<( std::ostream & os, Table const& t );
}
#endif
