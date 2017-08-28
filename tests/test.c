#include <stdio.h>
#include <string.h>

#include "stack.h"
#include "test.h"
#include "operations.h"

#define input_size 128

static long double actual_result() {
  return get_stack_value_at_index(get_stack_size() - 1);
}

// --- STACK MANIPULATION FUNCTIONS ---

static int test_rpn_calc_duplicate() {
  char input[input_size];

  strncpy(input, "5.5", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "\n", input_size);
  processUserInput(input, strlen(input));

  if (get_stack_size() == 2 && actual_result() == 5.5) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_drop() {
  char input[input_size];

  strncpy(input, "1.0", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "2.0", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "drop", input_size);
  processUserInput(input, strlen(input));

  if (get_stack_size() == 1 && actual_result() == 1.0) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_dropx() {
  char input[input_size];

  strncpy(input, "5.0", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "6.0", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "7.0", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "8.0", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "2.0", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "dropx", input_size);
  processUserInput(input, strlen(input));

  if (get_stack_size() == 3 &&
      get_stack_value_at_index(0) == 5.0 &&
      get_stack_value_at_index(1) == 7.0 &&
      get_stack_value_at_index(2) == 8.0) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_swap() {
  char input[input_size];

  strncpy(input, "1.0", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "2.0", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "swap", input_size);
  processUserInput(input, strlen(input));

  if (get_stack_size() == 2 && actual_result() == 1.0) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_clear() {
  char input[input_size];

  strncpy(input, "1.0", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "2.0", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "3.0", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "4.0", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "5.0", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "6.0", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "clear", input_size);
  processUserInput(input, strlen(input));

  if (get_stack_size() == 0) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_clearx() {
  char input[input_size];

  strncpy(input, "1.0", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "2.0", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "9.0", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "4.0", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "5.0", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "6.0", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "2.0", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "clearx", input_size);
  processUserInput(input, strlen(input));

  if (get_stack_size() == 2 && actual_result() == 2.0) {
    return 0;
  }
  return 1;
}

// --- MATHEMATICAL OPERATORS ---

static int test_rpn_calc_plus() {
  char input[input_size];

  strncpy(input, "1.0", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "2.0", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "+", input_size);
  processUserInput(input, strlen(input));

  if (get_stack_size() == 1 && actual_result() == 3.0) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_minus() {
  char input[input_size];

  strncpy(input, "1.0", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "2.0", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "-", input_size);
  processUserInput(input, strlen(input));

  if (get_stack_size() == 1 && actual_result() == -1.0) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_neg() {
  char input[input_size];

  strncpy(input, "1.0", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "2.0", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "neg", input_size);
  processUserInput(input, strlen(input));

  if (get_stack_size() == 2 && actual_result() == -2.0) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_multiply() {
  char input[input_size];

  strncpy(input, "3.0", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "2.0", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "*", input_size);
  processUserInput(input, strlen(input));

  if (get_stack_size() == 1 && actual_result() == 6.0) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_divide() {
  char input[input_size];

  strncpy(input, "1.0", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "2.0", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "/", input_size);
  processUserInput(input, strlen(input));

  if (get_stack_size() == 1 && actual_result() == 0.5) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_pow() {
  char input[input_size];

  strncpy(input, "2.0", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "4.0", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "**", input_size);
  processUserInput(input, strlen(input));

  if (get_stack_size() == 1 && actual_result() == 16.0) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_squared() {
  char input[input_size];

  strncpy(input, "1.0", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "3.0", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "**2", input_size);
  processUserInput(input, strlen(input));

  if (get_stack_size() == 2 && actual_result() == 9.0) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_cubed() {
  char input[input_size];

  strncpy(input, "1.0", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "2.0", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "**3", input_size);
  processUserInput(input, strlen(input));

  if (get_stack_size() == 2 && actual_result() == 8.0) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_sqrt() {
  char input[input_size];

  strncpy(input, "1.0", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "25.0", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "sqrt", input_size);
  processUserInput(input, strlen(input));

  if (get_stack_size() == 2 && actual_result() == 5.0) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_cbrt() {
  char input[input_size];

  strncpy(input, "1.0", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "125.0", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "cbrt", input_size);
  processUserInput(input, strlen(input));

  if (get_stack_size() == 2 && actual_result() == 5.0) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_xrt() {
  char input[input_size];

  strncpy(input, "32.0", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "5.0", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "//", input_size);
  processUserInput(input, strlen(input));

  if (get_stack_size() == 1 && actual_result() == 2.0) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_abs() {
  char input[input_size];

  strncpy(input, "1.0", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "-2.0", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "abs", input_size);
  processUserInput(input, strlen(input));

  if (get_stack_size() == 2 && actual_result() == 2.0) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_inv() {
  char input[input_size];

  strncpy(input, "1.0", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "3.0", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "inv", input_size);
  processUserInput(input, strlen(input));

  if (get_stack_size() == 2 && actual_result() > 0.33332 &&
      actual_result() < 0.33334) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_sin_deg() {
  char input[input_size];

  strncpy(input, "deg", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "30", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "sin", input_size);
  processUserInput(input, strlen(input));

  if (get_stack_size() == 1 && actual_result() > 0.499999 &&
      actual_result() < 0.500001) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_sin_rad() {
  char input[input_size];

  strncpy(input, "rad", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "pi", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "6", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "/", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "sin", input_size);
  processUserInput(input, strlen(input));

  if (get_stack_size() == 1 && actual_result() > 0.499999 &&
      actual_result() < 0.500001) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_cos_deg() {
  char input[input_size];

  strncpy(input, "deg", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "60", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "cos", input_size);
  processUserInput(input, strlen(input));

  if (get_stack_size() == 1 && actual_result() > 0.499999 &&
      actual_result() < 0.500001) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_cos_rad() {
  char input[input_size];

  strncpy(input, "rad", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "pi", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "3", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "/", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "cos", input_size);
  processUserInput(input, strlen(input));

  if (get_stack_size() == 1 && actual_result() > 0.4999 &&
      actual_result() < 0.50001) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_tan_deg() {
  char input[input_size];

  strncpy(input, "deg", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "45", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "tan", input_size);
  processUserInput(input, strlen(input));

  if (get_stack_size() == 1 && actual_result() > 0.999999 &&
      actual_result() < 1.000001) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_tan_rad() {
  char input[input_size];

  strncpy(input, "rad", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "pi", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "4", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "/", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "tan", input_size);
  processUserInput(input, strlen(input));

  if (get_stack_size() == 1 && actual_result() > 0.999999 &&
      actual_result() < 1.000001) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_asin_deg() {
  char input[input_size];

  strncpy(input, "deg", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "0.5", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "asin", input_size);
  processUserInput(input, strlen(input));

  if (get_stack_size() == 1 && actual_result() > 29.999999 &&
      actual_result() < 30.000001) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_asin_rad() {
  char input[input_size];

  strncpy(input, "rad", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "0.5", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "asin", input_size);
  processUserInput(input, strlen(input));

  if (get_stack_size() == 1 && actual_result() > 0.523598
      && actual_result() < 0.523600) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_acos_deg() {
  char input[input_size];

  strncpy(input, "deg", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "0.5", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "acos", input_size);
  processUserInput(input, strlen(input));

  if (get_stack_size() == 1 && actual_result() > 59.999999 &&
      actual_result() < 60.000001) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_acos_rad() {
  char input[input_size];

  strncpy(input, "rad", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "0.5", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "cos", input_size);
  processUserInput(input, strlen(input));

  if (get_stack_size() == 1 && actual_result() > 0.877582 &&
      actual_result() < 0.877584) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_atan_deg() {
  char input[input_size];

  strncpy(input, "deg", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "1.0", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "atan", input_size);
  processUserInput(input, strlen(input));

  if (get_stack_size() == 1 && actual_result() == 45) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_atan_rad() {
  char input[input_size];

  strncpy(input, "rad", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "1.0", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "atan", input_size);
  processUserInput(input, strlen(input));

  if (get_stack_size() == 1 && actual_result() > 1.557407 &&
      actual_result() < 1.557409) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_log() {
  char input[input_size];

  strncpy(input, "100", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "log", input_size);
  processUserInput(input, strlen(input));

  if (get_stack_size() == 1 && actual_result() == 2) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_ln() {
  char input[input_size];

  strncpy(input, "e", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "ln", input_size);
  processUserInput(input, strlen(input));

  if (get_stack_size() == 1 && actual_result() > 0.999999 &&
      actual_result() < 1.000001) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_logx() {
  char input[input_size];

  strncpy(input, "8", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "2", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "logx", input_size);
  processUserInput(input, strlen(input));

  if (get_stack_size() == 1 && actual_result() > 2.999999 &&
      actual_result() < 3.000001) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_exp() {
  char input[input_size];

  strncpy(input, "2", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "exp", input_size);
  processUserInput(input, strlen(input));

  if (get_stack_size() == 1 && actual_result() > 7.389055 &&
      actual_result() < 7.389057) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_sumstack() {
  char input[input_size];

  strncpy(input, "5", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "10", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "7", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "3", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "5", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "2", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "4", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "sumstack", input_size);
  processUserInput(input, strlen(input));


  if (get_stack_size() == 3 && actual_result() == 20.0 &&
      get_stack_value_at_index(0) == 5 && get_stack_value_at_index(1) == 5) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_sum() {
  char input[input_size];

  strncpy(input, "5", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "1", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "100", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "sum", input_size);
  processUserInput(input, strlen(input));

  if (get_stack_size() == 2 && actual_result() == 5050.0) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_avgstack() {
  char input[input_size];

  strncpy(input, "11", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "3", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "3", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "5", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "7", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "4", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "6", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "8", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "93", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "2", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "5", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "7", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "9", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "2", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "12", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "avgstack", input_size);
  processUserInput(input, strlen(input));


  if (get_stack_size() == 3 && get_stack_value_at_index(0) == 11.0 &&
      get_stack_value_at_index(1) == 9 && get_stack_value_at_index(2) == 13) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_factorial() {
  char input[input_size];

  strncpy(input, "7", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "!", input_size);
  processUserInput(input, strlen(input));


  if (get_stack_size() == 1 && actual_result() == 5040) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_fibonacci() {
  char input[input_size];

  strncpy(input, "30", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "fib", input_size);
  processUserInput(input, strlen(input));


  if (get_stack_size() == 1 && actual_result() == 832040) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_rand() {
  char input[input_size];
  int r = 0;

  strncpy(input, "rand", input_size);
  processUserInput(input, strlen(input));

  if (!(get_stack_size() == 1 && actual_result() >= 0 &&
        actual_result() <= 1)) {
    r = 1;
  }

  strncpy(input, "rand", input_size);
  processUserInput(input, strlen(input));

  if (!(get_stack_size() == 2 && actual_result() >= 0 &&
        actual_result() <= 1)) {
    r = 1;
  }

  strncpy(input, "rand", input_size);
  processUserInput(input, strlen(input));

  if (!(get_stack_size() == 3 && actual_result() >= 0 &&
        actual_result() <= 1)) {
    r = 1;
  }

  strncpy(input, "rand", input_size);
  processUserInput(input, strlen(input));

  if (!(get_stack_size() == 4 && actual_result() >= 0 &&
        actual_result() <= 1)) {
    r = 1;
  }
  return r;
}

static int test_rpn_calc_randx() {
  char input[input_size];
  int r = 0;

  strncpy(input, "1", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "10", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "randx", input_size);
  processUserInput(input, strlen(input));

  if (!(get_stack_size() == 1 && actual_result() >= 1 &&
        actual_result() <= 10)) {
    r = 1;
  }

  strncpy(input, "1", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "10", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "randx", input_size);
  processUserInput(input, strlen(input));

  if (!(get_stack_size() == 2 && actual_result() >= 1 &&
        actual_result() <= 10)) {
    r = 1;
  }

  strncpy(input, "1", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "10", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "randx", input_size);
  processUserInput(input, strlen(input));

  if (!(get_stack_size() == 3 && actual_result() >= 1 &&
        actual_result() <= 10)) {
    r = 1;
  }

  strncpy(input, "1", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "10", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "randx", input_size);
  processUserInput(input, strlen(input));

  if (!(get_stack_size() == 4 && actual_result() >= 1 &&
        actual_result() <= 10)) {
    r = 1;
  }

  return r;
}

// --- BITWISE OPERATIONS ---

static int test_rpn_calc_bit_and() {
  char input[input_size];

  strncpy(input, "0b1010", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "0b11", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "&", input_size);
  processUserInput(input, strlen(input));

  if (get_stack_size() == 1 && actual_result() == 2) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_bit_or() {
  char input[input_size];

  strncpy(input, "0b1010", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "0b11", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "|", input_size);
  processUserInput(input, strlen(input));

  if (get_stack_size() == 1 && actual_result() == 11) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_bit_xor() {
  char input[input_size];

  strncpy(input, "0b1010", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "0b11", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "^", input_size);
  processUserInput(input, strlen(input));

  if (get_stack_size() == 1 && actual_result() == 9) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_bit_left_shift() {
  char input[input_size];

  strncpy(input, "0b1010", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "2", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "<<", input_size);
  processUserInput(input, strlen(input));

  if (get_stack_size() == 1 && actual_result() == 40) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_bit_right_shift() {
  char input[input_size];

  strncpy(input, "0b1010", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "3", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, ">>", input_size);
  processUserInput(input, strlen(input));

  if (get_stack_size() == 1 && actual_result() == 1) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_bit_left_shift1() {
  char input[input_size];

  strncpy(input, "0b1010", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "<<1", input_size);
  processUserInput(input, strlen(input));

  if (get_stack_size() == 1 && actual_result() == 20) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_bit_right_shift1() {
  char input[input_size];

  strncpy(input, "0b1010", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, ">>1", input_size);
  processUserInput(input, strlen(input));

  if (get_stack_size() == 1 && actual_result() == 5) {
    return 0;
  }
  return 1;
}

// --- HIGHER LEVEL OPERATIONS ---

static int test_rpn_calc_expr() {
  char input[input_size];

  // 4+(4*(2+6))/2 = 20
  strncpy(input, "expr 2 6 + 4 * 2 / 4 +", input_size);
  processUserInput(input, strlen(input));

  if (get_stack_size() == 1 && actual_result() > 19.999999 &&
      actual_result() < 20.000001) {
    return 0;
  }
  return 1;
}

// LIST OF TESTS
const static struct {
  const char *name;
  int (*func)(void);

} test_functions [] = {
    // --- STACK MANIPULATION FUNCTIONS ---
    {"test_rpn_calc_duplicate"         , test_rpn_calc_duplicate         } ,
    {"test_rpn_calc_drop"              , test_rpn_calc_drop              } ,
    {"test_rpn_calc_dropx"             , test_rpn_calc_dropx             } ,
    {"test_rpn_calc_swap"              , test_rpn_calc_swap              } ,
    {"test_rpn_calc_clear"             , test_rpn_calc_clear             } ,
    {"test_rpn_calc_clearx"            , test_rpn_calc_clearx            } ,

    // --- MATHEMATICAL OPERATORS ---
    {"test_rpn_calc_plus"              , test_rpn_calc_plus              } ,
    {"test_rpn_calc_minus"             , test_rpn_calc_minus             } ,
    {"test_rpn_calc_neg"               , test_rpn_calc_neg               } ,
    {"test_rpn_calc_multiply"          , test_rpn_calc_multiply          } ,
    {"test_rpn_calc_divide"            , test_rpn_calc_divide            } ,
    {"test_rpn_calc_pow"               , test_rpn_calc_pow               } ,
    {"test_rpn_calc_squared"           , test_rpn_calc_squared           } ,
    {"test_rpn_calc_cubed"             , test_rpn_calc_cubed             } ,
    {"test_rpn_calc_sqrt"              , test_rpn_calc_sqrt              } ,
    {"test_rpn_calc_cbrt"              , test_rpn_calc_cbrt              } ,
    {"test_rpn_calc_xrt"               , test_rpn_calc_xrt               } ,
    {"test_rpn_calc_abs"               , test_rpn_calc_abs               } ,
    {"test_rpn_calc_inv"               , test_rpn_calc_inv               } ,
    {"test_rpn_calc_sin_deg"           , test_rpn_calc_sin_deg           } ,
    {"test_rpn_calc_sin_rad"           , test_rpn_calc_sin_rad           } ,
    {"test_rpn_calc_cos_deg"           , test_rpn_calc_cos_deg           } ,
    {"test_rpn_calc_cos_rad"           , test_rpn_calc_cos_rad           } ,
    {"test_rpn_calc_tan_deg"           , test_rpn_calc_tan_deg           } ,
    {"test_rpn_calc_tan_rad"           , test_rpn_calc_tan_rad           } ,
    {"test_rpn_calc_asin_deg"          , test_rpn_calc_asin_deg          } ,
    {"test_rpn_calc_asin_rad"          , test_rpn_calc_asin_rad          } ,
    {"test_rpn_calc_acos_deg"          , test_rpn_calc_acos_deg          } ,
    {"test_rpn_calc_acos_rad"          , test_rpn_calc_acos_rad          } ,
    {"test_rpn_calc_atan_deg"          , test_rpn_calc_atan_deg          } ,
    {"test_rpn_calc_atan_rad"          , test_rpn_calc_atan_rad          } ,
    {"test_rpn_calc_log"               , test_rpn_calc_log               } ,
    {"test_rpn_calc_ln"                , test_rpn_calc_ln                } ,
    {"test_rpn_calc_logx"              , test_rpn_calc_logx              } ,
    {"test_rpn_calc_exp"               , test_rpn_calc_exp               } ,
    {"test_rpn_calc_sumstack"          , test_rpn_calc_sumstack          } ,
    {"test_rpn_calc_sum"               , test_rpn_calc_sum               } ,
    {"test_rpn_calc_avgstack"          , test_rpn_calc_avgstack          } ,
    {"test_rpn_calc_factorial"         , test_rpn_calc_factorial         } ,
    {"test_rpn_calc_fibonacci"         , test_rpn_calc_fibonacci         } ,
    {"test_rpn_calc_rand"              , test_rpn_calc_rand              } ,
    {"test_rpn_calc_randx"             , test_rpn_calc_randx             } ,

    // --- BITWISE OPERATIONS ---
    {"test_rpn_calc_bit_and"           , test_rpn_calc_bit_and           } ,
    {"test_rpn_calc_bit_or"            , test_rpn_calc_bit_or            } ,
    {"test_rpn_calc_bit_xor"           , test_rpn_calc_bit_xor           } ,
    {"test_rpn_calc_bit_left_shift"    , test_rpn_calc_bit_left_shift    } ,
    {"test_rpn_calc_bit_right_shift"   , test_rpn_calc_bit_right_shift   } ,
    {"test_rpn_calc_bit_left_shift1"   , test_rpn_calc_bit_left_shift1   } ,
    {"test_rpn_calc_bit_right_shift1"  , test_rpn_calc_bit_right_shift1  } ,
    {"test_rpn_calc_bit_right_shift1"  , test_rpn_calc_bit_right_shift1  } ,

    // --- HIGHER LEVEL OPERATIONS ---
    {"test_rpn_calc_expr"  , test_rpn_calc_expr  } ,
  };

// PERFORM THE TESTS
int performTests() {
  stack_init();

  // Ret holds the number of failed tests
  int total_ret = 0;
  int ret = 0;

  int num_of_tests = sizeof(test_functions)/sizeof(test_functions[0]);

  for (int i = 0; i < num_of_tests; i++) {
    if (test_functions[i].func) {
      ret = test_functions[i].func();
      if (ret) {
        total_ret++;
        printf("FAILED!  %s()\n", test_functions[i].name);
      }
      else {
        printf("SUCCEEDED!  %s()\n", test_functions[i].name);
      }
    }
    ret = 0;
    stack_init();
  }
  printf("\nNumber of Failed Tests: %d\n", total_ret);
  return total_ret;
}
