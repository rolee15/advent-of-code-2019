#pragma once
#include <ostream>

class Node
{
public:

	enum Direction { up = 'U', down = 'D', right = 'R', left = 'L' };

	// Operations

	void step(char d);

	// Getters/Setters
	int x() const { return _x; }

	void x(int x) { _x = x; }

	int y() const { return _y; }

	void y(int y) { _y = y; }

	// Constructors
	Node();

	Node(int x, int y);

	Node(const Node &n);

private:

	// X coordinate
	int _x;
	// Y coordinate
	int _y;

public:

	// Operators
	friend bool operator==(const Node& lhs, const Node& rhs);

	friend bool operator<(const Node& lhs, const Node& rhs);
	
	friend std::ostream& operator<<(std::ostream& out, const Node& n);

	struct node_compare
	{
		bool operator() (const Node& lhs, const Node& rhs) const {
			return lhs.x() == rhs.x();
		}
	};
};

