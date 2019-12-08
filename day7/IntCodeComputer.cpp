#include "IntCodeComputer.h"
#include <fstream>


IntCodeComputer::IntCodeComputer(const char* code)
	: _ip(0)
{
	std::ifstream ifile(code);

	char str[16];
	while (ifile.getline(str, 16, ','))
	{
		int a = atoi(str);
		_code.push_back(a);
		_mem.push_back(a);
	}

	ifile.close();
}

int IntCodeComputer::run()
{
	// Reset output mode
	_out = false;

	while (next())
	{
		execute();
	}

	if (_oBuff.empty())
	{
		std::cerr << "Ip " << _ip << ": " << _mem[_ip] % 100 << ": Output buffer was empty!\n";
		return -1;
	}
	else
	{
		int last = _oBuff.back();
		return last;
	}
}

bool IntCodeComputer::next()
{
	if (_halted || _out)
		return false;

	return true;
}

void IntCodeComputer::execute()
{
	int opcode = _mem[_ip] % 100;
	int mode = _mem[_ip] / 100;

	if (_verbose)
		std::cout << "Ip " << _ip << ": ";
	
	operate(opcode, mode);
}

void IntCodeComputer::reset()
{
	// Clear memory and copy the code
	_mem.clear();
	_mem = _code;

	// Clear buffers
	_iBuff.clear();
	_oBuff.clear();

	// Reset instruction pointer
	_ip = 0;

	// Reset flags
	_out = false;
	_halted = false;
}

IntCodeComputer& operator<<(IntCodeComputer& c, const int& i)
{
	c._iBuff.push_back(i);

	return c;
}

IntCodeComputer& operator>>(IntCodeComputer& c, int& i)
{
	i = c._oBuff.front();
	c._oBuff.pop_front();

	return c;
}

void IntCodeComputer::operate(int opcode, int mode)
{
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

void IntCodeComputer::add(int a, int b, int p, int mode)
{
	int mode_a = mode % 10;
	int mode_b = (mode / 10) % 10;
	int mode_c = (mode / 100) % 10;

	if (mode_a == 0)
		a = _mem[a];

	if (mode_b == 0)
		b = _mem[b];

	_mem[p] = a + b;

	if (_verbose)
		std::cout << "Add(): " << a << " + " << b << " = " << a + b << ", stored on " << p << "\n";
}

void IntCodeComputer::multiply(int a, int b, int p, int mode)
{
	int mode_a = mode % 10;
	int mode_b = (mode / 10) % 10;

	if (mode_a == 0)
		a = _mem[a];

	if (mode_b == 0)
		b = _mem[b];

	_mem[p] = a * b;

	if (_verbose)
		std::cout << "Multiply(): " << a << " * " << b << " = " << a * b << ", stored on " << p << "\n";
}

void IntCodeComputer::input(int p)
{
	if (!_iBuff.empty())
	{
		_mem[p] = _iBuff.front();
		_iBuff.pop_front();
		if (_verbose)
			std::cout << "Input(): " << _mem[p] << " to " <<  p << "\n";
	}
	else
		std::cerr << "Ip " << _ip << ": Input(): input buffer was empty!";
}

void IntCodeComputer::output(int p, int mode)
{
	if (mode == 0)
		p = _mem[p];

	_oBuff.push_back(p);
	_out = true;

	if (_verbose)
		std::cout << "Output(): " << p << "\n";
}

void IntCodeComputer::jmp_true(int a, int p, int mode)
{
	int mode_a = mode % 10;
	int mode_p = (mode / 10) % 10;

	if (mode_a == 0)
		a = _mem[a];

	if (mode_p == 0)
		p = _mem[p];

	_ip = a != 0 ? p : _ip + 3;

	if (_verbose)
		std::cout << "Jump_true(): " << a << ", jump to " << _ip << "\n";
}

void IntCodeComputer::jmp_false(int a, int p, int mode)
{
	int mode_a = mode % 10;
	int mode_p = (mode / 10) % 10;

	if (mode_a == 0)
		a = _mem[a];

	if (mode_p == 0)
		p = _mem[p];

	_ip = a == 0 ? p : _ip + 3;

	if (_verbose)
		std::cout << "Jump_false(): " << a << ", jump to " << _ip << "\n";
}

void IntCodeComputer::lt(int a, int b, int p, int mode)
{
	int mode_a = mode % 10;
	int mode_b = (mode / 10) % 10;

	if (mode_a == 0)
		a = _mem[a];

	if (mode_b == 0)
		b = _mem[b];

	_mem[p] = a < b;

	if (_verbose)
		std::cout << "Lt(): " << a << " < " << b << " = " << (a < b) << ", stored on " << p << "\n";
}

void IntCodeComputer::eq(int a, int b, int p, int mode)
{
	int mode_a = mode % 10;
	int mode_b = (mode / 10) % 10;

	if (mode_a == 0)
		a = _mem[a];

	if (mode_b == 0)
		b = _mem[b];

	_mem[p] = a == b;

	if (_verbose)
		std::cout << "Eq(): " << a << " == " << b << " = " << (a == b) << ", stored on " << p << "\n";
}

void IntCodeComputer::halt()
{
	_halted = true;

	if (_verbose)
		std::cout << "Halt(): Hammerzeit\n";
}
