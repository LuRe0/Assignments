/******************************************************************************
filename    knapsack_brute_force_minchange.cpp
author      Anthon Reid
DP email    anthon.reid@digipen.edu
course      CS330
section     A
Lab			3
due date    10/4/2023

Brief Description:
This program implements iterative brute force solution for knapsack problem
using minimal change ordering of subsets:

*******************************************************************************/

#include "knapsack_brute_force_minchange.h"
//#include <iostream>

GreyCode::GreyCode(int s) 
	: m_NumberOfElements(s)
	, m_MaxSubsets(1 << m_NumberOfElements)
	, m_Counter(1)
	, m_OldCode(0)
{
}

////////////////////////////////////////////////////////////////////////////////
std::pair< bool, std::pair< bool, int > > GreyCode::Next() {


	////this function moves the bit to the next value
	///it fiddles with one position at a time

	int half = m_Counter >> 1;
	int gray_code = m_Counter ^ half;



	int  pos = -1;// which position is modified 


	int difference = std::abs(gray_code - m_OldCode);
	// Check for 1's in the binary form using
	// Brian Kernighan's Algorithm

	do
	{
		difference = difference >> 1;

		// increment count of shifts 
		++pos;

	} while (difference);


 	bool add = (((1 << pos) & gray_code) ? true : false);// is true if new value is 1 (add item), false otherwise 


	bool last = false;


	m_Counter += 1;

	if (m_Counter == m_MaxSubsets)
	{
		last = true;
	}
	

	m_OldCode = gray_code;

	return std::make_pair(!last, std::make_pair(add, pos));
}

////////////////////////////////////////////////////////////////////////////////
std::vector<bool> knapsack_brute_force(std::vector<Item> const& items, Weight const& W)
{
	//It's find the combinations of items with the highest value while not going over the weight
	
	//	So you just run the Grey code over and over
	
	//	And grab the combination that resulted in the highest value


	std::vector<bool> bag(items.size(), false); // empty - all positions are false
	std::vector<bool> final_bag(items.size(), false); // empty - all positions are false
	GreyCode gc(items.size());
	bool go = true;
	// print initial state
	// print vector from the end - same direction as binary representation


	Weight total_weight;
	int curr_value = 0;

	int best_value = 0;
	// the rest 
	while (go) {

		// while there is a next permutation
		std::pair< bool, std::pair< bool, int > > r = gc.Next();
		go = r.first;
		bool add = r.second.first;
		int  pos = r.second.second;
		if (add) {
			bag[pos] = true;

			total_weight += items[pos].GetWeight();
			curr_value += items[pos].GetValue();
		}
		else {
			bag[pos] = false;

			total_weight -= items[pos].GetWeight();
			curr_value -= items[pos].GetValue();
		}

		//if weight is less or equal to max weight and is greater than current best
		if(total_weight <= W && best_value <= curr_value)
		{
			final_bag = bag;
			best_value = curr_value;
		}
	}

	return final_bag;
}
