#pragma once
#include "Wire.h"

class Intersection
{
public:

	// Constructors
	Intersection(Wire& wl, Wire& wr);

private:
	
	Wire w1;

	Wire w2;

	std::vector<Node> _intersections;

public:

	int minsteps();
};

