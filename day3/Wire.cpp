#include "Wire.h"
#include <sstream>


Wire::iterator Wire::find(Node& n)
{
	return _nodes.find(n);
}

std::vector<Node> Wire::crosspoints(Wire& right)
{
	std::vector<Node> v;

	for (iterator it = _nodes.begin(); it != _nodes.end(); ++it)
	{
		if (right._nodes.find(*it) != right._nodes.end())
			v.push_back(*it);
	}

	return v;
}

int Wire::manhattan(Node &n)
{
	return abs(n.x()) + abs(n.y());
}

int Wire::distance(Node& n)
{
	std::stringstream ss(commands);

	Node curr(0, 0);
	int allsteps = 0;

	char tmp[16];
	while (ss.good())
	{
		ss.getline(tmp, 16, ',');

		int steps = atoi(tmp + 1);
		for (int i = 0; i < steps; i++)
		{
			curr.step(tmp[0]);
			++allsteps;

			if (curr == n)
				return allsteps;
		}
	}

	return INT_MAX;
}

void Wire::parse(std::string s)
{
	commands = s;

	std::stringstream ss(commands);

	Node curr(0, 0);
	_nodes.clear();

	char tmp[16];
	while (ss.good())
	{
		ss.getline(tmp, 16, ',');

		int steps = atoi(tmp + 1);
		for (int i = 0; i < steps; i++)
		{
			curr.step(tmp[0]);

			Node n(curr);
			_nodes.insert(n);
		}
	}
}

Wire::Wire()
	: _nodes()
{
}

Wire::Wire(std::string s)
	: _nodes()
{
	parse(s);
}

Wire::Wire(Wire& w)
{
	commands = w.commands;
	_nodes = w._nodes;
}


std::ostream& operator<<(std::ostream& out, const Wire& w)
{
	for (auto it = w._nodes.begin(); it != w._nodes.end(); ++it)
	{
		out << "("  << it->x()
			<< ", " << it->y()
			<< ") ";
	}

	return out;
}

