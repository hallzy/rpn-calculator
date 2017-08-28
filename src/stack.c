#include "stack.h"
#include "operations.h"
#include <ctype.h>
#include <stdlib.h>

// Just define some starting points for the stack
void stack_init() {
  s.top        = -1;
  s.angle_mode = RADIANS;
  s.base_mode  = DECIMAL;
}

// s.top is -1 for emtpy, and 0 for a stack with 1 element. This function will
// make it easier to use when I need to determine the size of the stack.
int stack_size() {
  return s.top + 1;
}

// Add the number "f" to the top of the stack
void push(long double f) {
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

void remove_from_stack_index(unsigned int j) {
  for (int i =j; i < s.top; i++) {
    s.stk[i] = s.stk[i+1];
  }
  s.top--;
}

// This grabs the octal input string from the user and converts it into a number
// that I can use.
static ret_codes get_octal_number_and_push(char *val) {
  char *next;
  long numl;
  // if it is prepended like an octal number then take off the prefix and
  // see if the rest of the number is okay. Octal prefix is "0" followed by
  // numbers, so I need to knock off just one character
  val += 1;
  numl = strtol(val, &next, 8);
  if (next == val || *next != '\0') {
    return FAILED_TO_PUSH;
  }
  push(numl);
  return SUCCESS;
}

// This grabs the binary input string from the user and converts it into a
// number that I can use.
static ret_codes get_binary_number_and_push(char *val) {
  char *next;
  long numl;
  // if it is prepended like a binary number then take off the prefix and
  // see if the rest of the number is okay. The binary prefix is "0b" or "0B"
  val += 2;
  numl = strtol(val, &next, 2);
  if (next == val || *next != '\0') {
    return FAILED_TO_PUSH;
  }
  push(numl);
  return SUCCESS;
}

// This grabs the decimal or hex input string from the user and converts it into
// a numeric value that I can use.
static ret_codes get_decimal_and_hex_numbers_and_push(char *val) {
  char *next;
  long double num;
  // strtof automatically recognizes "0x" for hex numbers.
  num = strtof(val, &next);
  if (next == val || *next != '\0') {
    return FAILED_TO_PUSH;
  }
  push(num);
  return SUCCESS;
}

// Check if the user input string is an operation, or a number, and act
// accordingly
ret_codes processUserInput(char *val, int val_size) {
  int op;

  // Is the input an operation? If so, then do the operation
  if ((op = whichOperation(val)) != -1) {
    return performOperation(op);
  }
  // if it wasn't an operation it better be a number...
  else {
    // Check if it is an octal number. Octals are prefixed by "0" and then a
    // number
    if (val[0] == '0' && isdigit(val[1])) {
      return get_octal_number_and_push(val);
    }
    // Check if it is a binary number. Binary numbers are prefixed with either
    // "0b" or "0B"
    else if (val[0] == '0' && (val[1] == 'b' || val[1] == 'B')) {
      return get_binary_number_and_push(val);
    }
    else {
      // this will recognize decimal or hex values.
      // This is the last chance for the input to be a number. if it isn't, then
      // it fails silently here and doesn't do anything to the stack.
      return get_decimal_and_hex_numbers_and_push(val);
    }
  }
}

// Remove the element at the top and update the stack pointer.
long double pop() {
  long double popped = s.stk[s.top];
  s.top--;
  return popped;
}
