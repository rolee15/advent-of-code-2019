// Day2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <vector>

constexpr auto SIZE = 512;

int run(std::vector<int>&);

int solution1(std::vector<int> a)
{
	// Restore to 1202 program alarm state
	a[1] = 12;
	a[2] = 2;

	return run(a);

}

std::pair<int,int>* solution2(std::vector<int> a)
{
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			std::cout << "Parameters: " << i << ", " << j;
			
			std::vector<int> tmp = a;
			tmp[1] = i; tmp[2] = j;

			int result = run(tmp);
			std::cout << " Result: " << result << "\n";

			if (result == 19690720)
			{
				return new std::pair<int, int>(i, j);
			}
		}
	}

	return new std::pair<int, int>(-1, -1);
}

int run(std::vector<int> &v)
{
	for (unsigned int ip = 0; ip < v.size(); ip += 4)
	{
		size_t n1_pos = v[ip + 1];
		size_t n2_pos = v[ip + 2];
		size_t res_pos = v[ip + 3];

		if (res_pos >= v.size())
			continue;

		switch (v[ip])
		{
		case 1:
			//std::cout << "Op  1: " << n1_pos << " + " << n2_pos << " = " << a[n1_pos] + a[n2_pos] << "\t-> " << res_pos << "\n";
			v[res_pos] = v[n1_pos] + v[n2_pos];
			break;
		case 2:
			//std::cout << "Op  2: " << n1_pos << " * " << n2_pos << " = " << a[n1_pos] * a[n2_pos] << "\t-> " << res_pos << "\n";
			v[res_pos] = v[n1_pos] * v[n2_pos];
			break;
		case 99:
			//std::cout << "Op 99: Program end.\n";
			return v[0];
		}
	}

	return v[0];
}

int main()
{
	// Tests
	std::vector<int> test = { 1,0,0,0,99 };

	// Read from file
	std::ifstream file;
	file.open("input.txt");

	std::vector<int> numbers;
	while (file.good())
	{
		char s[10];
		file.getline(s, 4, ',');
		numbers.push_back(atoi(s));
	}

	file.close();

	// Parameters
	int n = 0;
	std::vector<int> &input = numbers;

	// Do
	int res1 = solution1(input);
	std::pair<int, int> *res2 = solution2(input);

	// Print results
	std::cout << "result1: " << res1 << "\n";
	std::cout << "result2: " << res2->first * 100 + res2->second << "\n";
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
