#include "stack.h"
#include "bool.h"
#include "ctrl_codes.h"
#include "operations.h"
#include "factorial.h"
#include "fibonacci.h"
#include "kbhit.h"

#include <assert.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef TEST
static ret_codes rpn_calc_help();
#endif // TEST
// --- STACK MANIPULATION FUNCTIONS ---

// Blank entry duplicates the last item on the stack
static ret_codes rpn_calc_duplicate() {
  // Make sure there are at least 1 elements on the stack
  if (get_stack_size() >= 1) {
    long double num1 = pop();
    push(num1);
    push(num1);
    return SUCCESSFUL_OPERATION;
  }
  printf("ERROR: Not enough elements on the stack to perform \"Duplicate\"\n");
  return FAILED_OPERATION;
}

// Removes the last entry on the stack
static ret_codes rpn_calc_drop() {
  // Make sure there are at least 1 elements on the stack
  if (get_stack_size() >= 1) {
    pop();
    return SUCCESSFUL_OPERATION;
  }
  return FAILED_OPERATION;
}

// Swap the order of the last two stack entries
static ret_codes rpn_calc_swap() {
  // Make sure there are at least 2 elements on the stack
  if (get_stack_size() >= 2) {
    long double num2 = pop();
    long double num1 = pop();
    push(num2);
    push(num1);
    return SUCCESSFUL_OPERATION;
  }
  printf("ERROR: Not enough elements on the stack to perform \"Swap\"\n");
  return FAILED_OPERATION;
}

// Clear the WHOLE STACK
static ret_codes rpn_calc_clear() {
  set_stack_size(0);
  return SUCCESSFUL_OPERATION;
}

// --- MATHEMATICAL OPERATORS ---

// Adds the last two stack entries together
static ret_codes rpn_calc_plus() {
  // Make sure there are at least 2 elements on the stack
  if (get_stack_size() >= 2) {
    long double num2 = pop();
    long double num1 = pop();
    push(num1+num2);
    return SUCCESSFUL_OPERATION;
  }
  printf("ERROR: Not enough elements on the stack to perform \"+\"\n");
  return FAILED_OPERATION;
}

// Subtracts the last two stack entries together
static ret_codes rpn_calc_minus() {
  // Make sure there are at least 2 elements on the stack
  if (get_stack_size() >= 2) {
    long double num2 = pop();
    long double num1 = pop();
    push(num1-num2);
    return SUCCESSFUL_OPERATION;
  }
  printf("ERROR: Not enough elements on the stack for this Operation\n");
  return FAILED_OPERATION;
}

// Change the sign on the number
static ret_codes rpn_calc_neg() {
  // Make sure there are at least 1 elements on the stack
  if (get_stack_size() >= 1) {
    long double num = pop();
    push(num*-1);
    return SUCCESSFUL_OPERATION;
  }
  printf("ERROR: Not enough elements on the stack for this Operation\n");
  return FAILED_OPERATION;
}

// Multiplies the last two stack entries together
static ret_codes rpn_calc_multiply() {
  // Make sure there are at least 2 elements on the stack
  if (get_stack_size() >= 2) {
    long double num2 = pop();
    long double num1 = pop();
    push(num1*num2);
    return SUCCESSFUL_OPERATION;
  }
  printf("ERROR: Not enough elements on the stack for this Operation\n");
  return FAILED_OPERATION;
}

// Divides the last two stack entries together
static ret_codes rpn_calc_divide() {
  // Make sure there are at least 2 elements on the stack
  if (get_stack_size() >= 2) {
    long double num2 = pop();
    long double num1 = pop();
    push(num1/num2);
    return SUCCESSFUL_OPERATION;
  }
  printf("ERROR: Not enough elements on the stack for this Operation\n");
  return FAILED_OPERATION;
}

