/******************************************************************************
filename    perm-jt.cpp
author      Anthon Reid
DP email    anthon.reid@digipen.edu
course      CS330
section     A
Assignment  1
due date    9/18/2023

Brief Description:
Implementation of the Johnson-Trotter algorithm.

*******************************************************************************/
#include "perm-jt.h"

PermJohnsonTrotter::PermJohnsonTrotter(int size) 
	: m_Data()
	, m_Direction(size, -1)
{
	//.Initialize all elements with ←.
	for (int i = 0; i < size; i++)
	{
		m_Data.push_back(i + 1);
	}
}

bool PermJohnsonTrotter::Next()
{
	//	2. While the last permutation generated has a mobile element :
	bool found = false;
	int largest = 0;
	int index = 0;
	for (int i = 0; i < static_cast<int> (m_Data.size()); i++)
	{	
		if (i + m_Direction[i] >= 0 && i + m_Direction[i] < static_cast<int> (m_Data.size()))
		{
			if (m_Data[i] > m_Data[i + m_Direction[i]])
			{
				//Find the largest mobile element k.
				if (m_Data[i] > largest)
				{
					found = true;
					largest = m_Data[i];
					index = i;
				}
			}
		}
	}

	if (found)
	{

		//Swap k with the element k is pointing to
		std::swap(m_Data[index], m_Data[index + m_Direction[index]]);

		std::vector<int> dir = m_Direction;

		std::swap(dir[index], dir[index + m_Direction[index]]);

		index = index + m_Direction[index];

		m_Direction = dir;


		//Reverse the direction of all elements that are larger than k.
		for (int i = 0; i < static_cast<int> (m_Data.size()); i++)
		{
			if (m_Data[i] > m_Data[index])
			{
				m_Direction[i] *= -1;
			}
		}
	}
	return found;
}

std::vector<int> const& PermJohnsonTrotter::Get() const
{
	// TODO: insert return statement here
	return m_Data;
}
