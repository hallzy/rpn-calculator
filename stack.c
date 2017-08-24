#include "stack.h"
#include "operations.h"
#include "itoa.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void stack_init() {
  s.top      = -1;
  s.angle_mode = RADIANS;
  s.base_mode = DECIMAL;
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

static ret_codes get_octal_number_and_add_to_stack(char *val) {
  char *next;
  long numl;
  // if it is prepended like an octal number then take off the prefix and
  // see if the rest of the number is okay.
  val += 1;
  numl = strtol(val, &next, 8);
  if (next == val || *next != '\0') {
    return FAILED_TO_PUSH;
  }
  add_to_stack(numl);
  return SUCCESS;
}

static ret_codes get_binary_number_and_add_to_stack(char *val) {
  char *next;
  long numl;
  // if it is prepended like a binary number then take off the prefix and
  // see if the rest of the number is okay.
  val += 2;
  numl = strtol(val, &next, 2);
  if (next == val || *next != '\0') {
    return FAILED_TO_PUSH;
  }
  add_to_stack(numl);
  return SUCCESS;
}

static ret_codes get_decimal_and_hex_numbers_and_add_to_stack(char *val) {
  char *next;
  float num;
  num = strtof(val, &next);
  if (next == val || *next != '\0') {
    return FAILED_TO_PUSH;
  }
  add_to_stack(num);
  return SUCCESS;
}

ret_codes push(char *val, int val_size) {
  int op;

  // Is the input an operation
  if ((op = whichOperation(val)) != -1) {
    return performOperation(op);
  }
  // if it wasn't an operation it better be a number...
  else {
    // Check if it is an octal number
    if (val[0] == '0' && isdigit(val[1])) {
      return get_octal_number_and_add_to_stack(val);
    }
    // Check if it is a binary number
    else if (val[0] == '0' && (val[1] == 'b' || val[1] == 'B')) {
      return get_binary_number_and_add_to_stack(val);
    }
    else {
      // this will recognize decimal or hex values.
      return get_decimal_and_hex_numbers_and_add_to_stack(val);
    }
  }
}

float pop() {
  float popped = s.stk[s.top];
  s.top--;
  return popped;
}

void print_stack() {
  if (s.angle_mode == RADIANS) {
    printf("RAD\n");
  }
  else {
    printf("DEG\n");
  }

  if (s.base_mode == HEXADECIMAL) {
    printf("HEX\n\n");
    for (int i = 0; i <= s.top; i++) {
      printf("%d:  %x\n", i+1, (unsigned int)s.stk[i]);
    }
  }
  else if (s.base_mode == DECIMAL) {
    printf("DEC\n\n");
    for (int i = 0; i <= s.top; i++) {
      printf("%d:  %f\n", i+1, s.stk[i]);
    }
  }
  else if (s.base_mode == OCTAL) {
    printf("OCT\n\n");
    for (int i = 0; i <= s.top; i++) {
      printf("%d:  %o\n", i+1, (unsigned int)s.stk[i]);
    }
  }
  else {
    printf("BIN\n\n");
    for (int i = 0; i <= s.top; i++) {
      char buf[128];
      itoa((unsigned int)s.stk[i], buf, 2);
      printf("%d:  %s\n", i+1, buf);
    }
  }
}
