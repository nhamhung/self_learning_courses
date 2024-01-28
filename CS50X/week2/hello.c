#include <stdio.h>
#include <stdlib.h>
#include "my_library.h"

int main(void)
{
  string answer = get_string("What's your name?");

  printf("Hello %s\n", answer);

  free(answer);

  return 0;
}