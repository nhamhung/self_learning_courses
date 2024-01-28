// Write a function to replace vowels with numbers
// Get practice with strings
// Get practice with command line
// Get practice with switch

#include "../../my_library.h"
#include <stdio.h>
#include <string.h>

char *replace(char *input)
{
  for (int i = 0; i < strlen(input); i++)
  {
    switch (input[i])
    {
    case 'e':
      input[i] = '3';
      break;
    case 'a':
      input[i] = '6';
      break;
    case 'i':
      input[i] = '1';
      break;
    case 'o':
      input[i] = '0';
      break;
    default:
      break;
    }
  }

  return input;
}

int main(int argc, string argv[])
{
  if (argc < 2 || argc > 2)
  {
    printf("Only take 1 input!\n");
    return 1;
  }

  char *input = argv[1];

  char *output = replace(input);

  printf("%s\n", output);

  return 0;
}
