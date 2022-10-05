/*!*****************************************************************************
\file    functions.cpp
\author  Anthon Reid
\par     DP email:  anthon.reid@digipen.edu
\par     Course: CS170
\par     Assignment #5
\date    03-1-2022

\brief
This uses a class and performs various tasks on string table via several
separate functions to create, concatenate and destroy the table.

*******************************************************************************/
#include <iostream>
#include "functions.h"

namespace CS170 {
      /*!*****************************************************************************

     \brief
     pointer to the *first* element in the range that is equal to a given value

     \param T
     reference to the begining of the arrray
     \param T
     reference to the end of the arrray


     \return
     none
     *******************************************************************************/
  template <typename T>
    void display( T const *begin, T const *end )
    {
      if( begin != end ) std::cout << *begin++;
      while( begin<end ) {
        std::cout << ", " << *begin;
        ++begin;
      }
      std::cout << std::endl;
    }
    /*!*****************************************************************************

     \brief
     pointer to the *first* element in the range that is equal to a given value

     \param T
     reference to the begining of the arrray
     \param T
     reference to the end of the arrray
     \param T
     reference to the value to be found

     \return
     none
     *******************************************************************************/
  template <typename T>
    void swap( T *left, T *right )
    {
      T temp( *right );
      ( *right ) = ( *left );
      ( *left ) = temp;
    }
    /*!*****************************************************************************

     \brief
     pointer to the *first* element in the range that is equal to a given value

     \param T
     reference to the begining of the arrray
     \param T
     reference to the end of the arrray
     \param T
     reference to the value to be found

     \return
     the min value of the array
     *******************************************************************************/
  template <typename T>
    T* min_element( T *begin, T *end )
    {
      T* min=begin;
      while( begin!=end ) {
        if( *begin<*min ) min=begin;
        ++begin;
      }
      return min;
    }
    /*!*****************************************************************************

     \brief
     pointer to the *first* element in the range that is equal to a given value

     \param T
     reference to the begining of the arrray
     \param T
     reference to the end of the arrray
     \param T
     reference to the value to be found

     \return
     the min value of the array
     *******************************************************************************/
  template <typename T>
    T const* min_element( T const *begin, T const *end )
    {
      T const* min=begin;
      while( begin!=end ) {
        if( *begin<*min ) min=begin;
        ++begin;
      }
      return min;
    }

    /*!*****************************************************************************

     \brief
     pointer to the *first* element in the range that is equal to a given value

     \param T
     reference to the begining of the arrray
     \param T
     reference to the end of the arrray
     \param T
     reference to the value to be found

     \return
     none
     *******************************************************************************/
  template <  typename T  >
    void swap_ranges( T * begin,  T * end, T * begin2)
    {
     while (begin != end)
     {
       /*swaps the two pointers*/
      swap(begin, begin2);
       begin ++;
       begin2 ++;
     }

    }


    /*!*****************************************************************************

     \brief
     remove specified value from the range

     \param T
     reference to the begining of the arrray
     \param T
     reference to the end of the arrray
     \param T
     reference to the value to be found

     \return
     the end of the array
     *******************************************************************************/
  template <typename T>
    T* remove( T * begin,  T * end, T value )
    {
      T* temp = begin;
      while (temp != end && begin != end)
      {
        /*if the value is found*/
        if(*(temp) == value)
        {
          while (temp != end-1)
          {
            /*shift the array back*/
            *temp = *(temp+1);
            ++temp;
          }
          /*shrink the array*/
          --end;
          temp = begin;
        }
        temp++;
      }

        if(*begin == value )
        {
            end--;
        }
    
      return end;
    }


    /*!*****************************************************************************

     \brief
      overwrite all elements in the range with a given value

     \param T
     reference to the begining of the arrray
     \param T
     reference to the end of the arrray
     \param T
     reference to the value to be found

     \return
     none
     *******************************************************************************/
  template <typename T>
    void fill(T * begin,  T * end , T value )
    {
      while (begin != end)
     {
       /*set the pointers value to the wanted one */
        *begin = value;
    
       begin ++;
     }
    }
    /*!*****************************************************************************

     \brief
     count elements that are equal to a given value 

     \param T
     reference to the begining of the arrray
     \param T
     reference to the end of the arrray
     \param T
     reference to the value to be found

     \return
     the count of the array
     *******************************************************************************/
  template <typename T>
   T count(T const * begin,  T const * end , T value)
   {
     T count = 0;
      while (begin != end)
     {
       if(*begin == value)
       {
         /* increment teh count based on if the value is found */
         ++ count;
       }
       begin ++;
     }

     return count;
   }

