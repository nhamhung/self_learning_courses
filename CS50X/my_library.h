#include <stdbool.h>

typedef char *string;

string get_string(const char *format, ...);

int get_int(const char *prompt);

float get_float(const char *prompt);

long get_long(const char *prompt);

char get_char(const char *prompt);