// x to the power of y
static ret_codes rpn_calc_pow() {
  // Make sure there are at least 2 elements on the stack
  if (get_stack_size() >= 2) {
    long double num2 = pop();
    long double num1 = pop();
    push(pow(num1, num2));
    return SUCCESSFUL_OPERATION;
  }
  printf("ERROR: Not enough elements on the stack for this Operation\n");
  return FAILED_OPERATION;
}

// squared
static ret_codes rpn_calc_squared() {
  // Make sure there are at least 1 elements on the stack
  if (get_stack_size() >= 1) {
    long double num = pop();
    push(pow(num, 2));
    return SUCCESSFUL_OPERATION;
  }
  printf("ERROR: Not enough elements on the stack for this Operation\n");
  return FAILED_OPERATION;
}

// cubed
static ret_codes rpn_calc_cubed() {
  // Make sure there are at least 1 elements on the stack
  if (get_stack_size() >= 1) {
    long double num = pop();
    push(pow(num, 3));
    return SUCCESSFUL_OPERATION;
  }
  printf("ERROR: Not enough elements on the stack for this Operation\n");
  return FAILED_OPERATION;
}

// Square Roots the last stack entry
static ret_codes rpn_calc_sqrt() {
  // Make sure there are at least 1 elements on the stack
  if (get_stack_size() >= 1) {
    long double num = pop();
    push(sqrt(num));
    return SUCCESSFUL_OPERATION;
  }
  printf("ERROR: Not enough elements on the stack for this Operation\n");
  return FAILED_OPERATION;
}

// Cube Roots the last stack entry
static ret_codes rpn_calc_cbrt() {
  // Make sure there are at least 1 elements on the stack
  if (get_stack_size() >= 1) {
    long double num = pop();
    push(cbrt(num));
    return SUCCESSFUL_OPERATION;
  }
  printf("ERROR: Not enough elements on the stack for this Operation\n");
  return FAILED_OPERATION;
}

// xth Root the last stack entry
static ret_codes rpn_calc_xrt() {
  // Make sure there are at least 2 elements on the stack
  if (get_stack_size() >= 2) {
    long double num2 = pop();
    long double num1 = pop();
    push(pow(num1, 1.0/num2));
    return SUCCESSFUL_OPERATION;
  }
  printf("ERROR: Not enough elements on the stack for this Operation\n");
  return FAILED_OPERATION;
}

// invert the value
static ret_codes rpn_calc_inv() {
  // Make sure there are at least 1 elements on the stack
  if (get_stack_size() >= 1) {
    long double num = pop();
    push(1.0/num);
    return SUCCESSFUL_OPERATION;
  }
  printf("ERROR: Not enough elements on the stack for this Operation\n");
  return FAILED_OPERATION;
}

static ret_codes rpn_calc_sin() {
  // Make sure there are at least 1 elements on the stack
  if (get_stack_size() >= 1) {
    long double num = pop();
    if (get_angle_mode() == RADIANS) {
      push(sin(num));
    }
    else {
      push(sin(num*M_PI/180.0));
    }
    return SUCCESSFUL_OPERATION;
  }
  printf("ERROR: Not enough elements on the stack for this Operation\n");
  return FAILED_OPERATION;
}

static ret_codes rpn_calc_cos() {
  // Make sure there are at least 1 elements on the stack
  if (get_stack_size() >= 1) {
    long double num = pop();
    if (get_angle_mode() == RADIANS) {
      push(cos(num));
    }
    else {
      push(cos(num*M_PI/180.0));
    }
    return SUCCESSFUL_OPERATION;
  }
  printf("ERROR: Not enough elements on the stack for this Operation\n");
  return FAILED_OPERATION;
}

static ret_codes rpn_calc_tan() {
  // Make sure there are at least 1 elements on the stack
  if (get_stack_size() >= 1) {
    long double num = pop();
    if (get_angle_mode() == RADIANS) {
      push(tan(num));
    }
    else {
      push(tan(num*M_PI/180.0));
    }
    return SUCCESSFUL_OPERATION;
  }
  printf("ERROR: Not enough elements on the stack for this Operation\n");
  return FAILED_OPERATION;
}

