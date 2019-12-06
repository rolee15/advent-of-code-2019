#include "Memory.h"
#include <fstream>
#include <iostream>

Memory::Memory(const char* s)
	: _ip(0)
{
	std::ifstream ifile(s);

	char str[16];
	while (ifile.getline(str, 16, ','))
	{
		_mem.push_back(atoi(str));
	}

	ifile.close();
}

bool Memory::next()
{
	if (_ip >= _mem.size() - 1)
		return false;

	return true;
}

void Memory::execute()
{
	int opcode = _mem[_ip] % 100;
	int mode = _mem[_ip] / 100;

	switch (opcode)
	{
		case 1:
			add(_mem[_ip + 1], _mem[_ip + 2], _mem[_ip + 3], mode);
			_ip += 4;
			break;
		case 2:
			multiply(_mem[_ip + 1], _mem[_ip + 2], _mem[_ip + 3], mode);
			_ip += 4;
			break;
		case 3:
			input(_mem[_ip + 1]);
			_ip += 2;
			break;
		case 4:
			output(_mem[_ip + 1], mode);
			_ip += 2;
			break;
		case 5:
			jmp_true(_mem[_ip + 1], _mem[_ip + 2], mode);
			break;
		case 6:
			jmp_false(_mem[_ip + 1], _mem[_ip + 2], mode);
			break;
		case 7:
			lt(_mem[_ip + 1], _mem[_ip + 2], _mem[_ip + 3], mode);
			_ip += 4;
			break;
		case 8:
			eq(_mem[_ip + 1], _mem[_ip + 2], _mem[_ip + 3], mode);
			_ip += 4;
			break;
		case 99:
			halt();
			break;
		default:
			exit(EXIT_FAILURE);
	}

}

void Memory::add(int a, int b, int p, int mode)
{
	int mode_a = mode % 10;
	int mode_b = (mode / 10) % 10;
	int mode_c = (mode / 100) % 10;

	if (mode_a == 0)
		a = _mem[a];

	if (mode_b == 0)
		b = _mem[b];

	_mem[p] = a + b;
}

void Memory::multiply(int a, int b, int p, int mode)
{
	int mode_a = mode % 10;
	int mode_b = (mode / 10) % 10;

	if (mode_a == 0)
		a = _mem[a];

	if (mode_b == 0)
		b = _mem[b];

	_mem[p] = a * b;
}

void Memory::input(int p)
{
	std::cin >> _mem[p];
}

void Memory::output(int p, int mode)
{
	if (mode == 0)
		p = _mem[p];
	
	std::cout << p << "\n";
}

void Memory::jmp_true(int a, int p, int mode)
{
	int mode_a = mode % 10;
	int mode_p = (mode / 10) % 10;

	if (mode_a == 0)
		a = _mem[a];

	if (mode_p == 0)
		p = _mem[p];

	_ip = a != 0 ? p : _ip + 3;
}

void Memory::jmp_false(int a, int p, int mode)
{
	int mode_a = mode % 10;
	int mode_p = (mode / 10) % 10;

	if (mode_a == 0)
		a = _mem[a];

	if (mode_p == 0)
		p = _mem[p];

	_ip = a == 0 ? p : _ip + 3;
}

void Memory::lt(int a, int b, int p, int mode)
{
	int mode_a = mode % 10;
	int mode_b = (mode / 10) % 10;

	if (mode_a == 0)
		a = _mem[a];

	if (mode_b == 0)
		b = _mem[b];

	_mem[p] = a < b;
}

void Memory::eq(int a, int b, int p, int mode)
{
	int mode_a = mode % 10;
	int mode_b = (mode / 10) % 10;

	if (mode_a == 0)
		a = _mem[a];

	if (mode_b == 0)
		b = _mem[b];

	_mem[p] = a == b;
}

void Memory::halt()
{
	std::cout << "Program terminated. Press the red button and rest in peace.\n";
	exit(EXIT_SUCCESS);
}
