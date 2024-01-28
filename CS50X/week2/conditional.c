#include <stdio.h>
#include "my_library.h"

int main(void)
{
  int x = get_int("Enter x: ");
  int y = get_int("Enter y: ");

  if (x > y)
  {
    printf("x is more than y\n");
  }
  else if (x < y)
  {
    printf("x is less than y\n");
  }
  else
  {
    printf("x is equal to y\n");
  }
}