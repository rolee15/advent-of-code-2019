#pragma once
#include <vector>

class Memory
{
public:

	// Constructors
	Memory(const char* s);

private:
	// Vector for storing blocks of integers
	std::vector<int> _mem;

	// Instruction pointer
	unsigned int _ip;

public:

	// Publich methods
	bool next();

	void execute();

private:

	// TEST operations
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

