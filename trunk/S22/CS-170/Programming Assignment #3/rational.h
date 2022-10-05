#ifndef RATIONAL_H
#define RATIONAL_H
#include <fstream>  // std::fstream
#include <cstdlib>  // std::abs

namespace CS170 {
    class Rational {
        private:
            int n,d;
            static int width; // used by stream insertion, do not change
            ////////////////////////////////////////////////////////////////////////
            void CheckSign();
            void CheckGCD();
            int  GCD() const;
        public:
            int numerator() const { return n; }
            int denominator() const { return d; }

            // set width for 
            static void Width( int w );

            ////////////////////////////////////////////////////////////////////////
            friend std::ostream& operator<<( std::ostream& os, Rational const& r );

            Rational();

            Rational(int);

            Rational(int, int);


            // unary negate
            Rational operator- () const;
            
            Rational& operator+= (const Rational& r);

            Rational operator+ (const Rational& r) const;

            Rational operator- (const Rational& r) const;

            Rational& operator-= (const Rational& r);

            Rational& operator*= (const Rational& r);

            Rational operator* (const Rational& r) const;

            Rational& operator/= (const Rational& r);

            Rational operator/ (const Rational& r) const;


            ////////////////////////////////////////////////////////////////////////
            // comparisons
            bool operator< ( Rational const& op2 ) const;

            bool operator== (const Rational& r) const;

            bool operator<= (const Rational& r) const;

            bool operator>= (const Rational& r) const;
            
            bool operator> (const Rational& r) const;

            bool operator!= (const Rational& r) const;


            // ....
            ////////////////////////////////////////////////////////////////////////

    };
}
#endif
