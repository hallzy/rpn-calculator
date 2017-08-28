#include "expr.h"
#include "stack.h"
#include <stdio.h>
#include <string.h>

// Parses a 1 line RPN expression
ret_codes parseExpression(char *val) {
  char *p;
  // strtok searches my string (first arg) for the delimiters (arg 2). When it
  // has found one it gives me the string that I want in p.
  // Example: if val = "This is a test", p will be "This", then "is", then "a",
  // and then finally "test"
  // NOTE: the delimiters can be a list of delimiters such as " ,.-". Currently
  // I do not need this but it is something to consider in the future if I ever
  // have the need for it.
  p = strtok (val, " ");
  // As soon as p becomes null, we have reached the end of our string.
  while (p != NULL) {
    // For every result, send it to get processed
    processUserInput(p, strlen(p));
    // Calling this with null starts parsing the string where it left off the
    // last time it ran.
    p = strtok (NULL, " ");
  }

  return SUCCESS;
}
