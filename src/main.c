#ifndef TEST
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"
#else
#include "test.h"
#endif // TEST

int main() {
#ifndef TEST
  stack_init();

  char input[128];

  printf("The calculator is now running. Do some stuff!\n");
  while(1) {
    fgets(input, sizeof(input), stdin);
    if (input[0] != '\n') {
      input[strlen(input)-1] = 0;
    }

    if (strcmp(input, "q") ==0) return 0;

    printf("===============================================================\n");
    push(input, strlen(input));

    print_stack();
    printf("===============================================================\n");
  }
  return 0;

#else
  return performTests();
#endif // TEST
}
