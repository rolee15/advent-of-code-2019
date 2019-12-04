#include "Node.h"

void Node::step(char d)
{
	if (d == up)
		_y++;
	else if (d == down)
		_y--;
	else if (d == right)
		_x++;
	else if (d == left)
		_x--;
}

Node::Node()
	: _x(0), _y(0)
{
}

Node::Node(int x, int y)
	: _x(x), _y(y)
{
}

Node::Node(const Node& n)
	: _x(n._x), _y(n._y)
{
}

bool operator==(const Node& lhs, const Node& rhs)
{
	return lhs._x == rhs._x && lhs._y == rhs._y;
}

bool operator<(const Node& lhs, const Node& rhs)
{
	return (lhs._x < rhs._x) ||
		(lhs._x == rhs._x && lhs._y < rhs._y);
}

std::ostream& operator << (std::ostream& out, const Node& n)
{
	out << "(" << n._x;
	out << "," << n._y << ")";
	return out;
}
