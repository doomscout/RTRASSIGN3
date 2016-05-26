#pragma once

#include <iostream>
#include "Point2f.hpp"

class Arena
{

public:
	Point2f min;
	Point2f max;
	Point2f momentum;
	Arena();
	void displayArena();
};
