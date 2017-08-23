#include "stack.h"
#include "operations.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void stack_init() {
  s.top = -1;
}

static int isNumber(char *s, int s_len) {
  int already_has_decimal=0;
  for (int i = 0; i < s_len; i++) {
    if (isdigit(s[i])) {
      continue;
    }
    else if (s[i] == '.' && already_has_decimal == 0) {
        already_has_decimal=1;
        continue;
    }
    // failed. Not a number
    return 0;
  }
  return 1;
}

void add_to_stack(float f) {
  // first check that we haven't maxed out the stack already.
  // If we have already reached MAX_STK then drop the element at the bottom of
  // the stack, and move all elements down to make room for a new one.
  if (s.top == MAX_STK - 1) {
    for (int i = 1; i < MAX_STK; i++) {
      s.stk[i-1] = s.stk[i];
    }
    s.top--;
  }
  s.top++;
  s.stk[s.top] = f;
}

ret_codes push(char *val, int val_size) {
  int op;
  if (val_size == 0) {
    return NOTHING_TO_PUSH;
  }
  else if (isNumber(val, val_size)) {
    add_to_stack(atof(val));
    return SUCCESS;
  }
  else if ((op = whichOperation(val)) != -1) {
    return performOperation(op);
  }
  else {
    return FAILED_TO_PUSH;
  }
}

float pop() {
  float popped = s.stk[s.top];
  s.top--;
  return popped;
}

void print_stack() {
  for (int i = 0; i <= s.top; i++) {
    printf("%d:  %f\n", i+1, s.stk[i]);
  }
}
