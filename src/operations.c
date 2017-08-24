#include "stack.h"
#include "operations.h"
#include <string.h>
#include <math.h>

// --- STACK MANIPULATION FUNCTIONS ---

// Blank entry duplicates the last item on the stack
static ret_codes rpn_calc_duplicate() {
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
static ret_codes rpn_calc_drop() {
  // Make sure there are at least 1 elements on the stack
  if (stack_size() >= 1) {
    pop();
    return SUCCESS;
  }
  return FAILED_OPERATION;
}

// Swap the order of the last two stack entries
static ret_codes rpn_calc_swap() {
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
static ret_codes rpn_calc_plus() {
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
static ret_codes rpn_calc_minus() {
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
static ret_codes rpn_calc_neg() {
  // Make sure there are at least 1 elements on the stack
  if (stack_size() >= 1) {
    float num = pop();
    add_to_stack(num*-1);
    return SUCCESS;
  }
  return FAILED_OPERATION;
}

// Multiplies the last two stack entries together
static ret_codes rpn_calc_multiply() {
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
static ret_codes rpn_calc_divide() {
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
static ret_codes rpn_calc_pow() {
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
static ret_codes rpn_calc_squared() {
  // Make sure there are at least 1 elements on the stack
  if (stack_size() >= 1) {
    float num = pop();
    add_to_stack(pow(num, 2));
    return SUCCESS;
  }
  return FAILED_OPERATION;
}

// cubed
static ret_codes rpn_calc_cubed() {
  // Make sure there are at least 1 elements on the stack
  if (stack_size() >= 1) {
    float num = pop();
    add_to_stack(pow(num, 3));
    return SUCCESS;
  }
  return FAILED_OPERATION;
}

// Square Roots the last stack entry
static ret_codes rpn_calc_sqrt() {
  // Make sure there are at least 1 elements on the stack
  if (stack_size() >= 1) {
    float num = pop();
    add_to_stack(sqrt(num));
    return SUCCESS;
  }
  return FAILED_OPERATION;
}

// Cube Roots the last stack entry
static ret_codes rpn_calc_cbrt() {
  // Make sure there are at least 1 elements on the stack
  if (stack_size() >= 1) {
    float num = pop();
    add_to_stack(cbrt(num));
    return SUCCESS;
  }
  return FAILED_OPERATION;
}

// xth Root the last stack entry
static ret_codes rpn_calc_xrt() {
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
static ret_codes rpn_calc_abs() {
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
static ret_codes rpn_calc_inv() {
  // Make sure there are at least 1 elements on the stack
  if (stack_size() >= 1) {
    float num = pop();
    add_to_stack(1.0/num);
    return SUCCESS;
  }
  return FAILED_OPERATION;
}

static ret_codes rpn_calc_sin() {
  // Make sure there are at least 1 elements on the stack
  if (stack_size() >= 1) {
    float num = pop();
    if (s.angle_mode == RADIANS) {
      add_to_stack(sin(num));
    }
    else {
      add_to_stack(sin(num*M_PI/180.0));
    }
    return SUCCESS;
  }
  return FAILED_OPERATION;
}

static ret_codes rpn_calc_cos() {
  // Make sure there are at least 1 elements on the stack
  if (stack_size() >= 1) {
    float num = pop();
    if (s.angle_mode == RADIANS) {
      add_to_stack(cos(num));
    }
    else {
      add_to_stack(cos(num*M_PI/180.0));
    }
    return SUCCESS;
  }
  return FAILED_OPERATION;
}

static ret_codes rpn_calc_tan() {
  // Make sure there are at least 1 elements on the stack
  if (stack_size() >= 1) {
    float num = pop();
    if (s.angle_mode == RADIANS) {
      add_to_stack(tan(num));
    }
    else {
      add_to_stack(tan(num*M_PI/180.0));
    }
    return SUCCESS;
  }
  return FAILED_OPERATION;
}

static ret_codes rpn_calc_asin() {
  // Make sure there are at least 1 elements on the stack
  if (stack_size() >= 1) {
    float num = pop();
    if (s.angle_mode == RADIANS) {
      add_to_stack(asin(num));
    }
    else {
      add_to_stack(asin(num)*180.0/M_PI);
    }
    return SUCCESS;
  }
  return FAILED_OPERATION;
}

static ret_codes rpn_calc_acos() {
  // Make sure there are at least 1 elements on the stack
  if (stack_size() >= 1) {
    float num = pop();
    if (s.angle_mode == RADIANS) {
      add_to_stack(cos(num));
    }
    else {
      add_to_stack(acos(num)*180.0/M_PI);
    }
    return SUCCESS;
  }
  return FAILED_OPERATION;
}

static ret_codes rpn_calc_atan() {
  // Make sure there are at least 1 elements on the stack
  if (stack_size() >= 1) {
    float num = pop();
    if (s.angle_mode == RADIANS) {
      add_to_stack(tan(num));
    }
    else {
      add_to_stack(atan(num)*180.0/M_PI);
    }
    return SUCCESS;
  }
  return FAILED_OPERATION;
}

// --- BITWISE OPERATIONS ---

static ret_codes rpn_calc_bit_and() {
  // Make sure there are at least 2 elements on the stack
  if (stack_size() >= 2) {
    float num2 = pop();
    float num1 = pop();
    add_to_stack((int)num1 & (int)num2);
    return SUCCESS;
  }
  return FAILED_OPERATION;
}

static ret_codes rpn_calc_bit_or() {
  // Make sure there are at least 2 elements on the stack
  if (stack_size() >= 2) {
    float num2 = pop();
    float num1 = pop();
    add_to_stack((int)num1 | (int)num2);
    return SUCCESS;
  }
  return FAILED_OPERATION;
}

static ret_codes rpn_calc_bit_xor() {
  // Make sure there are at least 2 elements on the stack
  if (stack_size() >= 2) {
    float num2 = pop();
    float num1 = pop();
    add_to_stack((int)num1 ^ (int)num2);
    return SUCCESS;
  }
  return FAILED_OPERATION;
}

static ret_codes rpn_calc_bit_left_shift() {
  // Make sure there are at least 2 elements on the stack
  if (stack_size() >= 2) {
    float num2 = pop();
    float num1 = pop();
    add_to_stack((int)num1 << (int)num2);
    return SUCCESS;
  }
  return FAILED_OPERATION;
}

static ret_codes rpn_calc_bit_right_shift() {
  // Make sure there are at least 2 elements on the stack
  if (stack_size() >= 2) {
    float num2 = pop();
    float num1 = pop();
    add_to_stack((int)num1 >> (int)num2);
    return SUCCESS;
  }
  return FAILED_OPERATION;
}

static ret_codes rpn_calc_bit_left_shift_1() {
  // Make sure there are at least 1 elements on the stack
  if (stack_size() >= 1) {
    float num = pop();
    add_to_stack((int)num << 1);
    return SUCCESS;
  }
  return FAILED_OPERATION;
}

static ret_codes rpn_calc_bit_right_shift_1() {
  // Make sure there are at least 1 elements on the stack
  if (stack_size() >= 1) {
    float num = pop();
    add_to_stack((int)num >> 1);
    return SUCCESS;
  }
  return FAILED_OPERATION;
}

// --- CALUCLATOR SETTINGS ---

// Change to radians mode
static ret_codes rpn_calc_rad() {
  s.angle_mode=RADIANS;
  return SUCCESS;
}

// Change to degrees mode
static ret_codes rpn_calc_deg() {
  s.angle_mode=DEGREES;
  return SUCCESS;
}

// Change to degrees mode
static ret_codes rpn_calc_hex() {
  s.base_mode=HEXADECIMAL;
  return SUCCESS;
}

// Change to degrees mode
static ret_codes rpn_calc_dec() {
  s.base_mode=DECIMAL;
  return SUCCESS;
}

// Change to degrees mode
static ret_codes rpn_calc_oct() {
  s.base_mode=OCTAL;
  return SUCCESS;
}

// Change to degrees mode
static ret_codes rpn_calc_bin() {
  s.base_mode=BINARY;
  return SUCCESS;
}

// --- CONSTANTS ---

static ret_codes rpn_calc_pi() {
  add_to_stack(M_PI);
  return SUCCESS;
}

static ret_codes rpn_calc_e() {
  add_to_stack(M_E);
  return SUCCESS;
}

// -----------------------------------------------------------------------------

// Here I am mapping the user input string associated with an operation to the
// operations function name. In this way, I can accept the user input and
// directly map it to a funciton to execute using a function pointer. Makes it
// less for me to do in order to add more operations later.
const static struct {
  const char *name;
  ret_codes (*func)(void);

} calc_operations [] = {
  // Stack Manipulations
    {"\n"   , rpn_calc_duplicate          } ,
    {"drop" , rpn_calc_drop               } ,
    {"d"    , rpn_calc_drop               } ,
    {"s"    , rpn_calc_swap               } ,
    {"swap" , rpn_calc_swap               } ,

  // Math Operations
    {"+"    , rpn_calc_plus               } ,
    {"-"    , rpn_calc_minus              } ,
    {"neg"  , rpn_calc_neg                } ,
    {"*"    , rpn_calc_multiply           } ,
    {"/"    , rpn_calc_divide             } ,
    {"pow"  , rpn_calc_pow                } ,
    {"**"   , rpn_calc_pow                } ,
    {"**2"  , rpn_calc_squared            } ,
    {"**3"  , rpn_calc_cubed              } ,
    {"sqrt" , rpn_calc_sqrt               } ,
    {"//2"  , rpn_calc_sqrt               } ,
    {"cbrt" , rpn_calc_cbrt               } ,
    {"//3"  , rpn_calc_cbrt               } ,
    {"xrt"  , rpn_calc_xrt                } ,
    {"//"   , rpn_calc_xrt                } ,
    {"abs"  , rpn_calc_abs                } ,
    {"inv"  , rpn_calc_inv                } ,
    {"1/x"  , rpn_calc_inv                } ,
    {"sin"  , rpn_calc_sin                } ,
    {"cos"  , rpn_calc_cos                } ,
    {"tan"  , rpn_calc_tan                } ,
    {"asin" , rpn_calc_asin               } ,
    {"acos" , rpn_calc_acos               } ,
    {"atan" , rpn_calc_atan               } ,
    /* {"log"  , rpn_calc_log                } , */
    /* {"ln"   , rpn_calc_ln                 } , */
    /* {"logx" , rpn_calc_logx               } , */

    // Bitwise Operations
    {"&"    , rpn_calc_bit_and            } ,
    {"|"    , rpn_calc_bit_or             } ,
    {"^"    , rpn_calc_bit_xor            } ,
    {"<<"   , rpn_calc_bit_left_shift     } ,
    {">>"   , rpn_calc_bit_right_shift    } ,
    {"<<1"  , rpn_calc_bit_left_shift_1   } ,
    {">>1"  , rpn_calc_bit_right_shift_1  } ,

    // Calculator Settings
    {"deg"  , rpn_calc_deg                } ,
    {"rad"  , rpn_calc_rad                } ,
    {"hex"  , rpn_calc_hex                } ,
    {"dec"  , rpn_calc_dec                } ,
    {"oct"  , rpn_calc_oct                } ,
    {"bin"  , rpn_calc_bin                } ,

    // Constants
    {"pi"  , rpn_calc_pi                  } ,
    {"e"   , rpn_calc_e                   } ,
  };

// This is called from stack.c when we are trying to find out if the user input
// is an operation. This functions is what determines if it is an operation or
// not. If it is, it returns the index of the opreation from the operation
// mapping above, otherwise returns -1
int whichOperation(char *s) {
  int num_of_operations = sizeof(calc_operations)/sizeof(calc_operations[0]);

  for (int i = 0; i < num_of_operations; i++) {
    if (!strcmp(s, calc_operations[i].name) && calc_operations[i].func) {
      return i;
    }
  }
  return -1;
}

// Execute the operation function defined by the index input "op"
ret_codes performOperation(int op) {
  return calc_operations[op].func();
}
