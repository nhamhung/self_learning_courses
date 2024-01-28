#include "../../my_library.h"
#include <ctype.h>
#include <stdio.h>

float calc_hours(int hours[], int weeks, char output)
{
    float total = 0;

    for (int i = 0; i < weeks; i++)
    {
        total += hours[i];
    }

    if (output == 'T')
    {
        return total;
    }
    else
    {
        return total / weeks;
    }
}

int main(void)
{
    int weeks = get_int("Number of weeks taking CS50: ");
    int hours[weeks];
    char buffer[100];

    for (int i = 0; i < weeks; i++)
    {
        sprintf(buffer, "Week %i HW Hours: ", i);
        hours[i] = get_int(buffer);
    }

    // char output;
    // do
    // {
    //     output = toupper(get_char("Enter T for total hours, A for average hours per week: "));
    //     printf("Output: %c\n", output);
    // } while (output != 'T' && output != 'A');

    char output = toupper(get_char("Enter T for total hours, A for average hours per week: "));

    printf("%.1f hours\n", calc_hours(hours, weeks, output));
}