#include "../../my_library.h"
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    // printf("%zu\n", strlen(input));

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

int convert(string input)
{
    if (strlen(input) <= 0)
    {
        return 0;
    }

    int last_int = input[strlen(input) - 1] - '0';

    // Take only substring excluding last character
    input[strlen(input) - 1] = '\0';

    return convert(input) * 10 + last_int;
}