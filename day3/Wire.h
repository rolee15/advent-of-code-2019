#pragma once
#include "Node.h"
#include <vector>
#include <set>

class Wire
{
public:

	typedef unsigned int u_int;

    typedef std::set<Node> myset;

    typedef myset::iterator iterator;

    // Constructors
	Wire();

    Wire(std::string s);

    Wire(Wire& w);

private:

    std::string commands;
	// Array of nodes
    myset _nodes;

public:

    // Public operations
    iterator find(Node& n);

    std::vector<Node> crosspoints(Wire& right);

    static int manhattan(Node& n);

    int distance(Node& n);

    void parse(std::string s);

	friend std::ostream& operator<<(std::ostream& out, const Wire& w);
};

