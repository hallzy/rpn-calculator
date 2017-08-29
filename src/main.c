#ifndef TEST
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"
#include "kbhit.h"
#include "ui.h"
#include "expr.h"
#else
#include "test.h"
#endif // TEST

int main() {
#ifndef TEST
  stack_init();

  // Arbitrary size, but I can't see many reasons to have more than 128
  // characters for an input
  char input[128];

  // Set up the terminal so that the program will accept characters as they come
  // instead of after a newline.
  singleCharacterInputInit();

  // Keep looking for key presses.
  while(!kbhit()) {
    // Print the initial stack.
    print_stack();

    input[0] = getchar();
    input[1] = 0;
    // if the input is the expression char, then this is a one line RPN
    // expression that needs to be evaluated.
    if (input[0] == EXPRESSION_CHAR) {
      int i = 0;
      // Allow characters to be entered until a newline is reached. Down further
      // we will send it off to be processed.
      while(!kbhit()) {
        printf("%c", input[i]);
        ++i;
        input[i] = getchar();
        if (input[i] == '\n') {
          input[i] = 0;
          break;
        }
      }

    }

    // q will be used to quit the calculator
    if (strcmp(input, "q") ==0) return 0;

    // Give the user input to the calcualtor, and let it do its thing
    processUserInput(input, strlen(input));
  }
  return 0;

#else
  // If the program has been compiled with TEST defined, this will be the only
  // thing in main
  return performTests();
#endif // TEST
}
