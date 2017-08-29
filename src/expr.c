#include "expr.h"
#include "stack.h"
#include <stdio.h>
#include <string.h>

// Parses a 1 line RPN expression
ret_codes parseExpression(char *val) {
  char *p;
  char a[strlen(val)+1];
  expression_is_running = true;
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
    // Add a newline to the end of each input string
    strncpy(a, p, strlen(p));
    a[strlen(p)] = '\n';
    a[strlen(p)+1] = 0;
    // For every result, send it to get processed
    ret_codes ret = processUserInput(a, strlen(a));
    // The way that this works is that with the epression, it is effectively
    // entering a number, then pressing enter, then entering another number and
    // pressing enter, etc. This would result in mutiple duplicates to be left
    // on the stack and will produce an incorrect answer. Therefore, if we get
    // here, we should pop the duplicate number off.
    // Therefore, if we pushed a number, pop one of the numbers
    if (ret == SUCCESSFUL_PUSH) {
      pop();
    }
    // Calling this with null starts parsing the string where it left off the
    // last time it ran.
    p = strtok (NULL, " ");
  }

  expression_is_running = false;
  return SUCCESSFUL_EXPRESSION;
}
