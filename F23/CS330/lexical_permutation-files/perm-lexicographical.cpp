
/******************************************************************************
filename    perm-lexicographical.cpp
author      Anthon Reid
DP email    anthon.reid@digipen.edu
course      CS330
section     A
Assignment  1
due date    9/18/2023

Brief Description:
Implement lexicographical permutations algorithm.

*******************************************************************************/
#include "perm-lexicographical.h"
#include <algorithm>
#include <limits.h>
#include <iostream>

bool nextPermLexicographical(std::vector<int>& p)
{
	std::vector<int> pair;

	bool found = false;
	int index = 0;
	//1. Scan it right to left to find the first pair of elements such that ai < ai + 1.
	for (int i = static_cast<int>(p.size()) - 1; i >= 0; i--)
	{
		if (i + 1 >= 0 && i + 1 < static_cast<int> (p.size()))
		{
			if (p[i] < p[i + 1])
			{
				index = i;
				pair.push_back(p[i + 1]);
				pair.push_back(p[i]);
				found = true;
				break;
			}
		}
	}


	if (found)
	{
		//	2. Insert all elements from{ a0, . . . , ai−1 } into pj + 1.
		std::vector<int> p1 = std::vector<int>(p.begin(), (p.begin() + index));


		std::vector<int> tail = std::vector<int>(p.begin() + index + 2, p.end());


		//	3. Find the smallest ak within the “tail”(ai + 1, . . ., an) such that it ak > ai
		if (!tail.empty())
		{
			int smallest = INT_MAX;
			int ind = 0;
			bool f = false;
			for (int i = 0; i < static_cast<int>(tail.size()); i++)
			{
				//Smallest element larger than ai in tail 
				if (tail[i] > p[index])
				{
					if (tail[i] < smallest)
					{
						f = true;
						smallest = tail[i];
						ind = i;
					}
				}
			}

			if (f)
			{

				//	4. Insert ak at the end of pj + 1.
				p1.push_back(tail[ind]);
				tail.erase(tail.begin() + ind);

			}
			else
			{

				p1.push_back(pair[0]);

				pair.erase(pair.begin() + 0);
			}

			//	5. Insert at the end of pj + 1 all remaining elements in increasing order.
			pair.insert(pair.end(), tail.begin(), tail.end());

			bool done = false;

			while (!done)
			{
				int smallest = INT_MAX;
				int in = 0;

				for (int i = 0; i < static_cast<int>(pair.size()); i++)
				{
					if (pair[i] < smallest)
					{
						smallest = pair[i];
						in = i;
					}
				}

				p1.push_back(pair[in]);

				pair.erase(pair.begin() + in);
				
				done = pair.empty();
			}


		}
		else
		{

			p1.insert(p1.end(), pair.begin(), pair.end());
		}


		p = p1;
	}

	return found;
}
