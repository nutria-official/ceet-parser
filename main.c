#include "parser.h"
#include "math.h"

#define MAX_INPUT_LENGTH 128

static int shrinked_size = 0; // The amount of tokens in parsed string.

int main () {
  char input[MAX_INPUT_LENGTH];
  if (fgets(input, MAX_INPUT_LENGTH, stdin) == NULL) perror("fgets was null\n");
  int size = 0;
  for (int i = 0; i < MAX_INPUT_LENGTH; i++) {
    if (input[i] == '\n' || input[i] == '\0') { // Takes input without newline.
      break;
    } else {
      size++;
    }
  }
  float output = parser(input, size);
  printf("result: %lf\n", output);
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


  float output = evaluate(tokenized_input, shrinked_size);
  free(tokenized_input);
  return output;
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
  Token *tokenized_input = calloc(shrinked_size, sizeof(Token)); // Needs to be calloc because I'm doing arithmatic on the zeros.
  int index = shrinked_size; // Not minus one because i decrement index in the start.
  for (int i = size; i >= 0; i--) { // -- because radix works that way: The rightest decimal in a number is always radix 0, so i know the radix of all the upcoming decimals when itarating from the back;
    if (input[i] == '\n' || input[i] == '\0' || input[i] == ' ') {
      radix = 0;
    } else {
      if (input[i] >= '0' && input[i] <= '9') {
        if (radix == 0 && input[i + 1] != '.') { // Am i lowkey reading out of memory here?
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

float evaluate(Token* input, int size) {
  Token* calc_input = malloc((size - 2) * sizeof(Token)); // -3 because that for each operation 2 floats and one operator disapears.
  if (calc_input == NULL) {
    perror("Not enough available memory.\n");
    return 0;
  }

  float val_a = 0;
  float val_b = input[size - 1].number;
  char operator = '+';
  int operator_index = 0;

  bool previous_was_operator = false;
  bool new_operator = true; // If a new pair of values should be selected do to a operator with higher priority.
  bool first_operator = false;

  // Calculate result.
  for (int i = size - 1; i >= 0; i--) {
    if (input[i].type == number) {
      if (previous_was_operator) {
        if (new_operator) {
          val_b = val_a;
          val_a = input[i].number;
        } else {
          val_a = input[i].number;
        }
      }
      previous_was_operator = false;
    }
    else
    {
      previous_was_operator = true;

      if (first_operator) {
        operator = input[i].character;
        operator_index = i;
        first_operator = false;
        new_operator = true;
      }
      switch (operator) {
        case '+':
          if (input[i].character == '+' || input[i].character == '-' || input[i].character == '*' || input[i].character == '/') {
            operator = input[i].character;
            operator_index = i;
            new_operator = true;
          } else {
            new_operator = false;
          }
          break;
        case '-':
          if (input[i].character == '-' || input[i].character == '*' || input[i].character == '/') {
            operator = input[i].character;
            operator_index = i;
            new_operator = true;
          } else {
            new_operator = false;
          }
          break;
        case '*':
          if (input[i].character == '*' || input[i].character == '/') {
            operator = input[i].character;
            operator_index = i;
            new_operator = true;
          } else {
            new_operator = false;
          }
          break;
        case '/':
          if (input[i].character == '/') {
            operator = input[i].character;
            operator_index = i;
            new_operator = true;
          } else {
            new_operator = false;
          }
          break;
        default:
          printf("This should not happen.\n");
          break;
      }
    }
  }
  
  float result = 0;

  switch (operator) {
    case '+':
      result = val_a + val_b;
      break;
    case '-': 
      result = val_a - val_b;
      break;
    case '*':
      result = val_a * val_b;
      break;
    case '/':
      result = val_a / val_b;
      break;
    default:
      printf("This should also not happen.\n");
      break;
  }
  
  printf("val_a: %lf\n", val_a);
  printf("val_b: %lf\n", val_b);
  printf("Result: %lf\n", result);

  int offset = 0; // For skipping the indexes.
  for (int i = 0; i < size - 2; i++) {
    if (i == operator_index - 1) {
      calc_input[i].type = number;
      calc_input[i].number = result;
      offset = 2;
    } else {
    calc_input[i] = input[i + offset];
    }
  }
  for (int i = 0; i < size - 2; i++) {
    printf("calc_input[%d].number : %lf\n", i, calc_input[i].number);
  }

  for (int i = 0; i < size; i++) {
    printf("input[%d].number: %lf\n", i, input[i].number);
  }

  if (size <= 3) {
    free(calc_input);
    return result;
  }
  float new_result = evaluate(calc_input, size - 2);
  free(calc_input);
  return new_result;
}

