#pragma once
#include <string>
#include <algorithm>
#include "IntCodeComputer.h"

struct Amplifier : public IntCodeComputer
{
    Amplifier* next;

    const char* name;

    Amplifier(const char* code, const char* name)
        : IntCodeComputer(code), next(0), name(name) {}
};

struct Amplifiers
{
    Amplifier amp_A;
    Amplifier amp_B;
    Amplifier amp_C;
    Amplifier amp_D;
    Amplifier amp_E;

    int max_thrust = INT_MIN;

    bool verbose = false;

    Amplifiers()
        : amp_A("input.txt", "Amp A"), amp_B("input.txt", "Amp B"),
        amp_C("input.txt", "Amp C"), amp_D("input.txt", "Amp D"), amp_E("input.txt", "Amp E")
    {
        amp_A.next = &amp_B;
        amp_B.next = &amp_C;
        amp_C.next = &amp_D;
        amp_D.next = &amp_E;
        amp_E.next = &amp_A;
    }

    void permute(std::string a, int l, int r);

    void input(std::string a);

    void restart();

};


