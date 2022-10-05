#include "rational.h"
#include <iomanip>  // setw
#include <cstdlib>  // abs
/*!*****************************************************************************
\file    rational.cpp
\author  Anthon Reid
\par     DP email:  anthon.reid@digipen.edu
\par     Course: CS120
\par     Assignment #3
\date    01-31-2022

\brief
This uses a class and performs various tasks on robot via several
separate functions to create, move and destroy a robot.

*******************************************************************************/
#include "rational.h"
#include <iomanip>  // std::setw

namespace CS170 {


    int Rational::width = 0; // no padding by default

    /*!*****************************************************************************

     \brief
     Default Constructor

     \param Rational
     reference to a contant rational object

     \return
     none
     *******************************************************************************/
    Rational::Rational()               : n(0),  d(1)   
    {


    }
    
    /*!*****************************************************************************

     \brief
     Constructor that sets the numerator of the fraction

     \param Rational
     reference to a contant rational object

     \return
     none
     *******************************************************************************/
    Rational::Rational( int i )        : n(i),  d(1)   
    {
    
    }
    
    /*!*****************************************************************************

    \brief
    Constructor that sets the sign and gdc of the fraction

    \param instance
    A pointer the robot structure to be destroyed.

    \return
    None
    *******************************************************************************/
    Rational::Rational(int _n, int _d) : n(_n), d(_d) 
    {
        CheckSign(); 
        CheckGCD();
    }
    
    /*!*****************************************************************************

    \brief
    Oveloads the - operator

    \param Rational
    reference to a contant rational object

    \return
    none
    *******************************************************************************/
    Rational Rational::operator- () const
    {
        return Rational(-n,d); 
    }

    /*!*****************************************************************************

    \brief
    Oveloads the += operator

    \param Rational
    reference to a contant rational object

    \return
    none
    *******************************************************************************/
    Rational& Rational::operator+= (const Rational& r) 
    {
        n = (n * r.denominator()) + (r.numerator() * d);
        d = d * r.denominator();
        CheckSign();
        CheckGCD();

        return *this;
    }

    /*!*****************************************************************************

    \brief
    Oveloads the + operator

    \param Rational
    reference to a contant rational object

    \return
    none
    *******************************************************************************/
    Rational Rational::operator+ (const Rational& r) const
    {
        Rational result(n,d);

        result += r;

        return result;
    }

    /*!*****************************************************************************

    \brief
    Oveloads the - operator

    \param Rational
    reference to a contant rational object

    \return
    none
    *******************************************************************************/
    Rational Rational::operator- (const Rational& r) const
    {
        Rational result(n, d);
        result += (-r);

        return result;
    }

    /*!*****************************************************************************

    \brief
    Oveloads the -= operator

    \param Rational
    reference to a contant rational object

    \return
    none
    *******************************************************************************/
    Rational& Rational::operator-= (const Rational& r) 
    {
        *this += (-r);

        return *this;
    }

    /*!*****************************************************************************

    \brief
    Oveloads the *= operator

    \param Rational
    reference to a contant rational object

    \return
    none
    *******************************************************************************/
    Rational& Rational::operator*= (const Rational& r)
    {
        n =  n * r.numerator();
        d = d * r.denominator();
        CheckSign();
        CheckGCD();

        return *this;
    }

    /*!*****************************************************************************

     \brief
     Oveloads the * operator

     \param Rational
     reference to a contant rational object

     \return
     none
     *******************************************************************************/
    Rational Rational::operator* (const Rational& r) const
    {
        Rational result(n, d);
        result *= r;

        return result;
    }

    /*!*****************************************************************************

    \brief
    Oveloads the /= operator

    \param Rational
    reference to a contant rational object

    \return
    none
    *******************************************************************************/
    Rational& Rational::operator/= (const Rational& r)
    {
        n = n * r.denominator();
        d = d * r.numerator();
        CheckSign();
        CheckGCD();

        return *this;
    }

    /*!*****************************************************************************

    \brief
    Oveloads the / operator

    \param Rational
    reference to a contant rational object

    \return
    none
    *******************************************************************************/
    Rational Rational::operator/ (const Rational& r) const
    {
        Rational result(n, d);
        result /= r;

        return result;
    }


    /*!*****************************************************************************

    \brief
    Oveloads the < operator
 
    \param Rational
    reference to a contant rational object

    \return
    returns a rational less than this
    *******************************************************************************/
    bool Rational::operator< ( Rational const & op2 ) const 
    { 
        return (n*op2.d < d*op2.n); 
    }

    /*!*****************************************************************************

    \brief
    Oveloads the == operator

    \param Rational
    reference to a contant rational object

    \return
    returns a rational equal to this
    *******************************************************************************/
    bool Rational::operator== (const Rational& r) const
    {
        return (n == r.numerator() && d == r.denominator());
    }

    /*!*****************************************************************************

     \brief
     Oveloads the <= operator

     \param Rational
     reference to a contant rational object

     \return
     returns a a rational less or equal to this
     *******************************************************************************/
    bool Rational::operator<= (const Rational& r) const
    {
        return (*this < r || *this == r );
    }
    
    /*!*****************************************************************************

   \brief
   Oveloads the > operator

   \param Rational
   reference to a contant rational object

   \return
   returns a rational greater than this
   *******************************************************************************/
    bool Rational::operator> (const Rational& r) const
    {
        return !(*this <= r);
    }

    /*!*****************************************************************************

    \brief
    Oveloads the >= operator

    \param Rational
    reference to a contant rational object

    \return
    returns a rational greater or equal to this
    *******************************************************************************/
    bool Rational::operator>= (const Rational& r) const
    {
        return !(*this < r);
    }

    /*!*****************************************************************************

   \brief
   Oveloads the != operator

   \param Rational
   reference to a contant rational object

   \return
   returns a rational not  equal to this
   *******************************************************************************/
    bool Rational::operator!= (const Rational& r) const
    {
        return !(*this == r);
    }

    /*!*****************************************************************************

    \brief
    Oveloads the << operator

    \param ostream
    reference to a stream to print out the franctions
    
    \param Rational
    reference to a contant rational object

    \return
    None
    *******************************************************************************/
    std::ostream& operator<<( std::ostream& os, Rational const& r ) 
    {
        os << std::setw( r.width ) << r.n;
        if ( r.d != 1 ) { os << "/" << std::setw( r.width-1 ) << r.d; }
        else            { os <<        std::setw( r.width ) << " "; }
        return os;
    }
    
    /*!*****************************************************************************

     \brief
     Check the sign of the fraction

     \param None

     \return
     None
     *******************************************************************************/
    void Rational::CheckSign() 
    {
        if ( d<0 ) { n *= -1; d*= -1; }
    }
   
    /*!*****************************************************************************

    \brief
    Check the GDC of the fraction

    \param None

    \return
    None
    *******************************************************************************/
    void Rational::CheckGCD() 
    {
        int gcd = GCD();
        n = n/gcd;
        d = d/gcd;
    }


    // Euclid's algorithm
    int Rational::GCD() const 
    {
        int a=std::abs(n), b=std::abs(d);
        while ( a && b ) {
            if ( a < b ) { b = b%a; }
            else         { a = a%b; }
        }
        if ( a==0 ) return b;
        else        return a;
    }
}