static ret_codes rpn_calc_asin() {
  // Make sure there are at least 1 elements on the stack
  if (get_stack_size() >= 1) {
    long double num = pop();
    if (get_angle_mode() == RADIANS) {
      push(asin(num));
    }
    else {
      push(asin(num)*180.0/M_PI);
    }
    return SUCCESSFUL_OPERATION;
  }
  printf("ERROR: Not enough elements on the stack for this Operation\n");
  return FAILED_OPERATION;
}

static ret_codes rpn_calc_acos() {
  // Make sure there are at least 1 elements on the stack
  if (get_stack_size() >= 1) {
    long double num = pop();
    if (get_angle_mode() == RADIANS) {
      push(cos(num));
    }
    else {
      push(acos(num)*180.0/M_PI);
    }
    return SUCCESSFUL_OPERATION;
  }
  printf("ERROR: Not enough elements on the stack for this Operation\n");
  return FAILED_OPERATION;
}

static ret_codes rpn_calc_atan() {
  // Make sure there are at least 1 elements on the stack
  if (get_stack_size() >= 1) {
    long double num = pop();
    if (get_angle_mode() == RADIANS) {
      push(tan(num));
    }
    else {
      push(atan(num)*180.0/M_PI);
    }
    return SUCCESSFUL_OPERATION;
  }
  printf("ERROR: Not enough elements on the stack for this Operation\n");
  return FAILED_OPERATION;
}

// base 10 logarithms
static ret_codes rpn_calc_log() {
  // Make sure there are at least 1 elements on the stack
  if (get_stack_size() >= 1) {
    long double num = pop();
    // log is the natural log normally, so I need to convert it to base 10
    push(log(num)/log(10));
    return SUCCESSFUL_OPERATION;
  }
  printf("ERROR: Not enough elements on the stack for this Operation\n");
  return FAILED_OPERATION;
}

// Base e logarithms
static ret_codes rpn_calc_ln() {
  // Make sure there are at least 1 elements on the stack
  if (get_stack_size() >= 1) {
    long double num = pop();
    push(log(num));
    return SUCCESSFUL_OPERATION;
  }
  printf("ERROR: Not enough elements on the stack for this Operation\n");
  return FAILED_OPERATION;
}

// Variable Base logarithms
static ret_codes rpn_calc_logx() {
  // Make sure there are at least 2 elements on the stack
  if (get_stack_size() >= 2) {
    long double num = pop();
    long double base = pop();
    push(log(num)/log(base));
    return SUCCESSFUL_OPERATION;
  }
  printf("ERROR: Not enough elements on the stack for this Operation\n");
  return FAILED_OPERATION;
}

// e to the power of x
static ret_codes rpn_calc_exp() {
  // Make sure there are at least 1 elements on the stack
  if (get_stack_size() >= 1) {
    long double num = pop();
    push(exp(num));
    return SUCCESSFUL_OPERATION;
  }
  printf("ERROR: Not enough elements on the stack for this Operation\n");
  return FAILED_OPERATION;
}

// finds the sum of the numbers on the stack from stack position x to stack
// position y
static ret_codes rpn_calc_sumstack() {
  // Make sure there are at least 2 elements on the stack
  if (get_stack_size() >= 2) {
    long double y = pop();
    long double x = pop();
    ret_codes ret = SUCCESSFUL_OPERATION;

    if (y < 1 || y > get_stack_size()) {
      printf("ERROR: Second Argument was not in the stack\n");
      ret = FAILED_OPERATION;
    }
    if (x < 1 || x > get_stack_size()) {
      printf("ERROR: First Argument was not in the stack\n");
      ret = FAILED_OPERATION;
    }

    if (ret != SUCCESSFUL_OPERATION) {
      return ret;
    }

    int min, max;
    long double sum = 0;
    if (x <= y) {
      min = x;
      max = y;
    }
    else {
      min = y;
      max = x;
    }
    // decrement to make it an index
    min--;
    for (int i = min; i < max; i++) {
      sum += get_stack_value_at_index(i);
    }

    // now remove all the stack elements that were used in the addition.
    for (int i = min; i < max; i++) {
      remove_from_stack_index(min);
    }

    push(sum);
    return SUCCESSFUL_OPERATION;
  }
  printf("ERROR: Not enough elements on the stack for this Operation\n");
  return FAILED_OPERATION;
}

