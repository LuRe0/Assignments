#include <iostream>             // cout
#include <cstdlib>              // abort
#include "Vector.h"

namespace CS170 {

  Vector::Vector( void ) 
  {
    array_ =  NULL;
    size_ =  0;
    capacity_ =  0;
    allocs_ =  0;
  } 


  Vector::~Vector()
  {
      delete[] array_;
  }

  // Copy constructor
  Vector::Vector(Vector const& rhs)
  {
      capacity_ = rhs.size_;
      array_ = new int[capacity_];
      size_ = rhs.size_;
      allocs_ = 1;  

      for (unsigned int i = 0; i < rhs.size_; i++)
      {
          array_[i] = rhs.array_[i];
      }
  }

  // Assignment operator
  Vector& Vector::operator=(Vector const& rhs)
  { 
      if (capacity_ < rhs.size_)
      {
          delete[] array_;
          capacity_ = rhs.size_;
          array_ = new int[capacity_];
          size_ = rhs.size_;
          allocs_ = rhs.allocs_;
      }
      else
      {
          size_ = rhs.size_;
      }

      for (unsigned int i = 0; i < rhs.size_; i++)
      {
          array_[i] = rhs.array_[i];
      }

      return *this;
  }

  // Constructor to create a Vector from an array
  Vector::Vector(int const array[], unsigned size)
  {
      size_ = size;
      capacity_ = size;
      allocs_ = 1;
      array_ = new int[size];
      for (unsigned int i = 0; i < size; ++i)
      {
          array_[i] = array[i];
      } 
  }

  // Adds a node to the front of the list
  void Vector::push_back(int value)
  {
      if (size_ >= capacity_)
      {
          grow();
      }

      array_[size_] = value;

      ++size_;
  }

  // Adds a node to the end of the list
  void Vector::push_front(int value)
  {
      if (size_ >= capacity_ || array_ == NULL)
      {
          grow();
      }

      //for (int i = size_ - 1 ; i >= 0; --i)
      //{
      //    array_[i + 1] = array_[i];
      //}
      array_[0] = value;
      ++size_;
  }

  // Removes the last element. Does nothing if empty.
  void Vector::pop_back()
  {
      if (size_ == 0)
      {
          abort();
      }
      else
      {
            size_ -= 1;
      }
  }

  // Removes the first element. Does nothing if empty.
  void Vector::pop_front()
  {
      if (size_ == 0)
      {
          abort();
      }
      else
      {
          for (unsigned int i = 0; i < size_; ++i)
          {
              array_[i] = array_[i + 1];
          }

          size_ -= 1;
      }
 
  }

  // Inserts a new node at the specified position. Causes an
  // abort() if the position is invalid. (Calls check_bounds)
  void Vector::insert(int value, unsigned position)
  {

        check_bounds(position);

        if (size_ >= capacity_)
        {
            grow();
        }

        if (position == 0)
        {
            push_front(value);
        }
        else
        {
            for (unsigned int i = size_; i > position; i--)
            {
                array_[i] = array_[i - 1];
            }

            array_[position] = value;
            size_++;
        }    
  }

  // Removes an element with the specified value (first occurrence)
  void Vector::remove(int value)
  {
      for (unsigned int i = 0; i < size_; i++)
      {
          if (array_[i] == value)
          {
              for (unsigned int j = i; j < size_-1; j++)
              {
                  array_[j] = array_[j + 1];
              }
              size_--;

              break;
          }
      }

  }

  // Deletes the underlying array and sets size_ to 0
  void Vector::clear()
  {
      delete[] array_;
      array_ = new int[capacity_];
      capacity_ = 0;
      size_ = 0;
  }

  bool Vector::empty( void ) const 
  {
    return size_ == 0;
  } 


  // Concatenates a vector onto the end of this vector.
  Vector& Vector::operator+=(const Vector& rhs)
  {
      unsigned val = rhs.size_;

      for (unsigned int i = 0; i < val; i++)
      {
          push_back(rhs.array_[i]);
      }

      return *this;
  }

  // Concatenates two Vectors.
  Vector Vector::operator+(const Vector& rhs) const
  {
      Vector v = Vector(*this);

      v += rhs;

      v.allocs_ = 1;

      return v;
  }

  // Subscript operators.
  int  Vector::operator[] (unsigned index) const
  {
      check_bounds(index);
      return array_[index];
  }

  int& Vector::operator[] (unsigned index)
  {
      check_bounds(index);
      return array_[index];
  }

  unsigned Vector::size( void ) const 
  {
    return size_;
  } 

  unsigned Vector::capacity( void ) const 
  {
    return capacity_;
  } 

  unsigned Vector::allocations( void ) const 
  {
    return allocs_;
  }
  // /////////////////////////////////////////////////////////////////////////////// /////////////////////////////////////////////////////////////////////////////// private // /////////////////////////////////////////////////////////////////////////////// /////////////////////////////////////////////////////////////////////////////
  void Vector::check_bounds( unsigned index ) const 
  {
    // Don't have to check for < 0 because index is unsigned
    if ( index >= size_ ) {
      std::cout << "Attempting to access index " << index << ".";
      std::cout << " The size of the array is " << size_ << ". Aborting...\n";
      std::abort(  );
    }
  } 

  void Vector::grow( void ) 
  {
    // Double the capacity
    capacity_ = ( capacity_ ) ? capacity_ * 2 : 1;

    // Rest of the code here...
        // Rest of the code here...
   
    if (capacity_)
    {
        int *temp = new int[capacity_];

        for (unsigned int i = 0; i < size_; ++i)
        {
            temp[i] = array_[i];
        }

        delete[] array_;

        if (temp)
        {
            array_ = temp;
        }

        ++allocs_;
        
    }

  }

}                               // namespace CS170
