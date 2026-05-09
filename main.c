#include "parser.h"
#include "math.h"

#define MAX_INPUT_LENGTH 128

static int shrinked_size = 0;

int main () {
  char input[MAX_INPUT_LENGTH];
  fgets(input, MAX_INPUT_LENGTH, stdin);
  int size = 0;
  for (int i = 0; i < MAX_INPUT_LENGTH; i++) {
    if (input[i] == '\n' || input[i] == '\0') { // Takes input without newline.
      break;
    } else {
      size++;
    }
  }
  float output = parser(input, size);
  printf("result: %lf", output);
  return 1;
}

float parser(char* input, int size) {
  Token* tokenized_input = shrink_input(input, size);
  printf("\n");
  for (int i = 0; i < shrinked_size; i++) {
    if (tokenized_input[i].type == character) {
      printf("%c", tokenized_input[i].character);
    } else {
      printf("%lf", tokenized_input[i].number);
    }
  }
  printf("\n");

   

  return 1;
}

Token* shrink_input(char* input, int size) {
  bool previous_was_num = false; // Tokenize numbers;
  for (int i = 0; i < size; i++) {
    if (input[i] == '\n' || input[i] == '\0' || input[i] == ' ') {
      previous_was_num = false;
    } else {
      if ((input[i] >= '0' && input[i] <= '9') || input[i] == '.') {
        if(!previous_was_num) {
          shrinked_size++;
        }
        previous_was_num = true;
      } else {
        previous_was_num = false;
        shrinked_size++;
      }
    }
  }

  int radix = 0;
  Token *tokenized_input = calloc(shrinked_size, sizeof(Token));
  int index = shrinked_size; // Not minus one because i decrement index in the start.
  for (int i = size; i >= 0; i--) { // -- because radix works that way;
    if (input[i] == '\n' || input[i] == '\0' || input[i] == ' ') {
      radix = 0;
    } else {
      if (input[i] >= '0' && input[i] <= '9') {
        if (radix == 0 && input[i + 1] != '.') {
          index--;
        }
        tokenized_input[index].number += (input[i] - 48) * power(10, radix); // 48 is the ASCII representation of '0';
        tokenized_input[index].type = number;
        radix++;
      } else if (input[i] == '.' && index > 0) {
        tokenized_input[index].number = tokenized_input[index].number / power(10, radix);
        radix = 0;
      } else {
        radix = 0;
        index--;
        tokenized_input[index].character = input[i];
        tokenized_input[index].type = character;
      }
    }
  }
  return tokenized_input;
}

