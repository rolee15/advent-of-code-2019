#pragma once
#include <map>
#include <string>
#include "Object.h"
class Universe
{
public:

	// Constructors

	Universe(const char* s);

private:

	// Members
	
	unsigned int _num_orbits;

	Object* com;

	std::map<std::string, Object*> _obj;

public:

	// Public methods
	
	unsigned int num_orbits() { return _num_orbits;  }

	unsigned int orbital_jumps();

private:

	// Helper functions

	Object* i_get(std::string name);

	// Count direct and indirect orbits
	unsigned int traverse(Object* o);
};

