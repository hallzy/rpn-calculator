#include "stack.h"
#include "ui.h"
#include "expr.h"
#include "kbhit.h"
#include "operations.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// Define THE stack here and static so that it can't be accesssed anywhere else,
// thus forcing everyone to use the below functions to interact with the stack
// and make the code more readable.
static stack s;

// Just define some starting points for the stack
void stack_init() {
  s.top        = -1;
  s.angle_mode = RADIANS;
  s.base_mode  = DECIMAL;

  expression_is_running = false;
  need_to_pop = false;
}

void set_angle_mode(angle_modes angle) {
  s.angle_mode = angle;
}

void set_base_mode(base_modes base) {
  s.base_mode = base;
}

angle_modes get_angle_mode() {
  return s.angle_mode;
}

base_modes get_base_mode() {
  return s.base_mode;
}

long double get_stack_value_at_index(int i) {
  return s.stk[i];
}

// s.top is -1 for emtpy, and 0 for a stack with 1 element. This function will
// make it easier to use when I need to determine the size of the stack.
int get_stack_size() {
  return s.top + 1;
}

void set_stack_size(int size) {
  // minus 1 because s.top is -1 when empty. So specify that the stack should be
  // empty means that size should equal 0.
  s.top = size - 1;
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

// Remove the element at the top and update the stack pointer.
long double pop() {
  long double popped = s.stk[s.top];
  s.top--;
  return popped;
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
  // Push twice so that the number you start editing the next time is
  // automatically pushed. The second one will be popped automatically if it is
  // found that the user is entering a number the next time.
  push(numl);
  push(numl);
  return SUCCESSFUL_PUSH;
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

  // Push twice so that the number you start editing the next time is
  // automatically pushed. The second one will be popped automatically if it is
  // found that the user is entering a number the next time.
  push(numl);
  push(numl);
  return SUCCESSFUL_PUSH;
}

// This grabs the decimal or hex input string from the user and converts it into
// a numeric value that I can use.
static ret_codes get_decimal_and_hex_numbers_and_push(char *val) {
  char *next;
  long double num;
  // strtold automatically recognizes "0x" for hex numbers.
  num = strtold(val, &next);
  if (next == val || *next != '\0') {
    return FAILED_TO_PUSH;
  }
  // Push twice so that the number you start editing the next time is
  // automatically pushed. The second one will be popped automatically if it is
  // found that the user is entering a number the next time.
  push(num);
  push(num);
  return SUCCESSFUL_PUSH;
}

// We have finished parsing the number now. Just push it using one of the 3
// functions defined above depending on what base the number is.
static ret_codes push_the_number(char *val) {
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

// In the event that val starts with a number, we assume it is a number and we
// run this in order to allow the user to finish typing their number. While
// getting the data for the number, we are also checking if the user inputs an
// operation on the end of the number for us to perform.
#ifndef TEST
void get_the_rest_of_the_number_from_user(char *val, operation_location *op) {
  // If it is a number, then we will want to wait until the user presses
  // enter before doing anything with it so that we know the user has
  // finished entering their number.
  char c[2];
  c[1] = 0;
  if (isdigit(val[0])) {
    while(!kbhit()) {
      int i = 0;
      printf("%c", val[i]);
      ++i;
      c[0] = getCharacter();
      *op = whichOperation(c);
      if (c[0] == ENTER_KEY) {
        // if we get into this then we need to reset op, because it was just
        // given a new value above.
        op->operation_index = -1;
        op->operation_type_index = -1;
        val[i] = 0;
        return;
      }
      else if (op->operation_index != -1) {
        val[i] = 0;
        return;
      }
      // Is the input an operation? If so, then do the operation after pushing
      // the number
      val[i] = c[0];
    }
  }
}
#endif // TEST

static ret_codes parseNumber(char *val) {
#ifndef TEST
  operation_location op;
  op.operation_type_index=-1;
  op.operation_index=-1;
#endif // TEST
  ret_codes ret;
  // If I am entering a number after I JUST entered a number onto the stack,
  // the number is on the stack twice automatically. If I get to this point
  // after JUST adding a number, it means I need to overwrite the latest
  // number (which was duplicate of the last one).
  if (need_to_pop && !expression_is_running) {
    pop();
    print_stack();
  }
  need_to_pop = true;
#ifndef TEST
  // If we are in an expression there is no need to wait for more characters
  // because we have them all already.
  if (!expression_is_running) {
    // also returns the operation op index
    get_the_rest_of_the_number_from_user(val, &op);
  }
  else {
#endif // TEST
    val[strlen(val)-1] = 0;
#ifndef TEST
  }
#endif // TEST
  // We now have a number, so figure out what base it is, and push it.
  ret = push_the_number(val);

  // If pushing a number failed, then return the error code
  if (ret != SUCCESSFUL_PUSH) {
    // if it failed, then don't pop next time
    need_to_pop = false;
    return ret;
  }
  // If no error happened in the previous step, check if we had an operation
  // on the end of the number and perform it.
#ifndef TEST
  if (op.operation_index != -1) {
    // If my number ended with an operation, then I have pushed that number
    // twice already. Do get expected results, I need to pop one of the
    // duplicates off first. I also need to tell the program NOT to pop the
    // number off the next time.
    pop();
    return performOperation(op);
  }
#endif //TEST
  // If anything else, then return ret;
  return ret;
}

// Check if the user input string is an operation, or a number, and act
// accordingly
ret_codes processUserInput(char *val, int val_size) {
  operation_location op;

  // Is the input an operation? If so, then do the operation
  op = whichOperation(val);
  if (op.operation_index != -1) {
    return performOperation(op);
  }
  // Check to see if the input is an RPN string expression
  // If it is, then I need to parse the string to break it into parts.
  else if(val[0] == EXPRESSION_CHAR) {
    // Parse the expression.
    // + strlen() is to remove the "expr: " string from the input
    return parseExpression(val+1);
  }
  // if it wasn't an operation it better be a number...
  else {
    return parseNumber(val);
  }
}
