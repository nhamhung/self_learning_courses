#include "../../my_library.h"
#include <stdio.h>

int main(void)
{
  int n;

  do
  {
    n = get_int("Height: ");

    for (int i = 0; i < n; i++)
    {
      for (int j = 0; j < n - i - 1; j++)
      {
        printf(" ");
      }
      for (int j = 0; j < i + 1; j++)
      {
        printf("#");
      }
      printf("  ");
      for (int j = 0; j < i + 1; j++)
      {
        printf("#");
      }
      for (int j = 0; j < n - i - 1; j++)
      {
        printf(" ");
      }

      printf("\n");
    }
  } while (n < 1);
}