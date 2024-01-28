#include "../../my_library.h"
#include <stdio.h>

int main(int argc, string argv[])
{
  string test = get_string("abc %s: ", "hi");
  string test2 = get_string("abc %s: ", "he");
  printf("%s", test);
}
