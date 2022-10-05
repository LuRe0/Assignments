/*!*****************************************************************************
\file    rational.cpp
\author  Anthon Reid
\par     DP email:  anthon.reid@digipen.edu
\par     Course: CS120
\par     Assignment #6
\date    04-07-2022

\brief
This uses a class and performs various tasks on rational class through overloaded
funtions
*******************************************************************************/
#include "rational.h"
#include <iomanip>  // setw
#include <cstdlib>  // abs


namespace CS170 {

    template < typename T> 
    int Rational<T>::width = 0; // no padding by default

    ////////////////////////////////////////////////////////////////////////
    template < typename T> 
    Rational<T>::Rational()               : n(0),  d(1)   {}
    ////////////////////////////////////////////////////////////////////////
    template < typename T> 
    Rational<T>::Rational( T i )        : n(i),  d(1)   {}
    ////////////////////////////////////////////////////////////////////////
    template < typename T> 
    Rational<T>::Rational(T _n, T _d) : n(_n), d(_d)  { CheckSign(); CheckGCD(); }

    
    
    // ....
        /*!*****************************************************************************

    \brief
    Oveloads the - operator

    \param Rational<T>
    reference to a contant rational object

    \return
    none
    *******************************************************************************/
    template < class T> 
    Rational<T> Rational<T>::operator- () const
    {
        return Rational(-n,d); 
    }

    /*!*****************************************************************************

    \brief
    Oveloads the += operator

    \param Rational<T>
    reference to a contant rational object

    \return
    none
    *******************************************************************************/
    template < class T>
    Rational<T>& Rational<T>::operator+= (Rational<T> const& r)
    {
        n = (n * r.d) + (r.n * d);
        d = d * r.d;
        CheckSign();
        CheckGCD();

        return *this;
    }

    /*!*****************************************************************************

    \brief
    Oveloads the + operator

    \param Rational<T>
    reference to a contant rational object

    \return
    none
    *******************************************************************************/
    template < class T>
    Rational<T> Rational<T>::operator+ (Rational<T> const& r) const
    {
        Rational result(n, d);

        result += r;

        return result;
    }

    /*!*****************************************************************************

    \brief
    Oveloads the - operator

    \param Rational<T>
    reference to a contant rational object

    \return
    none
    *******************************************************************************/
    template < class T>
    Rational<T> Rational<T>::operator- (Rational<T> const& r) const
    {
        Rational result(n, d);
        result += (-r);

        return result;
    }

    /*!*****************************************************************************

    \brief
    Oveloads the -= operator

    \param Rational<T>
    reference to a contant rational object

    \return
    none
    *******************************************************************************/
    template < class T>
    Rational<T>& Rational<T>::operator-= (Rational<T> const& r)
    {
        *this += (-r);

        return *this;
    }

    /*!*****************************************************************************

    \brief
    Oveloads the *= operator

    \param Rational<T>
    reference to a contant rational object

    \return
    none
    *******************************************************************************/
    template < class T>
    Rational<T>& Rational<T>::operator*= (Rational<T> const& r)
    {
        n = n * r.n;
        d = d * r.d;
        CheckSign();
        CheckGCD();

        return *this;
    }

    /*!*****************************************************************************

     \brief
     Oveloads the * operator

     \param Rational<T>
     reference to a contant rational object

     \return
     none
     *******************************************************************************/
    template < class T>
    Rational<T> Rational<T>::operator* (Rational<T> const& r) const
    {
        Rational result(n, d);
        result *= r;

        return result;
    }

    /*!*****************************************************************************

    \brief
    Oveloads the /= operator

    \param Rational<T>
    reference to a contant rational object

    \return
    none
    *******************************************************************************/
    template < class T>
    Rational<T>& Rational<T>::operator/= (Rational<T> const& r)
    {
        n = n * r.d;
        d = d * r.n;
        CheckSign();
        CheckGCD();

        return *this;
    }

    /*!*****************************************************************************

    \brief
    Oveloads the / operator

    \param Rational<T>
    reference to a contant rational object

    \return
    none
    *******************************************************************************/
    template < class T>
    Rational<T> Rational<T>::operator/ (Rational<T> const& r) const
    {
        Rational result(n, d);
        result /= r;

        return result;
    }


    /*!*****************************************************************************

    \brief
    Oveloads the < operator

    \param Rational<T>
    reference to a contant rational object

    \return
    returns a rational less than this
    *******************************************************************************/
    template < class T>
    bool Rational<T>::operator< (Rational<T> const& op2) const
    {
        return (n * op2.d < d* op2.n);
    }

    /*!*****************************************************************************

    \brief
    Oveloads the == operator

    \param Rational<T>
    reference to a contant rational object

    \return
    returns a rational equal to this
    *******************************************************************************/
    template < class T>
    bool Rational<T>::operator== (Rational<T> const& r) const
    {
        return (n == r.n && d == r.d);
    }

    /*!*****************************************************************************

     \brief
     Oveloads the <= operator

     \param Rational<T>
     reference to a contant rational object

     \return
     returns a a rational less or equal to this
     *******************************************************************************/
    template < class T>
    bool Rational<T>::operator<= (Rational<T> const& r) const
    {
        return (*this < r || *this == r);
    }

    /*!*****************************************************************************

   \brief
   Oveloads the > operator

   \param Rational<T>
   reference to a contant rational object

   \return
   returns a rational greater than this
   *******************************************************************************/
    template < class T>
    bool Rational<T>::operator> (Rational<T> const& r) const
    {
        return !(*this <= r);
    }

    /*!*****************************************************************************

    \brief
    Oveloads the >= operator

    \param Rational<T>
    reference to a contant rational object

    \return
    returns a rational greater or equal to this
    *******************************************************************************/
    template < class T>
    bool Rational<T>::operator>= (Rational<T> const& r) const
    {
        return !(*this < r);
    }

    /*!*****************************************************************************

   \brief
   Oveloads the != operator

   \param Rational<T>
   reference to a contant rational object

   \return
   returns a rational not  equal to this
   *******************************************************************************/
    template < class T>
    bool Rational<T>::operator!= (Rational<T> const& r) const
    {
        return !(*this == r);
    }

    


    ////////////////////////////////////////////////////////////////////////
    template < typename U> 
    std::ostream& operator<<( std::ostream& os, Rational<U> const& r ) {
        os << std::setw( r.width ) << r.n;
        if ( r.d != 1 ) { os << "/" << std::setw( r.width-1 ) << r.d; }
        else            { os <<        std::setw( r.width ) << " "; }
        return os;
    }
    ////////////////////////////////////////////////////////////////////////
    template < typename T> 
    void Rational<T>::CheckSign() {
        if ( d<0 ) { n *= -1; d*= -1; }
    }
    ////////////////////////////////////////////////////////////////////////
    template < typename T> 
    void Rational<T>::CheckGCD() {
        int gcd = GCD();
        n = n/gcd;
        d = d/gcd;
    }
    ////////////////////////////////////////////////////////////////////////
    template < typename T> 
    int Rational<T>::GCD() const {
        int a=std::abs(n), b=std::abs(d);
        while ( a && b ) {
            if ( a < b ) { b = b%a; }
            else         { a = a%b; }
        }
        if ( a==0 ) return b;
        else        return a;
    }
}