// Finds the sum of all the numbers between x and y.
// ex: if x = 5 and y = 7, sum = 5+6+7 = 18
static ret_codes rpn_calc_sum() {
  // Make sure there are at least 2 elements on the stack
  if (get_stack_size() >= 2) {
    long double y = pop();
    long double x = pop();

    int min, max;
    long double sum = 0;
    if (x <= y) {
      min = x;
      max = y;
    }
    else {
      min = y;
      max = x;
    }
    for (int i = min; i <= max; i++) {
      sum += i;
    }
    push(sum);
    return SUCCESSFUL_OPERATION;
  }
  printf("ERROR: Not enough elements on the stack for this Operation\n");
  return FAILED_OPERATION;
}

// finds the avg of the numbers on the stack from stack position x to stack
// position y
static ret_codes rpn_calc_avgstack() {
  // Make sure there are at least 2 elements on the stack
  if (get_stack_size() >= 2) {
    long double y = pop();
    long double x = pop();
    ret_codes ret = SUCCESSFUL_OPERATION;

    if (y < 1 || y > get_stack_size()) {
      printf("ERROR: Second Argument was not in the stack\n");
      ret = FAILED_OPERATION;
    }
    if (x < 1 || x > get_stack_size()) {
      printf("ERROR: First Argument was not in the stack\n");
      ret = FAILED_OPERATION;
    }

    if (ret != SUCCESSFUL_OPERATION) {
      return ret;
    }

    int min, max;
    long double sum = 0;
    if (x <= y) {
      min = x;
      max = y;
    }
    else {
      min = y;
      max = x;
    }
    // decrement to make it an index
    min--;
    for (int i = min; i < max; i++) {
      sum += get_stack_value_at_index(i);
    }

    // now remove all the stack elements that were used in the addition.
    for (int i = min; i < max; i++) {
      remove_from_stack_index(min);
    }

    push(sum/(max-min));
    return SUCCESSFUL_OPERATION;
  }
  printf("ERROR: Not enough elements on the stack for this Operation\n");
  return FAILED_OPERATION;
}

static ret_codes rpn_calc_factorial() {
  // Make sure there are at least 1 elements on the stack
  if (get_stack_size() >= 1) {
    long double x = pop();
    long double ans = factorial(x);

    if (ans == -1) {
      printf("ERROR: Factorial is only accurate up to %d!\n",
              MAX_FACTORIAL_INPUT-1);
      push(x);
      return FAILED_OPERATION;
    }
    push(ans);
    return SUCCESSFUL_OPERATION;
  }
  printf("ERROR: Not enough elements on the stack for this Operation\n");
  return FAILED_OPERATION;
}

static ret_codes rpn_calc_fibonacci() {
  // Make sure there are at least 1 elements on the stack
  if (get_stack_size() >= 1) {
    long double x = pop();
    long double ans = fibonacci(x);

    if (ans == -1) {
      printf("ERROR: Fibonacci is only accurate up to %d!\n",
              MAX_FIBONACCI_INPUT-1);
      push(x);
      return FAILED_OPERATION;
    }
    push(ans);
    return SUCCESSFUL_OPERATION;
  }
  printf("ERROR: Not enough elements on the stack for this Operation\n");
  return FAILED_OPERATION;
}

static int random_helper() {
  static bool already_seeded = false;
  if (!already_seeded) {
    srand(time(NULL));
    already_seeded = true;
  }
  return rand();
}

