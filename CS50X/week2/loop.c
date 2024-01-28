#include <stdio.h>
#include "my_library.h"

int get_safe_n(char *prompt)
{
  int n;

  do
  {
    n = get_int(prompt);
  } while (n < 1);

  return n;
}

int horizon_blocks(int n)
{
  while (n > 0)
  {
    printf("#");
    n--;
  }

  printf("\n");

  return 0;
}

int vertical_blocks(int n)
{
  for (int i = 0; i < n; i++)
  {
    printf("#\n");
  }

  return 0;
}

int square_blocks(int n)
{
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      printf("#");
    }
    printf("\n");
  }

  return 0;
}

int main(void)
{
  int horizon_n = get_safe_n("Number of horizon blocks: ");
  horizon_blocks(horizon_n);
  int vertical_n = get_safe_n("Number of vertical blocks: ");
  vertical_blocks(vertical_n);
  int square_n = get_safe_n("Number of square blocks: ");
  square_blocks(square_n);
}