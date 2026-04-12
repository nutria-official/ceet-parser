#include "parser.h"
#include "math.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

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
  int output = parser(input, size);
  printf("result: %d", output);
  return 1;
}

int parser(char* input, int size) {
  Token* shrinked_input = shrink_input(input, size);
  printf("\n");
  for (int i = 0; i < shrinked_size; i++) {
    if (shrinked_input[i].type == character) {
      printf("%c", shrinked_input[i].character);
    } else {
      printf("%d", shrinked_input[i].number);
    }
  }
  printf("\n");
  return 1;
}

Token* shrink_input(char* input, int size) {
  bool previous_was_int = false; // Tokenize numbers;
  for (int i = 0; i < size; i++) {
    if (input[i] == '\n' || input[i] == '\0' || input[i] == ' ') {
      previous_was_int = false;
    } else {
      if (input[i] >= '0' && input[i] <= '9') {
        if(!previous_was_int) {
          shrinked_size++;
        }
        previous_was_int = true;
      } else {
        previous_was_int = false;
        shrinked_size++;
      }
    }
  }

  int radix = 0;
  Token *shrinked_input = calloc(shrinked_size, sizeof(Token));
  int index = shrinked_size; // Not minus one because we decrement index in the start.
  for (int i = size; i >= 0; i--) { // -- because radix works that way;
    if (input[i] == '\n' || input[i] == '\0' || input[i] == ' ') {
      radix = 0;
    } else {
      if (input[i] >= '0' && input[i] <= '9') {
        if (radix == 0) {
          index--;
        }
        shrinked_input[index].number += (input[i] - 48) * power(10, radix); // 48 is the ASCII representation of '0';
        shrinked_input[index].type = number;
        radix++;
      } else {
        radix = 0;
        index--;
        shrinked_input[index].character = input[i];
        shrinked_input[index].type = character;
      }
    }
  }
  return shrinked_input;
}