// Generate a random number between 0 and 1
static ret_codes rpn_calc_rand() {
  push((long double)random_helper() / RAND_MAX);
  return SUCCESSFUL_OPERATION;
}

// Generate a random number between min and max inclusive
static ret_codes rpn_calc_randx() {
  // Make sure there are at least 2 elements on the stack
  if (get_stack_size() >= 2) {
    int max = (int)pop();
    int min = (int)pop();
    push((long double)(random_helper() % (max-min+1) + min));
    return SUCCESSFUL_OPERATION;
  }
  printf("ERROR: Not enough elements on the stack for this Operation\n");
  return FAILED_OPERATION;
}

// Check to see if the value lowest on the stack is prime
static ret_codes rpn_calc_is_prime() {
  // Make sure there is at least 1 element on the stack
  if (get_stack_size() >= 1) {
    long double x = pop();
    int x_int = (int)x;

    // If the input is not an integer, then we can't check if it is prime
    if (x_int != x) {
        push(x);
        printf("ERROR: Can't check if a non integer is prime\n");
        return FAILED_OPERATION;
    }

    // If the number is negative, 0, or 1 it isn't prime
    if (x_int < 2) {
        push(0);
        return SUCCESSFUL_OPERATION;
    }
    for (unsigned int i = 2; i < sqrt(x_int); i++) {
      if (x_int % i == 0) {
        push(0);
        return SUCCESSFUL_OPERATION;
      }
    }
    push(1);
    return SUCCESSFUL_OPERATION;
  }
  printf("ERROR: Not enough elements on the stack for this Operation\n");
  return FAILED_OPERATION;
}

// --- BITWISE OPERATIONS ---

static ret_codes rpn_calc_bit_and() {
  // Make sure there are at least 2 elements on the stack
  if (get_stack_size() >= 2) {
    long double num2 = pop();
    long double num1 = pop();
    push((int)num1 & (int)num2);
    return SUCCESSFUL_OPERATION;
  }
  printf("ERROR: Not enough elements on the stack for this Operation\n");
  return FAILED_OPERATION;
}

static ret_codes rpn_calc_bit_or() {
  // Make sure there are at least 2 elements on the stack
  if (get_stack_size() >= 2) {
    long double num2 = pop();
    long double num1 = pop();
    push((int)num1 | (int)num2);
    return SUCCESSFUL_OPERATION;
  }
  printf("ERROR: Not enough elements on the stack for this Operation\n");
  return FAILED_OPERATION;
}

static ret_codes rpn_calc_bit_xor() {
  // Make sure there are at least 2 elements on the stack
  if (get_stack_size() >= 2) {
    long double num2 = pop();
    long double num1 = pop();
    push((int)num1 ^ (int)num2);
    return SUCCESSFUL_OPERATION;
  }
  printf("ERROR: Not enough elements on the stack for this Operation\n");
  return FAILED_OPERATION;
}

static ret_codes rpn_calc_bit_left_shift() {
  // Make sure there are at least 2 elements on the stack
  if (get_stack_size() >= 2) {
    long double num2 = pop();
    long double num1 = pop();
    push((int)num1 << (int)num2);
    return SUCCESSFUL_OPERATION;
  }
  printf("ERROR: Not enough elements on the stack for this Operation\n");
  return FAILED_OPERATION;
}

static ret_codes rpn_calc_bit_right_shift() {
  // Make sure there are at least 2 elements on the stack
  if (get_stack_size() >= 2) {
    long double num2 = pop();
    long double num1 = pop();
    push((int)num1 >> (int)num2);
    return SUCCESSFUL_OPERATION;
  }
  printf("ERROR: Not enough elements on the stack for this Operation\n");
  return FAILED_OPERATION;
}

// --- CALCULATOR SETTINGS ---

// Change to radians mode
static ret_codes rpn_calc_rad() {
  set_angle_mode(RADIANS);
  return SUCCESSFUL_OPERATION;
}

