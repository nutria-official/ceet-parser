#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LENGTH 256

typedef enum {
  NO_ERROR,
  BAD_INPUT,
} ErrorCodes;

void tokenizer(char *input);
ErrorCodes should_be_calculated(char *input);

int main() {
  char *input = malloc(sizeof(char) * MAX_INPUT_LENGTH);
  fgets(input, MAX_INPUT_LENGTH, stdin); // For testing.
  printf("input: %s\n", input);
  if (should_be_calculated(input) == BAD_INPUT) {
    return BAD_INPUT;
  }
  return NO_ERROR;
}
ErrorCodes should_be_calculated(char *input) {
  if (!(strlen(input) > 0)) {
    printf("The given input has no values!\n");
    return BAD_INPUT;
  }
  if (memchr(input, '=', 1) != NULL) {
    char *output = malloc(sizeof(char) * (strlen(input) - 1));
    strncpy(output, input + sizeof(char), sizeof(char) * (strlen(input) - 1));
    tokenizer(output);
    printf("output: %s\n", output);
  } else {
    printf("Should not be calculated\n");
  }
  return NO_ERROR;
}

void tokenizer(char *input) {
  size_t open_parentheses[MAX_INPUT_LENGTH];
  size_t closed_parentheses[MAX_INPUT_LENGTH];

  for (int i = 0; i < strlen(input); i++) {
    if (input[i] == '(') {
      open_parentheses[i] = i;
    }
    if (input[i] == ')') {
      closed_parentheses[i] = i;
    }
  }
}
