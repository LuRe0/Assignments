/******************************************************************************
filename    hull-bruteforce.cpp
author      Anthon Reid
DP email    anthon.reid@digipen.edu
course      CS330
section     A
Assignment  1
due date    9/12/2023

Brief Description:
This program calculates in whether given points are are in a hull

*******************************************************************************/
#include "hull-bruteforce.h"
#include <algorithm>
#include <iostream>

bool Point::operator==(Point const& arg2) const {
	return ((x == arg2.x) && (y == arg2.y));
}

std::ostream& operator<< (std::ostream& os, Point const& p) {
	os << "(" << p.x << " , " << p.y << ") ";
	return os;
}

std::istream& operator>> (std::istream& os, Point& p) {
	os >> p.x >> p.y;
	return os;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//return value is (on left, on right)
std::pair<bool, bool> get_location(
	float const& p1x, //check which side of the line (p1x,p1y)-->(p2x,p2y) 
	float const& p1y, //point (qx,qy) is on
	float const& p2x,
	float const& p2y,
	float const& qx,
	float const& qy
)
{
	Point dir = { p2x - p1x,p2y - p1y };
	Point norm = { dir.y, -dir.x };
	Point point = { qx - p1x,qy - p1y };
	//scalar product is positive if on right side
	float scal_prod = norm.x * point.x + norm.y * point.y;
	return std::make_pair((scal_prod < 0), (scal_prod > 0));
}

//returns a set of indices of points that form convex hull
std::set<int> hullBruteForce(std::vector< Point > const& points) {
	int num_points = points.size();
	//std::cout << "number of points " << num_points << std::endl;
	if (num_points < 3) throw "bad number of points";

	std::set<int> hull_indices;


	//Since hull is represented by a std::set, you do not haveto worry about duplicates.
	for (size_t i = 0; i < points.size(); ++i) //for each pair points determine whether all other points are one side of the line formed by the pair of points.
	{
		// i is the first point
		for (size_t j = 0; j < points.size(); j++)
		{
			if (!(points[j] == points[i]))
			{
				//j is the point that it forms a line with
				std::pair<bool, bool> check;
				bool found = true;
				for (size_t k = 0; k < points.size(); k++)
				{
					if (!(points[k] == points[i]) && !(points[k] == points[j]))
					{
						// k is the point being check for side
						//determine whether all other points are one side of the line formed by the pair of points.
						std::pair<bool, bool> location = get_location(points[i].x, points[i].y, points[j].x, points[j].y, points[k].x, points[k].y);
						
						if (check.first == check.second)
						{
							check = location;
						}
						else if (check != location)
						{
							found = false;
							break;
						}
					}

				}

				if (found)
				{
					hull_indices.emplace(i);//If it does - add the points(or rather indices to the hull).
					break;
				}
			}
		}
	}


	return hull_indices;
}

std::vector<int> hullBruteForce2(std::vector< Point > const& points) 
{
	size_t num_points = points.size();
	if (num_points < 3) throw "bad number of points";

	std::vector<int> hull_indices;

	float min_x = std::numeric_limits<float>::max();
	float min_y = std::numeric_limits<float>::max();
	size_t index = -1;
	//find the first point that is in the hull(smalles or biggest x or y coordinate),
	for (size_t i = 0; i < points.size(); i++)
	{
		if (points[i].x < min_x)
		{
			min_x = points[i].x;
			min_y = points[i].y;
			index = i;
		}
		else if (points[i].x == min_x && points[i].y < min_y)
		{
			min_x = points[i].x;
			min_y = points[i].y;
			index = i;
		}
	}

	hull_indices.push_back(index);
	//order by considering all lines through the
	//	previous vertex and requiring that there are no points to the right of it.

	//then find the next vertex of the hull in counter - clockwise 
	for (size_t i = 0; i < hull_indices.size(); i++)
	{
		for (size_t j = 0; j < points.size(); j++)
		{
			if (!(points[j] == points[hull_indices[i]]))
			{
				bool found = true;

				for (size_t k = 0; k < points.size(); k++)
				{

					if (!(points[k] == points[j]) && !(points[k] == points[hull_indices[i]]))
					{
						std::pair<bool, bool> location = get_location(points[hull_indices[i]].x, points[hull_indices[i]].y, points[j].x, points[j].y, points[k].x, points[k].y);

						if (location.second)
						{
							found = false;
						}
					}
				}

				if (found)
				{
					if (points[hull_indices[0]] == points[j])
						break;

					
					hull_indices.push_back(j);
					break;
				}
			}
		}
	}
	//bool done = false;


	return hull_indices;

}