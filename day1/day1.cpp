#include <iostream>
#include <fstream>
#include <vector>

long additional(long, long*);

int main()
{

    std::ifstream infile("input.txt");
    std::vector<long> numbers;
    int a;
    while (infile >> a)
    {
        // store number
        numbers.push_back(a);
    }
    infile.close();
    
    long sum = 0;
    long add_sum = 0;
    for (int i = 0; i < numbers.size(); i++)
    {
        sum += numbers[i] / 3 - 2;        

        long compound = 0;
        additional(numbers[i], &compound);
        
        add_sum += compound;

        printf("Module weight: %li, module fuel: %li, all fuel: %li\n", 
            numbers[i], numbers[i] / 3 - 2, compound);
    }

    printf("\n");
    printf("Fuel required: %li\n", sum);
    printf("All fuel required: %li\n", add_sum);

    return EXIT_SUCCESS;
}


long additional(long num, long *sum)
{
    if (num <= 0)
        return 0;

    num = num / 3 - 2;

    if (num > 0)
        *sum += num;

    return additional(num, sum);
}


