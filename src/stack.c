#include "stack.h"
#include "operations.h"
#include "itoa.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

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

// This grabs the octal input string from the user and converts it into a number
// that I can use.
static ret_codes get_octal_number_and_add_to_stack(char *val) {
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
  add_to_stack(numl);
  return SUCCESS;
}

// This grabs the binary input string from the user and converts it into a
// number that I can use.
static ret_codes get_binary_number_and_add_to_stack(char *val) {
  char *next;
  long numl;
  // if it is prepended like a binary number then take off the prefix and
  // see if the rest of the number is okay. The binary prefix is "0b" or "0B"
  val += 2;
  numl = strtol(val, &next, 2);
  if (next == val || *next != '\0') {
    return FAILED_TO_PUSH;
  }
  add_to_stack(numl);
  return SUCCESS;
}

// This grabs the decimal or hex input string from the user and converts it into
// a numeric value that I can use.
static ret_codes get_decimal_and_hex_numbers_and_add_to_stack(char *val) {
  char *next;
  float num;
  // strtof automatically recognizes "0x" for hex numbers.
  num = strtof(val, &next);
  if (next == val || *next != '\0') {
    return FAILED_TO_PUSH;
  }
  add_to_stack(num);
  return SUCCESS;
}

// Check if the user input string is an operation, or a number, and act
// accordingly
ret_codes push(char *val, int val_size) {
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
      return get_octal_number_and_add_to_stack(val);
    }
    // Check if it is a binary number. Binary numbers are prefixed with either
    // "0b" or "0B"
    else if (val[0] == '0' && (val[1] == 'b' || val[1] == 'B')) {
      return get_binary_number_and_add_to_stack(val);
    }
    else {
      // this will recognize decimal or hex values.
      // This is the last chance for the input to be a number. if it isn't, then
      // it fails silently here and doesn't do anything to the stack.
      return get_decimal_and_hex_numbers_and_add_to_stack(val);
    }
  }
}

// Remove the element at the top and update the stack pointer.
float pop() {
  float popped = s.stk[s.top];
  s.top--;
  return popped;
}

// Print all of my calculator information and stack info.
void print_stack() {
  // Is my calculator in Radians or Degrees?
  if (s.angle_mode == RADIANS) {
    printf("RAD\n");
  }
  else {
    printf("DEG\n");
  }

  // What base am I in?
  // Make sure to print the stack info to respect the base.
  if (s.base_mode == HEXADECIMAL) {
    printf("HEX\n\n");
    // Iterate through the whole stack and print out each number as a hex value.
    for (int i = 0; i <= s.top; i++) {
      printf("%d:  %x\n", i+1, (unsigned int)s.stk[i]);
    }
  }
  else if (s.base_mode == DECIMAL) {
    printf("DEC\n\n");
    // Iterate through the whole stack and print out each number as a decimal
    // value.
    for (int i = 0; i <= s.top; i++) {
      printf("%d:  %f\n", i+1, s.stk[i]);
    }
  }
  else if (s.base_mode == OCTAL) {
    printf("OCT\n\n");
    // Iterate through the whole stack and print out each number as an octal
    // value.
    for (int i = 0; i <= s.top; i++) {
      printf("%d:  %o\n", i+1, (unsigned int)s.stk[i]);
    }
  }
  else {
    printf("BIN\n\n");
    // Iterate through the whole stack and print out each number as a binary
    // value.
    for (int i = 0; i <= s.top; i++) {
      // I need to use itoa to do this since C doesn't have any built-in way to
      // print binary numbers
      // This converts the number into a string represented as a binary number
      char buf[128];
      itoa((unsigned int)s.stk[i], buf, 2);
      printf("%d:  %s\n", i+1, buf);
    }
  }
}
