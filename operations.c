#include "stack.h"
#include "operations.h"
#include <string.h>
#include <math.h>

// --- STACK MANIPULATION FUNCTIONS ---

// Blank entry duplicates the last item on the stack
static ret_codes duplicate() {
  // Make sure there are at least 1 elements on the stack
  if (stack_size() >= 1) {
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
  if (stack_size() >= 1) {
    pop();
    return SUCCESS;
  }
  return FAILED_OPERATION;
}

// Swap the order of the last two stack entries
static ret_codes swap() {
  // Make sure there are at least 1 elements on the stack
  if (stack_size() >= 1) {
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
  if (stack_size() >= 2) {
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
  if (stack_size() >= 2) {
    float num2 = pop();
    float num1 = pop();
    add_to_stack(num1-num2);
    return SUCCESS;
  }
  return FAILED_OPERATION;
}

// Change the sign on the number
static ret_codes neg() {
  // Make sure there are at least 1 elements on the stack
  if (stack_size() >= 1) {
    float num = pop();
    add_to_stack(num*-1);
    return SUCCESS;
  }
  return FAILED_OPERATION;
}

// Multiplies the last two stack entries together
static ret_codes multiply() {
  // Make sure there are at least 2 elements on the stack
  if (stack_size() >= 2) {
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
  if (stack_size() >= 2) {
    float num2 = pop();
    float num1 = pop();
    add_to_stack(num1/num2);
    return SUCCESS;
  }
  return FAILED_OPERATION;
}

// x to the power of y
static ret_codes my_pow() {
  // Make sure there are at least 2 elements on the stack
  if (stack_size() >= 2) {
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
  if (stack_size() >= 1) {
    float num = pop();
    add_to_stack(pow(num, 2));
    return SUCCESS;
  }
  return FAILED_OPERATION;
}

// cubed
static ret_codes cubed() {
  // Make sure there are at least 1 elements on the stack
  if (stack_size() >= 1) {
    float num = pop();
    add_to_stack(pow(num, 3));
    return SUCCESS;
  }
  return FAILED_OPERATION;
}

// Square Roots the last stack entry
static ret_codes my_sqrt() {
  // Make sure there are at least 1 elements on the stack
  if (stack_size() >= 1) {
    float num = pop();
    add_to_stack(sqrt(num));
    return SUCCESS;
  }
  return FAILED_OPERATION;
}

// Cube Roots the last stack entry
static ret_codes my_cbrt() {
  // Make sure there are at least 1 elements on the stack
  if (stack_size() >= 1) {
    float num = pop();
    add_to_stack(cbrt(num));
    return SUCCESS;
  }
  return FAILED_OPERATION;
}

// xth Root the last stack entry
static ret_codes xrt() {
  // Make sure there are at least 2 elements on the stack
  if (stack_size() >= 2) {
    float num2 = pop();
    float num1 = pop();
    add_to_stack(pow(num1, 1.0/num2));
    return SUCCESS;
  }
  return FAILED_OPERATION;
}

// absolute value of number
static ret_codes my_abs() {
  // Make sure there are at least 1 elements on the stack
  if (stack_size() >= 1) {
    float num = pop();

    if (num < 0) {
      num *= -1;
    }
    add_to_stack(num);
    return SUCCESS;
  }
  return FAILED_OPERATION;
}

// invert the value
static ret_codes inv() {
  // Make sure there are at least 1 elements on the stack
  if (stack_size() >= 1) {
    float num = pop();
    add_to_stack(1.0/num);
    return SUCCESS;
  }
  return FAILED_OPERATION;
}

static ret_codes sine() {
  // Make sure there are at least 1 elements on the stack
  if (stack_size() >= 1) {
    float num = pop();
    if (s.rad_mode) {
      add_to_stack(sin(num));
    }
    else {
      add_to_stack(sin(num*pi/180.0));
    }
    return SUCCESS;
  }
  return FAILED_OPERATION;
}

static ret_codes cosine() {
  // Make sure there are at least 1 elements on the stack
  if (stack_size() >= 1) {
    float num = pop();
    if (s.rad_mode) {
      add_to_stack(cos(num));
    }
    else {
      add_to_stack(cos(num*pi/180.0));
    }
    return SUCCESS;
  }
  return FAILED_OPERATION;
}

static ret_codes tangent() {
  // Make sure there are at least 1 elements on the stack
  if (stack_size() >= 1) {
    float num = pop();
    if (s.rad_mode) {
      add_to_stack(tan(num));
    }
    else {
      add_to_stack(tan(num*pi/180.0));
    }
    return SUCCESS;
  }
  return FAILED_OPERATION;
}

static ret_codes asine() {
  // Make sure there are at least 1 elements on the stack
  if (stack_size() >= 1) {
    float num = pop();
    if (s.rad_mode) {
      add_to_stack(asin(num));
    }
    else {
      add_to_stack(asin(num)*180.0/pi);
    }
    return SUCCESS;
  }
  return FAILED_OPERATION;
}

static ret_codes acosine() {
  // Make sure there are at least 1 elements on the stack
  if (stack_size() >= 1) {
    float num = pop();
    if (s.rad_mode) {
      add_to_stack(cos(num));
    }
    else {
      add_to_stack(acos(num)*180.0/pi);
    }
    return SUCCESS;
  }
  return FAILED_OPERATION;
}

static ret_codes atangent() {
  // Make sure there are at least 1 elements on the stack
  if (stack_size() >= 1) {
    float num = pop();
    if (s.rad_mode) {
      add_to_stack(tan(num));
    }
    else {
      add_to_stack(atan(num)*180.0/pi);
    }
    return SUCCESS;
  }
  return FAILED_OPERATION;
}

// --- CALUCLATOR SETTINGS ---

// Change to radians mode
static ret_codes rad() {
  s.rad_mode=1;
  return SUCCESS;
}

// Change to degrees mode
static ret_codes deg() {
  s.rad_mode=0;
  return SUCCESS;
}

// --- CONSTANTS ---

static ret_codes my_pi() {
  add_to_stack(pi);
  return SUCCESS;
}

static ret_codes my_e() {
  add_to_stack(e);
  return SUCCESS;
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
    {"neg"  , neg       } ,
    {"*"    , multiply  } ,
    {"/"    , divide    } ,
    {"pow"  , my_pow    } ,
    {"**"   , my_pow    } ,
    {"**2"  , squared   } ,
    {"**3"  , cubed     } ,
    {"sqrt" , my_sqrt   } ,
    {"//2"  , my_sqrt   } ,
    {"cbrt" , my_cbrt   } ,
    {"//3"  , my_cbrt   } ,
    {"xrt"  , xrt       } ,
    {"//"   , xrt       } ,
    {"abs"  , my_abs    } ,
    {"inv"  , inv       } ,
    {"1/x"  , inv       } ,
    {"sin"  , sine      } ,
    {"cos"  , cosine    } ,
    {"tan"  , tangent   } ,
    {"asin" , asine     } ,
    {"acos" , acosine   } ,
    {"atan" , atangent  } ,

    // Calculator Settings
    {"deg"  , deg       } ,
    {"rad"  , rad       } ,

    // Constants
    {"pi"  , my_pi     } ,
    {"e"   , my_e      } ,
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
