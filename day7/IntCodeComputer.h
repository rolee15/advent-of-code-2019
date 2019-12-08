#pragma once
#include <vector>
#include <list>
#include <iostream>

class IntCodeComputer
{
public:
	
	// Constructors
	
	IntCodeComputer(const char* code);

private:

	// Members
	
	// Memory
	std::vector<int> _mem;

	// Original copy of the code
	std::vector<int> _code;

	// Instruction pointer
	unsigned int _ip;

	// Input buffer
	std::list<int> _iBuff;

	// Output buffer
	std::list<int> _oBuff;

	// Program passes output
	bool _out = false;

	// Program terminated
	bool _halted = false;

	// Print commands to std output
	bool _verbose = false;

public:

	// Publich methods

	int run();

	// 
	bool next();

	// Execute current operation
	void execute();

	void reset();

	bool is_halted() { return _halted; }

	void verbose(bool b) { _verbose = b; }

	// Operators

	// Push an integer into the input buffer
	friend IntCodeComputer& operator<<(IntCodeComputer& c, const int& i);

	// Pop an integer from the front of the output buffer
	friend IntCodeComputer& operator>>(IntCodeComputer& c, int& i);

private:

	void operate(int opcode, int mode);

	// IntCode operations
	void add(int a, int b, int p, int mode);

	void multiply(int a, int b, int p, int mode);

	void input(int p);

	void output(int p, int mode);

	void jmp_true(int a, int p, int mode);

	void jmp_false(int a, int p, int mode);

	void lt(int a, int b, int p, int mode);

	void eq(int a, int b, int p, int mode);

	void halt();
};

