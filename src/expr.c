#include "expr.h"
#include "stack.h"
#include <stdio.h>
#include <string.h>

// Parses a 1 line RPN expression
ret_codes parseExpression(char *val) {
  char *p;
  p = strtok (val, " ");
  while (p != NULL) {
    processUserInput(p, strlen(p));
    // Calling this with null starts parsing the string where it left off the
    // last time it ran.
    p = strtok (NULL, " ");
  }

  return SUCCESS;
}
