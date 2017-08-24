#include "stack.h"
#include "operations.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void stack_init() {
  s.top      = -1;
  s.rad_mode = 1;
}

int stack_size() {
  return s.top + 1;
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
  float num;

  // Is the input an operation
  if ((op = whichOperation(val)) != -1) {
    return performOperation(op);
  }
  // if it wasn't an operation it better be a number...
  else {
    char *next;
    // this will recognize decimal or hex values.
    num = strtof(val, &next);
    if (next == val || *next != '\0') {

      return FAILED_TO_PUSH;
    }
    add_to_stack(num);
    return SUCCESS;
  }
}

float pop() {
  float popped = s.stk[s.top];
  s.top--;
  return popped;
}

void print_stack() {
  if (s.rad_mode == 1) {
    printf("RAD\n\n");
  }
  else {
    printf("DEG\n\n");
  }
  for (int i = 0; i <= s.top; i++) {
    printf("%d:  %f\n", i+1, s.stk[i]);
  }
}
