#pragma once
#include <string>
#include <vector>

class Object
{
public:
	
	std::string name;

	unsigned int num_orbits;

	Object* parent;

	std::vector<Object*> children;


	Object(std::string& name)
		: name(name), num_orbits(0), parent(0) {}

	Object(const char* name)
		: name(name), num_orbits(0), parent(0) {}
};

