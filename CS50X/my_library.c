#include "my_library.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <stdarg.h>

string get_string(const char *format, ...)
{
  char buffer[100];
  memset(buffer, 0, sizeof(buffer));
  va_list args;
  va_start(args, format);
  vprintf(format, args);
  va_end(args);

  fflush(stdin); // clear any residual data in input buffer
  fgets(buffer, sizeof(buffer), stdin);
  buffer[strcspn(buffer, "\n")] = '\0'; // Remove trailing newline character

  string result = (string)malloc(strlen(buffer) + 1); // Allocate memory for the result
  strcpy(result, buffer);                             // Copy the input to the result

  return result;
}

int get_int(const char *prompt)
{
  int number;
  printf("%s", prompt);
  scanf("%d", &number);

  return number;
}

float get_float(const char *prompt)
{
  float number;
  printf("%s", prompt);
  scanf("%f", &number);

  return number;
}

long get_long(const char *prompt)
{
  long number;
  bool validInput = false;
  char buffer[100];

  do
  {
    printf("%s", prompt);

    // attempt to get stdin to buffer
    if (fgets(buffer, sizeof(buffer), stdin) == NULL)
    {
      printf("Error reading input. Please try again.\n");
      continue;
    }

    // attempt to parse formatted input from a string, return number of successfully parsed values
    if (sscanf(buffer, "%ld", &number) != 1)
    {
      printf("Invalid input. Please enter a valid long value.\n");
      continue;
    }

    if (number < LONG_MIN || number > LONG_MAX)
    {
      printf("Input value is out of long range.\n");
      continue;
    }

    validInput = true;
  } while (!validInput);

  return number;
}

char get_char(const char *prompt)
{
  int c;

  printf("%s", prompt);

  // Discard any leftover characters in the input buffer
  while ((c = getchar()) != '\n' && c != EOF)
    ;

  c = getchar();

  // Return the character as a char type
  return (char)c;
}