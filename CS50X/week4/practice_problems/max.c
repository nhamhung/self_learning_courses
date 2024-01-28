// Practice writing a function to find a max value

#include "../../my_library.h"
#include <stdio.h>
#include <limits.h>

int max(int array[], int n);

int main(void)
{
    int n;
    do
    {
        n = get_int("Number of elements: ");
    } while (n < 1);

    int arr[n];

    for (int i = 0; i < n; i++)
    {
        arr[i] = get_int("Element: ");
    }

    printf("The max value is %i.\n", max(arr, n));
}

// TODO: return the max value
int max(int array[], int n)
{
    int max_value = INT_MIN;

    for (int i = 0; i < n; i++)
    {
        if (array[i] > max_value)
        {
            max_value = array[i];
        }
    }

    return max_value;
}
