// day3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <sstream>
#include <fstream>

#include "Node.h"
#include "Wire.h"
#include "Intersection.h"

void test1();
void test2();
void solution1();
void solution2();

int main()
{
    // ---------------------------------------------------------------
    //   Tests
    // ---------------------------------------------------------------

    // Test 1
    test1();
    // Test 2
    test2();

    // ---------------------------------------------------------------
    //   File input
    // ---------------------------------------------------------------
    
    // Part 1
    solution1();

    // Part 2
    solution2();
}

void test1()
{
    //  Test 1

    std::string test1 = "R75,D30,R83,U83,L12,D49,R71,U7,L72";
    std::string test2 = "U62,R66,U55,R34,D71,R55,D58,R83";


    Wire wire1(test1);
    Wire wire2(test2);

    std::vector<Node> t1 = wire1.crosspoints(wire2);

    std::cout << "Manhattans:" << "\n";

    int min = INT_MAX;
    for (unsigned int i = 0; i < t1.size(); ++i)
    {
        int manhattan = Wire::manhattan(t1[i]);
        std::cout << t1[i] << " " << manhattan << "\n";
        if (manhattan < min) min = manhattan;
    }
    std::cout << "\nMin:" << min << "\n\n";
}

void test2()
{
    //  Test 2

    std::string test3 = "R98,U47,R26,D63,R33,U87,L62,D20,R33,U53,R51";
    std::string test4 = "U98,R91,D20,R16,D67,R40,U7,R15,U6,R7";

    Wire wire3(test3);
    Wire wire4(test4);

    std::vector<Node> t2 = wire3.crosspoints(wire4);

    int min = INT_MAX;
    for (unsigned int i = 0; i < t2.size(); ++i)
    {
        int manhattan = Wire::manhattan(t2[i]);
        std::cout << t2[i] << " " << manhattan << "\n";
        if (manhattan < min) min = manhattan;
    }
    std::cout << "\nMin:" << min << "\n\n";
}


void solution1()
{
    std::vector<Wire*> wires;

    std::ifstream infile("input.txt");
    std::string line;
    while (std::getline(infile, line))
    {
        wires.push_back(new Wire(line));
    }
    infile.close();

    if (wires.size() != 2)
    {
        std::cerr << "you need two lines in the input file, pal!\n";
        exit(EXIT_FAILURE);
    }

    Wire& w1 = *wires[0];
    Wire& w2 = *wires[1];

    std::vector<Node> v = w1.crosspoints(w2);

    int min = INT_MAX;
    for (unsigned int i = 0; i < v.size(); ++i)
    {
        int manhattan = Wire::manhattan(v[i]);
        if (manhattan < min) min = manhattan;
    }
    std::cout << "\nMin manhattan:" << min << "\n\n";
}

void solution2()
{
    std::vector<Wire*> wires;

    std::ifstream infile("input.txt");
    std::string line;
    while (std::getline(infile, line))
    {
        wires.push_back(new Wire(line));
    }
    infile.close();

    if (wires.size() != 2)
    {
        std::cerr << "you need two lines in the input file, pal!\n";
        exit(EXIT_FAILURE);
    }
    
    Wire& w1 = *wires[0];
    Wire& w2 = *wires[1];

    Intersection i(w1, w2);

    int minsteps = i.minsteps();
    
    std::cout << "\nMin steps:" << minsteps <<  "\n\n";
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