// Change to degrees mode
static ret_codes rpn_calc_deg() {
  set_angle_mode(DEGREES);
  return SUCCESSFUL_OPERATION;
}

// Change to degrees mode
static ret_codes rpn_calc_hex() {
  set_base_mode(HEXADECIMAL);
  return SUCCESSFUL_OPERATION;
}

// Change to degrees mode
static ret_codes rpn_calc_dec() {
  set_base_mode(DECIMAL);
  return SUCCESSFUL_OPERATION;
}

// Change to degrees mode
static ret_codes rpn_calc_oct() {
  set_base_mode(OCTAL);
  return SUCCESSFUL_OPERATION;
}

// Change to degrees mode
static ret_codes rpn_calc_bin() {
  set_base_mode(BINARY);
  return SUCCESSFUL_OPERATION;
}

// --- CONSTANTS ---

static ret_codes rpn_calc_pi() {
  push(M_PI);
  return SUCCESSFUL_OPERATION;
}

static ret_codes rpn_calc_e() {
  push(M_E);
  return SUCCESSFUL_OPERATION;
}

// -----------------------------------------------------------------------------

// Here I am mapping the user input string associated with an operation to the
// operations function name. In this way, I can accept the user input and
// directly map it to a function to execute using a function pointer. Makes it
// less for me to do in order to add more operations later.
struct operation_map {
  const char name;
  ret_codes (*func)(void);
  char description[40];

};

const static struct operation_map calc_single_char_operations [] = {
  // Stack Manipulations
    {'\n'    , rpn_calc_duplicate        , "<enter> : Duplicate Last Stack Entry"     } ,
    {'d'     , rpn_calc_drop             , "d       : Delete Last Stack Entry"        } ,
    {'s'     , rpn_calc_swap             , "s       : Swap Last 2 Stack Entries"      } ,
    {ESCAPE  , rpn_calc_clear            , "<esc>   : Clear Stack"                    } ,
#ifndef TEST
    {'?'     , rpn_calc_help             , "?       : Show Help"                      } ,
#endif // TEST

  // Math Operations
    {'+'     , rpn_calc_plus             , "+       : Plus"                           } ,
    {'-'     , rpn_calc_minus            , "-       : Minus"                          } ,
    {'*'     , rpn_calc_multiply         , "*       : Multiply"                       } ,
    {'/'     , rpn_calc_divide           , "/       : Divide"                         } ,
    {'n'     , rpn_calc_neg              , "n       : Change Sign (+/-)"              } ,
    {'i'     , rpn_calc_inv              , "i       : 1/x"                            } ,
    {'!'     , rpn_calc_factorial        , "!       : Factorial of last Stack Entry"  } ,

    // Bitwise Operations
    {'&'     , rpn_calc_bit_and          , "&       : Bitwise AND"                    } ,
    {'|'     , rpn_calc_bit_or           , "|       : Bitwise OR"                     } ,
    {'^'     , rpn_calc_bit_xor          , "^       : Bitwise XOR"                    } ,
    {'<'     , rpn_calc_bit_left_shift   , "<       : Left Shift x entry y bits"      } ,
    {'>'     , rpn_calc_bit_right_shift  , ">       : Right Shift x entry y bits"     } ,

    // Calculator Settings
    {CTRL_E  , rpn_calc_deg              , "ctrl+e  : Change Angle to Degrees"        } ,
    {CTRL_R  , rpn_calc_rad              , "ctrl+r  : Change Angle to Radians"        } ,
    {CTRL_H  , rpn_calc_hex              , "ctrl+h  : Change numeric base to HEX"     } ,
    {CTRL_D  , rpn_calc_dec              , "ctrl+d  : Change numeric base to DEC"     } ,
    {CTRL_O  , rpn_calc_oct              , "ctrl+o  : Change numeric base to OCT"     } ,
    {CTRL_B  , rpn_calc_bin              , "ctrl+b  : Change numeric base to BIN"     } ,
  };


