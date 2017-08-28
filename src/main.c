#ifndef TEST
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"
#include "ui.h"
#else
#include "test.h"
#endif // TEST

int main() {
#ifndef TEST
  stack_init();

  // Arbitrary size, but I can't see many reasons to have more than 128
  // characters for an input
  char input[128];

  while(1) {
    // And give me the result!
    print_stack();

    fgets(input, sizeof(input), stdin);
    // Remove the newline character unless it is the only thing in the string (I
    // will use that later in order to drop the element from the top of the
    // stack)
    if (input[0] != '\n') {
      input[strlen(input)-1] = 0;
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
