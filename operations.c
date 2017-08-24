#include "stack.h"
#include "operations.h"
#include <string.h>
#include <math.h>

static ret_codes duplicate() {
  // Make sure there are at least 1 elements on the stack
  if (s.top >= 0) {
    float num1 = pop();
    add_to_stack(num1);
    add_to_stack(num1);
    return SUCCESS;
  }
  return FAILED_OPERATION;
}

static ret_codes drop() {
  // Make sure there are at least 1 elements on the stack
  if (s.top >= 0) {
    pop();
    return SUCCESS;
  }
  return FAILED_OPERATION;
}

static ret_codes plus() {
  // Make sure there are at least 2 elements on the stack
  if (s.top >= 1) {
    float num2 = pop();
    float num1 = pop();
    add_to_stack(num1+num2);
    return SUCCESS;
  }
  return FAILED_OPERATION;
}

static ret_codes minus() {
  // Make sure there are at least 2 elements on the stack
  if (s.top >= 1) {
    float num2 = pop();
    float num1 = pop();
    add_to_stack(num1-num2);
    return SUCCESS;
  }
  return FAILED_OPERATION;
}

static ret_codes multiply() {
  // Make sure there are at least 2 elements on the stack
  if (s.top >= 1) {
    float num2 = pop();
    float num1 = pop();
    add_to_stack(num1*num2);
    return SUCCESS;
  }
  return FAILED_OPERATION;
}

static ret_codes divide() {
  // Make sure there are at least 2 elements on the stack
  if (s.top >= 1) {
    float num2 = pop();
    float num1 = pop();
    add_to_stack(num1/num2);
    return SUCCESS;
  }
  return FAILED_OPERATION;
}

static ret_codes my_pow() {
  // Make sure there are at least 1 elements on the stack
  if (s.top >= 0) {
    float num2 = pop();
    float num1 = pop();
    add_to_stack(pow(num1, num2));
    return SUCCESS;
  }
  return FAILED_OPERATION;
}

static ret_codes squared() {
  // Make sure there are at least 1 elements on the stack
  if (s.top >= 0) {
    float num = pop();
    add_to_stack(pow(num, 2));
    return SUCCESS;
  }
  return FAILED_OPERATION;
}

static ret_codes cubed() {
  // Make sure there are at least 1 elements on the stack
  if (s.top >= 0) {
    float num = pop();
    add_to_stack(pow(num, 3));
    return SUCCESS;
  }
  return FAILED_OPERATION;
}

static ret_codes my_sqrt() {
  // Make sure there are at least 1 elements on the stack
  if (s.top >= 0) {
    float num = pop();
    add_to_stack(sqrt(num));
    return SUCCESS;
  }
  return FAILED_OPERATION;
}

static ret_codes my_cbrt() {
  // Make sure there are at least 1 elements on the stack
  if (s.top >= 0) {
    float num = pop();
    add_to_stack(cbrt(num));
    return SUCCESS;
  }
  return FAILED_OPERATION;
}

static ret_codes xrt() {
  // Make sure there are at least 1 elements on the stack
  if (s.top >= 0) {
    float num2 = pop();
    float num1 = pop();
    add_to_stack(pow(num1, 1.0/num2));
    return SUCCESS;
  }
  return FAILED_OPERATION;
}

const static struct {
  const char *name;
  ret_codes (*func)(void);

} calc_operations [] = {
    {"\n"   , duplicate } , // Blank entry duplicates the last item on the stack
    {"drop" , drop      } , // Removes the last entry on the stack
    {"+"    , plus      } , // Adds the last two stack entries together
    {"-"    , minus     } , // Subtracts the last two stack entries together
    {"*"    , multiply  } , // Multiplies the last two stack entries together
    {"/"    , divide    } , // Divides the last two stack entries together
    {"pow"  , my_pow    } , // x to the power of y
    {"**2"  , squared   } , // squared
    {"**3"  , cubed     } , // cubed
    {"sqrt" , my_sqrt   } , // Square Roots the last stack entry
    {"cbrt" , my_cbrt   } , // Cube Roots the last stack entry
    {"xrt"  , xrt       } , // xth Root the last stack entry
    {"//"   , xrt       } ,
  };

// returns the index of the operation
int whichOperation(char *s) {
  int num_of_operations = sizeof(calc_operations)/sizeof(calc_operations[0]);

  for (int i = 0; i < num_of_operations; i++) {
    if (!strcmp(s, calc_operations[i].name) && calc_operations[i].func) {
      return i;
    }
  }
  return -1;
}

ret_codes performOperation(int op) {
  return calc_operations[op].func();
}
