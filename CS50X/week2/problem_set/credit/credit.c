#include "../../my_library.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool is_valid(char *card_number_str)
{
  int n = strlen(card_number_str);
  int every_other_digits_sum = 0;

  for (int i = n - 2; i > -1; i -= 2)
  {
    char char_at_index = card_number_str[i];
    int char_value = atoi(&char_at_index) * 2;

    while (char_value > 0)
    {
      every_other_digits_sum += char_value % 10;
      char_value /= 10;
    }
  }

  for (int i = n - 1; i > -1; i -= 2)
  {
    char char_at_index = card_number_str[i];
    int char_value = atoi(&char_at_index);
    every_other_digits_sum += char_value;
  }

  if (every_other_digits_sum % 10 == 0)
  {
    return true;
  }

  return false;
}

char *get_card_type(char *number_str)
{
  if (number_str[0] == '4' && is_valid(number_str))
  {
    return "VISA";
  }
  else if (number_str[0] == '3' && (number_str[1] == '4' || number_str[1] == '7') && is_valid(number_str))
  {
    return "AMERICAN EXPRESS";
  }
  else if (number_str[0] == '5' && (number_str[1] == '1' || number_str[1] == '2' || number_str[1] == '3' || number_str[1] == '4' || number_str[1] == '5') && is_valid(number_str))
  {
    return "MASTERCARD";
  }
  else
  {
    return "INVALID";
  }
}

int main(void)
{
  char card_number_str[20];
  long card_number;
  // card_number = get_long("Number: ");
  card_number = 5555555555554444;

  snprintf(card_number_str, sizeof(card_number_str), "%ld", card_number);

  char *card_type = get_card_type(card_number_str);
  printf("%s\n", card_type);
}