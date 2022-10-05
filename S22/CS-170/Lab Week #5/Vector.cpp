/*!*****************************************************************************
\file    vector.cpp
\author  Anthon Reid
\par     DP email:  anthon.reid@digipen.edu
\par     Course: CS120
\par     Lab #5
\date    02-11-2022

\brief
This uses grows a vector to add a value in front or behind it.

*******************************************************************************/
#include <iostream>  // cout
#include <cstdlib>   // abort
#include "Vector.h"

namespace CS170
{

  Vector::Vector(void) : array_(0), size_(0), capacity_(0), allocs_(0)
  {
  }

    // Destructor
  Vector::~Vector()
  {
      delete[] array_;
  }

  bool Vector::empty(void) const
  {
    return size_ == 0;
  }

  unsigned Vector::size(void) const
  {
    return size_;
  }

  unsigned Vector::capacity(void) const
  {
    return capacity_;
  }

  unsigned Vector::allocations(void) const
  {
    return allocs_;
  }


  void Vector::push_back(int value)
  {
      if (size_ >= capacity_)
      {
          grow();
      }

      array_[size_] = value;
      ++size_;
  }

  void Vector::push_front(int value)
  {
      if (size_ >= capacity_)
      {
          grow();
      }

      for (int i = size_ - 1; i >= 0; --i)
      {
          array_[i + 1] = array_[i];
      }
      array_[0] = value;
      ++size_;
  }
  int Vector::operator[](unsigned index) const
  {
      check_bounds(index);
      return array_[index];
  }
  int& Vector::operator[](unsigned index)
  {
      check_bounds(index);
      return array_[index];
  }

  void Vector::clear(void)
  {
      delete[] array_;
      array_ = new int[capacity_];
      size_ = 0;
      capacity_ = 0;
  }


  ///////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////
  // private 
  ///////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////

  void Vector::check_bounds(unsigned index) const
  {
    // Don't have to check for < 0 because index is unsigned
    if (index >= size_)
    {
      std::cout << "Attempting to access index " << index << ".";
      std::cout << " The size of the array is " << size_ << ". Aborting...\n";
      std::abort();
    }
  }

  void Vector::grow(void)
  {
    // Double the capacity ( or set to 1 if it was zero)
    capacity_ = (capacity_) ? capacity_ * 2 : 1;

    // Rest of the code here...
    int* temp = new int[capacity_];
    if (capacity_)
    {
        for (unsigned int i = 0; i < size_; ++i)
        {
            temp[i] = array_[i];
        }
    }
    delete[] array_;

    array_ = temp;
    ++allocs_;
  }

} // namespace CS170
