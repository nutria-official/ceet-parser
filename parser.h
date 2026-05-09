#ifndef PARSER_H
#define PARSER_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

enum types {
  character,
  number,
};

typedef struct tokens {
  enum types type;
  char character;
  float number;
} Token;

float parser(char* input, int size);
Token* shrink_input(char* input, int size);

#endif