       /*!*****************************************************************************

     \brief
     add all element of the array together

     \param T
     reference to the begining of the arrray
     \param T
     reference to the end of the arrray

     \return
     the sum of the array
     *******************************************************************************/
  template < typename T> 
    T sum(T const *begin, T const *end  )
    {
      T sum = 0;

    while (begin != end)
        {
          /* increment the sum as the array moves forward */
          sum += *begin;
          begin ++;
        }

        return sum;
    }

     /*!*****************************************************************************

     \brief
    copy all elements from first range into second

     \param T
     reference to the begining of the arrray
     \param T
     reference to the end of the arrray
     \param T2
     reference to the Beginnign of the second array

     \return
     the end of the array
     *******************************************************************************/
  template <typename T1, typename T2>
   T2* copy(T1 const* begin,  T1 const * end, T2 *begin2)
   {
     while (begin != end)
     {
       /* fill the second array with the first */
       *begin2 = *begin;
       begin ++;
       begin2++;
     }

     return begin2;
   }



    /*!*****************************************************************************

     \brief
     compare 2 ranges, similar to copy you compare each element of the first range to a 
     corresponding element of the second. 

     \param T
     reference to the begining of the arrray
     \param T
     reference to the end of the arrray
     \param T2
     reference to the Beginnign of the second array

     \return
     the end of the array
     *******************************************************************************/
  template <typename T1, typename T2>
    bool equal( T1 const *begin, T1 const *end , T2 const * begin2)
    {
      while (begin != end)
      {
        if(*begin != *begin2)
        {
          /*if a the arrays do not match */
          return false;
        }
        ++begin;
        ++begin2;
      }
      /* otherwise return true */
      return true;
  }
    /*!*****************************************************************************

     \brief
      replace all elements in the range that are equal to old_value with a given value

     \param T
     reference to the begining of the arrray
     \param T
     reference to the end of the arrray
     \param T
     reference to the value to be found

     \return
     the end of the array
     *******************************************************************************/
  template <typename T>
    void replace( T  *begin, T  *end , T  old_value, T  new_value)
    {
      T* temp = begin;
      while (temp != end)
      {
        if(*temp == old_value)
        {
          /* if the old value is found, replace with new value */
          *temp = new_value;
        }
          ++temp;
      }
    }

    /*!*****************************************************************************

     \brief
    pointer to the largest element.

     \param T
     reference to the begining of the arrray
     \param T
     reference to the end of the arrray
     \param T
     reference to the value to be found

     \return
     the end of the array
     *******************************************************************************/
    template <typename T>
    T* max_element(T * begin,  T * end  )
    {
      T * max = begin;
      while( begin != end ) {
        if( *begin>*max )
        {
          /* update the max value if begin if greater than it */
           max = begin;
        }
        ++begin;
      }
      return max;
    }

    /*!*****************************************************************************

     \brief
      pointer to the *first* element in the range that is equal to a given value

     \param T
     reference to the begining of the arrray
     \param T
     reference to the end of the arrray
     \param T
     reference to the value to be found

     \return
     the beginning of the array
     *******************************************************************************/
  template <typename T>
  const T* find(T const* begin,  T const *  end , T const value ) 
    {
      while (begin != end)
      {
        if(*begin == value)
        {
          /* return the pointer if the value is there */
          return begin;
        }
        ++ begin;
      }
      return begin;
    }
    /*!*****************************************************************************

     \brief
     pointer to the *first* element in the range that is equal to a given value

     \param T
     reference to the begining of the arrray
     \param T
     reference to the end of the arrray
     \param T
     reference to the value to be found

     \return
     the beginning of the array
     *******************************************************************************/
  template <typename T>
    T* find(T * begin,  T * end , T value )
    {
      while (begin != end)
      {
        if(*begin == value)
        {
          
          /* return the pointer if the value is there */
          return begin;
        }
        ++ begin;
      }
      return begin;
    }
}
