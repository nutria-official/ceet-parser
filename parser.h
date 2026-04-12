#ifndef PARSER_H
#define PARSER_H

enum types {
  character,
  number,
};

typedef struct tokens {
  enum types type;
  char character;
  int number;
} Token;

int parser(char* input, int size);
Token* shrink_input(char* input, int size);

#endif
