#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

#define SIZE 512

long additional(long, long*);

int main(void)
{

    FILE *fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("input.txt", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);


    long number = 0;
    const int base = 10;
    long numbers[SIZE];
    int count = 0;

    while ((read = getline(&line, &len, fp)) != -1)
    {
        char* endptr = NULL;
        errno = 0;  // reset errno before the calls

        // convert line to number
        number = strtol(line, &endptr, base);

        // error checking
        if (line == endptr)
            printf (" number : %li  invalid  (no digits found, 0 returned)\n", number);
        else if (errno == ERANGE && number == LONG_MIN)
            printf (" number : %li  invalid  (underflow occurred)\n", number);
        else if (errno == ERANGE && number == LONG_MAX)
            printf (" number : %li  invalid  (overflow occurred)\n", number);
        else if (errno == EINVAL)  /* not in all c99 implementations - gcc OK */
            printf (" number : %li  invalid  (base contains unsupported value)\n", number);
        else if (errno != 0 && number == 0)
            printf (" number : %li  invalid  (unspecified error occurred)\n", number);
        else if (errno == 0 && line && !*endptr)
            printf (" number : %li    valid  (and represents all characters read)\n", number);
        else if (errno == 0 && line && *endptr != 0)
            // for some reason this runs for every line ¯\_(ツ)_/¯
            //printf (" number : %li    valid  (but additional characters remain)\n", number);

        // store number
        numbers[count++] = number;
    }

    fclose(fp);
    if (line)
        free(line);

    
    long sum = 0;
    long add_sum = 0;
    for (int i = 0; i < count; i++)
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
    printf("All uel required: %li\n", add_sum);

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


