// Day2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>

constexpr auto SIZE = 512;

void solution1(int* a, int N)
{
	for (int ip = 0; ip < N; ip += 4)
	{
		size_t n1_pos = a[ip + 1];
		size_t n2_pos = a[ip + 2];
		size_t res_pos = a[ip + 3];
		switch (a[ip])
		{
		case 1:
			std::cout << "Op  1: " << a[n1_pos] << " + " << a[n2_pos] << "\n";
			a[res_pos] = a[n1_pos] + a[n2_pos];
			break;
		case 2:
			std::cout << "Op  2: " << a[n1_pos] << " * " << a[n2_pos] << "\n";
			a[res_pos] = a[n1_pos] * a[n2_pos];
			break;
		case 99:
			std::cout << "Op 99: Program end.\n";
			return;
		default:
			exit(EXIT_FAILURE);
		}
	}

}

void solution2(int* a)
{

}

int main()
{
	// Tests
	int test[] = { 1,0,0,0,99 };

	// Input variables
	int n = 0;
	int N = 5;
	int* input = test;

	// Print input
	std::cout << "Input: ";
	for (int i = 0; i < N; i++)
		std::cout << input[i];
	std::cout << "\n";

	// Do
	solution1(input, N);

	// Print output
	std::cout << "Output: ";
	for (int i = 0; i < N; i++)
		std::cout << input[i];
	std::cout << "\n";
	std::cout << "result: " << input[0] << "\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
