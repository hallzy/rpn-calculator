#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

int main() {
  stack_init();

  char input[128];
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
}
