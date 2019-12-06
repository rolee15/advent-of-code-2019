#include "Universe.h"
#include <fstream>
#include <iostream>
#include <sstream>

Universe::Universe(const char* s)
	: _num_orbits(0)
{
	std::ifstream infile(s);

	char str1[64];
	char str2[64];
	while (infile >> str1)
	{
		std::stringstream ss(str1);

		ss.getline(str2, 64, ')');
		Object* left = i_get(str2);
		
		ss.getline(str2, 64, ')');
		Object* right = i_get(str2);

		// Set parent and add children
		right->parent = left;
		left->children.push_back(right);
	}
	infile.close();

	// Find root
	auto it = _obj.find("COM");
	com = it->second;

	// Traverse
	traverse(com);
}

unsigned int Universe::orbital_jumps()
{
	Object* you = _obj.find("YOU")->second;
	Object* san = _obj.find("SAN")->second;
	Object* p_san = san;
	Object* p_you = you;

	unsigned int san_lvl = san->num_orbits;
	unsigned int you_lvl = you->num_orbits;
	int jumps = 0;

	while (you_lvl < san_lvl)
	{
		p_san = p_san->parent;
		san_lvl--;
		jumps++;
	}
	while (san_lvl < you_lvl)
	{
		p_you = p_you->parent;
		you_lvl--;
		jumps++;
	}

	// Now they are on the same level, step simultaneously
	while (p_san->parent != p_you->parent)
	{
		p_san = p_san->parent;
		p_you = p_you->parent;
		jumps += 2;
	}

	return jumps;
}

// Get object, if doesn't exist yet, create and insert it
Object* Universe::i_get(std::string name)
{
	auto search = _obj.find(name);

	if (search != _obj.end())
	{
		return search->second;
	}
	else
	{
		const auto it = _obj.insert({ name, new Object(name) }).first;
		return it->second;
	}
}

unsigned int Universe::traverse(Object* o)
{
	for (unsigned int i = 0; i < o->children.size(); ++i)
	{
		o->children[i]->num_orbits = o->num_orbits + 1;
		traverse(o->children[i]);
	}

	_num_orbits += o->num_orbits;
	
	return 0;
}
