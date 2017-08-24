#include "stack.h"
#include "operations.h"
#include <string.h>
#include <math.h>


// --- STACK MANIPULATION FUNCTIONS ---

// Blank entry duplicates the last item on the stack
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

// Removes the last entry on the stack
static ret_codes drop() {
  // Make sure there are at least 1 elements on the stack
  if (s.top >= 0) {
    pop();
    return SUCCESS;
  }
  return FAILED_OPERATION;
}

// Swap the order of the last two stack entries
static ret_codes swap() {
  // Make sure there are at least 1 elements on the stack
  if (s.top >= 0) {
    float num2 = pop();
    float num1 = pop();
    add_to_stack(num2);
    add_to_stack(num1);
    return SUCCESS;
  }
  return FAILED_OPERATION;
}

// --- MATHEMATICAL OPERATORS ---

// Adds the last two stack entries together
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

// Subtracts the last two stack entries together
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

// Multiplies the last two stack entries together
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

// Divides the last two stack entries together
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

// x to the power of y
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

// squared
static ret_codes squared() {
  // Make sure there are at least 1 elements on the stack
  if (s.top >= 0) {
    float num = pop();
    add_to_stack(pow(num, 2));
    return SUCCESS;
  }
  return FAILED_OPERATION;
}

// cubed
static ret_codes cubed() {
  // Make sure there are at least 1 elements on the stack
  if (s.top >= 0) {
    float num = pop();
    add_to_stack(pow(num, 3));
    return SUCCESS;
  }
  return FAILED_OPERATION;
}

// Square Roots the last stack entry
static ret_codes my_sqrt() {
  // Make sure there are at least 1 elements on the stack
  if (s.top >= 0) {
    float num = pop();
    add_to_stack(sqrt(num));
    return SUCCESS;
  }
  return FAILED_OPERATION;
}

// Cube Roots the last stack entry
static ret_codes my_cbrt() {
  // Make sure there are at least 1 elements on the stack
  if (s.top >= 0) {
    float num = pop();
    add_to_stack(cbrt(num));
    return SUCCESS;
  }
  return FAILED_OPERATION;
}

// xth Root the last stack entry
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

// -----------------------------------------------------------------------------

const static struct {
  const char *name;
  ret_codes (*func)(void);

} calc_operations [] = {
  // Stack Manipulations
    {"\n"   , duplicate } ,
    {"drop" , drop      } ,
    {"d"    , drop      } ,
    {"s"    , swap      } ,
    {"swap" , swap      } ,

  // Math Operations
    {"+"    , plus      } ,
    {"-"    , minus     } ,
    {"*"    , multiply  } ,
    {"/"    , divide    } ,
    {"pow"  , my_pow    } ,
    {"**2"  , squared   } ,
    {"**3"  , cubed     } ,
    {"sqrt" , my_sqrt   } ,
    {"cbrt" , my_cbrt   } ,
    {"xrt"  , xrt       } ,
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