// ****** BEGINNING OF MULTI-CHAR OPERATIONS ******

// These are ALL of the trig functions available in the calculator.
static struct operation_map calc_trig_operations [] = {
    {'C' , rpn_calc_acos , "acos" } ,
    {'S' , rpn_calc_asin , "asin" } ,
    {'T' , rpn_calc_atan , "atan" } ,
    {'c' , rpn_calc_cos  , "cos"  } ,
    {'s' , rpn_calc_sin  , "sin"  } ,
    {'t' , rpn_calc_tan  , "tan"  } ,
  };

// These are ALL of the exponent related operations available in the calculator.
static struct operation_map calc_exponent_operations [] = {
    {'2' , rpn_calc_squared , "x Squared"           } ,
    {'3' , rpn_calc_cubed   , "x Cubed"             } ,
    {'e' , rpn_calc_exp     , "e to the power of x" } ,
    {'p' , rpn_calc_pow     , "x to the power of y" } ,
  };

// These are ALL of the radical related operations available in the calculator.
static struct operation_map calc_radical_operations [] = {
    {'2' , rpn_calc_sqrt    , "square root"         } ,
    {'3' , rpn_calc_cbrt    , "cube root"           } ,
    {'r' , rpn_calc_xrt     , "xth root"            } ,
  };

// These are ALL of the radical related operations available in the calculator.
static struct operation_map calc_logarithm_operations [] = {
    {'e' , rpn_calc_ln    , "log_e of x"  } ,
    {'l' , rpn_calc_log   , "log_10 of x" } ,
    {'x' , rpn_calc_logx  , "log_x of y"  } ,
  };

// These are ALL of the radical related operations available in the calculator.
static struct operation_map calc_complex_operations [] = {
    {'S' , rpn_calc_sum       , "Sum from x to y"              } ,
    {'a' , rpn_calc_avgstack  , "Avg of stack entries x to y"  } ,
    {'f' , rpn_calc_fibonacci , "Returns the xth Fibonacci"    } ,
    {'p' , rpn_calc_is_prime  , "Checks if x is a prime number"} ,
    {'s' , rpn_calc_sumstack  , "Sum of stack entries x to y"  } ,
  };


// These are ALL of the random related operations available in the calculator.
static struct operation_map calc_random_operations [] = {
    {'r' , rpn_calc_rand  , "Random number between 0 and 1"  } ,
    {'x' , rpn_calc_randx , "Random integer between x and y" } ,
  };

// These are ALL of the trig functions available in the calculator.
static struct operation_map calc_constants [] = {
    // Constants
    {'e' , rpn_calc_e  ,"e" } ,
    {'p' , rpn_calc_pi ,"π" } ,
  };

const static struct {
  const char name;
  struct operation_map *map;
  int size;
  char description[30];

} calc_operation_types [] = {
  {'C'  , calc_complex_operations    , (int)sizeof(calc_complex_operations)   , "Complex Operations"        } ,
  {'E'  , calc_exponent_operations   , (int)sizeof(calc_exponent_operations)  , "Exponent Operations"       } ,
  {'L'  , calc_logarithm_operations  , (int)sizeof(calc_logarithm_operations) , "Logarithm Operations"      } ,
  {'R'  , calc_radical_operations    , (int)sizeof(calc_radical_operations)   , "Radical Operations"        } ,
  {'T'  , calc_trig_operations       , (int)sizeof(calc_trig_operations)      , "Trigonometric Operations"  } ,
  {'c'  , calc_constants             , (int)sizeof(calc_constants)            , "Constants"                 } ,
  {'r'  , calc_random_operations     , (int)sizeof(calc_random_operations)    , "Random Operations"         } ,
};

// ****** END OF MULTI-CHAR OPERATIONS ******

