#include "Amplifier.h"

void Amplifiers::permute(std::string a, int l, int r)
{
    // Base case  
    if (l == r)
    {
        // Restart computers
        restart();

        // Provide phase configurations
        input(a);

        // Run programs until E halted
        std::cout << "Config: " << a << "\n";
        int result = 0;
        Amplifier* amp = &amp_A;
        while (!amp_E.is_halted())
        {
            *amp << result;
            if (verbose)
                std::cout << "Running " << amp->name << " with parameter " << result << "\n";
            result = amp->run();

            amp = amp->next;
        }
        std::cout << "Result: " << result << "\n\n";

        // See if output of E is new maximum
        if (result > max_thrust)
            max_thrust = result;
    }
    else
    {
        // Permutations made  
        for (int i = l; i <= r; i++)
        {
            // Swapping done  
            std::swap(a[l], a[i]);

            // Recursion called  
            permute(a, l + 1, r);

            //backtrack  
            std::swap(a[l], a[i]);
        }
    }
}

void Amplifiers::input(std::string a)
{
    amp_A << atoi(a.substr(0, 1).c_str());
    amp_B << atoi(a.substr(1, 1).c_str());
    amp_C << atoi(a.substr(2, 1).c_str());
    amp_D << atoi(a.substr(3, 1).c_str());
    amp_E << atoi(a.substr(4, 1).c_str());
}

void Amplifiers::restart()
{
    amp_A.reset();
    amp_B.reset();
    amp_C.reset();
    amp_D.reset();
    amp_E.reset();
}