#ifndef TEST
ret_codes help() {
  int num_iterations = sizeof(calc_single_char_operations)/
                       sizeof(calc_single_char_operations[0]);

  for (int i = 0; i < num_iterations; i++) {
    printf("%s\n", calc_single_char_operations[i].description);
  }
  printf("\n");

  num_iterations = sizeof(calc_operation_types)/
                   sizeof(calc_operation_types[0]);

  for (int i = 0; i < num_iterations; i++) {
    printf("\n%c: ", calc_operation_types[i].name);
    printf("%s", calc_operation_types[i].description);
  }
  printf("\n");

  return SUCCESSFUL_OPERATION;
}

static ret_codes rpn_calc_help() {
  ret_codes ret = help();

  // Wait for a character to continue
  getCharacter();

  return ret;
}

static void print_operation_type_key(int op_type) {
  int type_size             = calc_operation_types[op_type].size;
  struct operation_map *map = calc_operation_types[op_type].map;
  int num_of_operations     = type_size/sizeof(map[0]);

  for (int i = 0; i < num_of_operations; i++) {
    printf("\n%c: ", calc_operation_types[op_type].map[i].name);
    printf("%s", calc_operation_types[op_type].map[i].description);
  }
  printf("\n");
}
#endif // TEST

static int find_single_char_operation(char op) {
  int num_of_operations = sizeof(calc_single_char_operations)/
                          sizeof(calc_single_char_operations[0]);

  for (int i = 0; i < num_of_operations; i++) {
    if (op == calc_single_char_operations[i].name &&
        calc_single_char_operations[i].func) {
      return i;
    }
  }
  return -1;
}

static int find_out_what_type_of_operation(char op) {
  int num_of_operation_types = sizeof(calc_operation_types)/
                               sizeof(calc_operation_types[0]);
  for (int i = 0; i < num_of_operation_types; i++) {
    if (op == calc_operation_types[i].name) {
      return i;
    }
  }
  return -1;
}

static int find_multi_char_operation(char op, int op_type) {
  int type_size             = calc_operation_types[op_type].size;
  struct operation_map *map = calc_operation_types[op_type].map;
  int num_of_operations     = type_size/sizeof(map[0]);
  for (int j = 0; j < num_of_operations; j++) {
    if (op == map[j].name && map[j].func) {
      return j;
    }
  }
  return -1;
}

// This is called from stack.c when we are trying to find out if the user input
// is an operation. This functions is what determines if it is an operation or
// not. If it is, it returns the index of the operation from the operation
// mapping above, and the operation type. If the type is just a single char
// operation, it returns -1 for that part of the struct, and if the operation
// can't be found, the second part of the struct is also -1.
operation_location whichOperation(char *op_string) {
  operation_location ret;

  char op = op_string[0];

  // Find out what type of operation this is. ie. Trig etc
  int op_type = find_out_what_type_of_operation(op);
  // Set the return code for the operation type
  ret.operation_type_index=op_type;

  // If we found a type, then continue, otherwise if it returned -1 go find a
  // single char operator with that command
  if (op_type != -1) {
    // Print a small help guide for the operation type
#ifndef TEST
    print_operation_type_key(op_type);

    // Since we are doing a multi character command, we need to look for the
    // second command.
    op = getCharacter();
#else
    op = op_string[1];
#endif // TEST

    // Find out if that last command corresponds to anything in the operation
    // type that was selected. If it failed, it returns a -1.
    ret.operation_index = find_multi_char_operation(op, op_type);
  }
  else {
    // If we didn't find a multi-char operation above, then resort to this.
    ret.operation_index = find_single_char_operation(op);
  }
  return ret;
}

// Execute the operation function defined by the index input "op"
ret_codes performOperation(operation_location op) {
  // We should NEVER be calling this if an operation could not be found
  assert(op.operation_index != -1);

  need_to_pop   = false;
  int op_type   = op.operation_type_index;
  int operation = op.operation_index;

  // If we didn't find a type then it is a single character command.
  if (op_type == -1) {
    return calc_single_char_operations[operation].func();
  }
  return calc_operation_types[op_type].map[operation].func();
}
