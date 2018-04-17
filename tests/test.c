#include <stdio.h>
#include <string.h>

#include "ctrl_codes.h"
#include "stack.h"
#include "test.h"
#include "operations.h"
#include "ui.h"
#include "itoa.h"

#define input_size 128

static long double actual_result() {
  return get_stack_value_at_index(get_stack_size() - 1);
}

static void push_number(char *num) {
  char input[input_size];

  strncpy(input, num, input_size);
  strncat(input, "\n", 1);
  processUserInput(input, strlen(input));
}

static void push_command_string(char *input) {
  processUserInput(input, strlen(input));
}

static void push_command(char command) {
  char input[2];
  input[0] = command;
  input[1] = 0;
  processUserInput(input, strlen(input));
}

// --- STACK MANIPULATION FUNCTIONS ---

static int test_rpn_calc_duplicate() {
  int ret = 1;
  push_number("5.5");
  push_command('\n');
  if (get_stack_size() == 3 && actual_result() == 5.5) {
    ret = 0;
  }
  return ret;
}

static int test_rpn_calc_drop() {
  int ret = 1;
  push_number("1.0");
  push_number("2.0");
  push_command('d');
  push_command('d');
  if (get_stack_size() == 1 && actual_result() == 1.0) {
    ret = 0;
  }
  return ret;
}

static int test_rpn_calc_swap() {
  int ret = 1;
  push_number("1.0");
  push_number("2.0");
  push_command('d');
  push_command('s');
  if (get_stack_size() == 2 && actual_result() == 1.0) {
    ret = 0;
  }
  return ret;
}

static int test_rpn_calc_clear() {
  int ret = 1;
  push_number("1.0");
  push_number("2.0");
  push_number("3.0");
  push_number("4.0");
  push_number("5.0");
  push_number("6.0");
  push_command(ESCAPE);
  if (get_stack_size() == 0) {
    ret = 0;
  }
  return ret;
}

static int test_rpn_calc_stack_max() {
  int ret = 1;
  int i;
  // start at 2 because the first push pushes 2 numbers
  for (i = 0; i < MAX_STK+30; i++) {
    push_number("1.0");
  }

  if (get_stack_size() == 128) {
    ret = 0;
  }
  return ret;
}

// --- MATHEMATICAL OPERATORS ---

static int test_rpn_calc_plus() {
  int ret = 1;
  push_number("1.0");
  push_number("2.0");
  push_command('d');
  push_command('+');
  if (get_stack_size() == 1 && actual_result() == 3.0) {
    ret = 0;
  }
  return ret;
}

static int test_rpn_calc_minus() {
  int ret = 1;
  push_number("1.0");
  push_number("2.0");
  push_command('d');
  push_command('-');
  if (get_stack_size() == 1 && actual_result() == -1.0) {
    ret = 0;
  }
  return ret;
}

static int test_rpn_calc_neg() {
  int ret = 1;
  push_number("1.0");
  push_number("2.0");
  push_command('d');
  push_command('n');
  if (get_stack_size() == 2 && actual_result() == -2.0) {
    ret = 0;
  }
  return ret;
}

static int test_rpn_calc_multiply() {
  int ret = 1;
  push_number("3.0");
  push_number("2.0");
  push_command('d');
  push_command('*');
  if (get_stack_size() == 1 && actual_result() == 6.0) {
    ret = 0;
  }
  return ret;
}

static int test_rpn_calc_divide() {
  int ret = 1;
  push_number("1.0");
  push_number("2.0");
  push_command('d');
  push_command('/');
  if (get_stack_size() == 1 && actual_result() == 0.5) {
    ret = 0;
  }
  return ret;
}

static int test_rpn_calc_pow() {
  int ret = 1;
  push_number("2.0");
  push_number("4.0");
  push_command('d');
  push_command_string("Ep");
  if (get_stack_size() == 1 && actual_result() == 16.0) {
    ret = 0;
  }
  return ret;
}

static int test_rpn_calc_squared() {
  int ret = 1;
  push_number("1.0");
  push_number("3.0");
  push_command('d');
  push_command_string("E2");
  if (get_stack_size() == 2 && actual_result() == 9.0) {
    ret = 0;
  }
  return ret;
}

static int test_rpn_calc_cubed() {
  int ret = 1;
  push_number("1.0");
  push_number("2.0");
  push_command('d');
  push_command_string("E3");
  if (get_stack_size() == 2 && actual_result() == 8.0) {
    ret = 0;
  }
  return ret;
}

static int test_rpn_calc_sqrt() {
  int ret = 1;
  push_number("1.0");
  push_number("25.0");
  push_command('d');
  push_command_string("R2");
  if (get_stack_size() == 2 && actual_result() == 5.0) {
    ret = 0;
  }
  return ret;
}

static int test_rpn_calc_cbrt() {
  int ret = 1;
  push_number("1.0");
  push_number("125.0");
  push_command('d');
  push_command_string("R3");
  if (get_stack_size() == 2 && actual_result() == 5.0) {
    ret = 0;
  }
  return ret;
}

static int test_rpn_calc_xrt() {
  int ret = 1;
  push_number("32.0");
  push_number("5.0");
  push_command('d');
  push_command_string("Rr");
  if (get_stack_size() == 1 && actual_result() == 2.0) {
    ret = 0;
  }
  return ret;
}

static int test_rpn_calc_inv() {
  int ret = 1;
  push_number("1.0");
  push_number("3.0");
  push_command('d');
  push_command('i');
  if (get_stack_size() == 2 && actual_result() > 0.33332 &&
      actual_result() < 0.33334) {
    ret = 0;
  }
  return ret;
}

static int test_rpn_calc_sin_deg() {
  int ret = 1;
  // Change to Degrees
  push_command(CTRL_E);
  push_number("30");
  push_command('d');
  push_command_string("Ts");
  if (get_stack_size() == 1 && actual_result() > 0.499999 &&
      actual_result() < 0.500001) {
    ret = 0;
  }
  return ret;
}

static int test_rpn_calc_sin_rad() {
  int ret = 1;
  // Pi
  push_command_string("cp");
  push_number("6");
  push_command('d');
  push_command('/');
  push_command_string("Ts");
  if (get_stack_size() == 1 && actual_result() > 0.499999 &&
      actual_result() < 0.500001) {
    ret = 0;
  }
  return ret;
}

static int test_rpn_calc_cos_deg() {
  int ret = 1;
  // Change to Degrees
  push_command(CTRL_E);
  push_number("60");
  push_command('d');
  push_command_string("Tc");
  if (get_stack_size() == 1 && actual_result() > 0.499999 &&
      actual_result() < 0.500001) {
    ret = 0;
  }
  return ret;
}

static int test_rpn_calc_cos_rad() {
  int ret = 1;
  // Pi
  push_command_string("cp");
  push_number("3");
  push_command('d');
  push_command('/');
  push_command_string("Tc");
  if (get_stack_size() == 1 && actual_result() > 0.4999 &&
      actual_result() < 0.50001) {
    ret = 0;
  }
  return ret;
}

static int test_rpn_calc_tan_deg() {
  int ret = 1;
  // Change to Degrees
  push_command(CTRL_E);
  push_number("45");
  push_command('d');
  push_command_string("Tt");
  if (get_stack_size() == 1 && actual_result() > 0.999999 &&
      actual_result() < 1.000001) {
    ret = 0;
  }
  return ret;
}

static int test_rpn_calc_tan_rad() {
  int ret = 1;
  // Pi
  push_command_string("cp");
  push_number("4");
  push_command('d');
  push_command('/');
  push_command_string("Tt");
  if (get_stack_size() == 1 && actual_result() > 0.999999 &&
      actual_result() < 1.000001) {
    ret = 0;
  }
  return ret;
}

static int test_rpn_calc_asin_deg() {
  int ret = 1;
  // Change to Degrees
  push_command(CTRL_E);
  push_number("0.5");
  push_command('d');
  push_command_string("TS");
  if (get_stack_size() == 1 && actual_result() > 29.999999 &&
      actual_result() < 30.000001) {
    ret = 0;
  }
  return ret;
}

static int test_rpn_calc_asin_rad() {
  int ret = 1;
  push_number("0.5");
  push_command('d');
  push_command_string("TS");
  if (get_stack_size() == 1 && actual_result() > 0.523598
      && actual_result() < 0.523600) {
    ret = 0;
  }
  return ret;
}

static int test_rpn_calc_acos_deg() {
  int ret = 1;
  // Change to Degrees
  push_command(CTRL_E);
  push_number("0.5");
  push_command('d');
  push_command_string("TC");
  if (get_stack_size() == 1 && actual_result() > 59.999999 &&
      actual_result() < 60.000001) {
    ret = 0;
  }
  return ret;
}

static int test_rpn_calc_acos_rad() {
  int ret = 1;
  push_number("0.5");
  push_command('d');
  push_command_string("TC");
  if (get_stack_size() == 1 && actual_result() > 0.877582 &&
      actual_result() < 0.877584) {
    ret = 0;
  }
  return ret;
}

static int test_rpn_calc_atan_deg() {
  int ret = 1;
  // Change to Degrees
  push_command(CTRL_E);
  push_number("1.0");
  push_command('d');
  push_command_string("TT");
  if (get_stack_size() == 1 && actual_result() == 45) {
    ret = 0;
  }
  return ret;
}

static int test_rpn_calc_atan_rad() {
  int ret = 1;
  push_number("1.0");
  push_command('d');
  push_command_string("TT");
  if (get_stack_size() == 1 && actual_result() > 1.557407 &&
      actual_result() < 1.557409) {
    ret = 0;
  }
  return ret;
}

static int test_rpn_calc_log() {
  int ret = 1;
  push_number("100");
  push_command('d');
  push_command_string("Ll");
  if (get_stack_size() == 1 && actual_result() == 2) {
    ret = 0;
  }
  return ret;
}

static int test_rpn_calc_ln() {
  int ret = 1;
  // e constant
  push_command_string("ce");
  push_command_string("Le");
  if (get_stack_size() == 1 && actual_result() == 1) {
    ret = 0;
  }
  return ret;
}

static int test_rpn_calc_logx() {
  int ret = 1;
  push_number("2");
  push_number("8");
  push_command('d');
  push_command_string("Lx");
  if (get_stack_size() == 1 && actual_result() == 3) {
    ret = 0;
  }
  return ret;
}

static int test_rpn_calc_exp() {
  int ret = 1;
  push_number("2");
  push_command('d');
  push_command_string("Ee");
  char input[input_size];

  strncpy(input, "2", input_size);
  processUserInput(input, strlen(input));

  strncpy(input, "exp", input_size);
  processUserInput(input, strlen(input));

  if (get_stack_size() == 1 && actual_result() > 7.389055 &&
      actual_result() < 7.389057) {
    ret = 0;
  }
  return ret;
}

static int test_rpn_calc_sumstack() {
  int ret = 1;
  push_number("5");
  push_number("10");
  push_number("7");
  push_number("3");
  push_number("5");
  push_number("2");
  push_number("4");
  push_command('d');
  push_command_string("Cs");
  if (get_stack_size() == 3 && actual_result() == 20.0 &&
      get_stack_value_at_index(0) == 5 && get_stack_value_at_index(1) == 5) {
    ret = 0;
  }
  return ret;
}

static int test_rpn_calc_sum() {
  int ret = 1;
  push_number("5");
  push_number("1");
  push_number("100");
  push_command('d');
  push_command_string("CS");
  if (get_stack_size() == 2 && actual_result() == 5050.0) {
    ret = 0;
  }
  return ret;
}

static int test_rpn_calc_avgstack() {
  int ret = 1;
  push_number("11");
  push_number("3");
  push_number("3");
  push_number("5");
  push_number("7");
  push_number("4");
  push_number("6");
  push_number("8");
  push_number("93");
  push_number("2");
  push_number("5");
  push_number("7");
  push_number("9");
  push_number("2");
  push_number("12");
  push_command('d');
  push_command_string("Ca");
  if (get_stack_size() == 3 && get_stack_value_at_index(0) == 11.0 &&
      get_stack_value_at_index(1) == 9 && get_stack_value_at_index(2) == 13) {
    ret = 0;
  }
  return ret;
}

static int test_rpn_calc_factorial() {
  int ret = 1;
  push_number("7");
  push_command('d');
  push_command('!');
  if (get_stack_size() == 1 && actual_result() == 5040) {
    ret = 0;
  }
  return ret;
}

static int test_rpn_calc_factorial_repeat() {
  int ret = 1;
  push_number("8");
  push_command('d');
  push_command('!');
  if (get_stack_size() == 1 && actual_result() == 40320) {
    ret = 0;
  }
  return ret;
}

static int test_rpn_calc_factorial_over_max() {
  int ret = 1;
  push_number("26");
  push_command('d');
  push_command('!');
  if (get_stack_size() == 1 && actual_result() == 26) {
    ret = 0;
  }
  return ret;
}

static int test_rpn_calc_fibonacci() {
  int ret = 1;
  push_number("30");
  push_command('d');
  push_command_string("Cf");
  if (get_stack_size() == 1 && actual_result() == 832040) {
    ret = 0;
  }
  return ret;
}

static int test_rpn_calc_fibonacci_over_max() {
  int ret = 1;
  push_number("94");
  push_command('d');
  push_command_string("Cf");
  if (get_stack_size() == 1 && actual_result() == 94) {
    ret = 0;
  }
  return ret;
}

static int test_rpn_calc_rand() {
  int r = 4;

  push_command_string("rr");
  if (get_stack_size() == 1 && actual_result() >= 0 &&
        actual_result() <= 1) {
    r -= 1;
  }

  push_command_string("rr");
  if (get_stack_size() == 2 && actual_result() >= 0 &&
        actual_result() <= 1) {
    r -= 1;
  }

  push_command_string("rr");
  if (get_stack_size() == 3 && actual_result() >= 0 &&
        actual_result() <= 1) {
    r -= 1;
  }

  push_command_string("rr");
  if (get_stack_size() == 4 && actual_result() >= 0 &&
        actual_result() <= 1) {
    r -= 1;
  }

  return r == 0 ? 0 : 1;
}

static int test_rpn_calc_randx() {
  int r = 4;

  push_number("1");
  push_number("10");
  push_command('d');
  push_command_string("rx");
  if (get_stack_size() == 1 && actual_result() >= 1 &&
        actual_result() <= 10) {
    r -= 1;
  }

  push_number("1");
  push_number("10");
  push_command('d');
  push_command_string("rx");
  if (get_stack_size() == 2 && actual_result() >= 1 &&
        actual_result() <= 10) {
    r -= 1;
  }

  push_number("1");
  push_number("10");
  push_command('d');
  push_command_string("rx");
  if (get_stack_size() == 3 && actual_result() >= 1 &&
        actual_result() <= 10) {
    r -= 1;
  }

  push_number("1");
  push_number("10");
  push_command('d');
  push_command_string("rx");
  if (get_stack_size() == 4 && actual_result() >= 1 &&
        actual_result() <= 10) {
    r -= 1;
  }

  return r == 0 ? 0 : 1;
}

static int test_rpn_calc_is_prime() {
  int r = 5;

  push_number("100");
  push_command('d');
  push_command_string("Cp");
  if (get_stack_size() == 1 && actual_result() == 0) {
    r -= 1;
  }

  push_number("5");
  push_command('d');
  push_command_string("Cp");
  if (get_stack_size() == 2 && actual_result() == 1) {
    r -= 1;
  }

  push_number("100");
  push_command('d');
  push_command('n');
  push_command_string("Cp");
  if (get_stack_size() == 3 && actual_result() == 0) {
    r -= 1;
  }

  push_number("1");
  push_command('d');
  push_command_string("Cp");
  if (get_stack_size() == 4 && actual_result() == 0) {
    r -= 1;
  }

  push_number("0");
  push_command('d');
  push_command_string("Cp");
  if (get_stack_size() == 5 && actual_result() == 0) {
    r -= 1;
  }

  return r == 0 ? 0 : 1;
}

// --- BITWISE OPERATIONS ---

static int test_rpn_calc_bit_and() {
  int ret = 1;
  push_number("0b1010");
  push_number("0b11");
  push_command('d');
  push_command('&');
  if (get_stack_size() == 1 && actual_result() == 2) {
    ret = 0;
  }
  return ret;
}

static int test_rpn_calc_bit_or() {
  int ret = 1;
  push_number("012");
  push_number("03");
  push_command('d');
  push_command('|');
  if (get_stack_size() == 1 && actual_result() == 11) {
    ret = 0;
  }
  return ret;
}

static int test_rpn_calc_bit_xor() {
  int ret = 1;
  push_number("0b1010");
  push_number("0b11");
  push_command('d');
  push_command('^');
  if (get_stack_size() == 1 && actual_result() == 9) {
    ret = 0;
  }
  return ret;
}

static int test_rpn_calc_bit_left_shift() {
  int ret = 1;
  push_number("0b1010");
  push_number("0b10");
  push_command('d');
  push_command('<');
  if (get_stack_size() == 1 && actual_result() == 40) {
    ret = 0;
  }
  return ret;
}

static int test_rpn_calc_bit_right_shift() {
  int ret = 1;
  push_number("0b1010");
  push_number("3");
  push_command('d');
  push_command('>');
  if (get_stack_size() == 1 && actual_result() == 1) {
    ret = 0;
  }
  return ret;
}

// --- HIGHER LEVEL OPERATIONS ---

static int test_rpn_calc_expr() {
  int ret = 1;
  char input[input_size];

  // 4+(4*(2+6))/2 = 20
  strncpy(input, "e 2 6 + 4 * 2 / 4 +", input_size);
  processUserInput(input, strlen(input));

  if (get_stack_size() == 1 && actual_result() == 20) {
    ret = 0;
  }
  return ret;
}

// --- OTHER ---
static int test_itoa_base_2() {
  int ret = 1;
  int twenty = 20;
  int base = 2;
  char result[128];

  // Convert 20 to a binary number
  itoa(twenty, result, base);
  if (strcmp(result, "10100") == 0) {
    ret = 0;
  }
  return ret;
}

static int test_itoa_undefined_base() {
  int ret = 1;
  int twenty = 20;
  int base = 37;
  char result[128];

  // Convert 20 to a binary number
  itoa(twenty, result, base);
  if (strcmp(result, "") == 0) {
    ret = 0;
  }
  return ret;
}

static int test_itoa_negative() {
  int ret = 1;
  int twenty = -20;
  int base = 2;
  char result[128];

  // Convert 20 to a binary number
  itoa(twenty, result, base);
  if (strcmp(result, "-10100") == 0) {
    ret = 0;
  }
  return ret;
}

// --- REGRESSION ---

static int test_rpn_calc_numbers_hold_precision() {
  int ret = 1;
  push_number("20.55");
  push_command('d');
  if (get_stack_size() == 1 && actual_result() == 20.55) {
    ret = 0;
  }
  return ret;
}

// LIST OF TESTS
const static struct {
  const char *name;
  int (*func)(void);

} test_functions [] = {
    // --- STACK MANIPULATION FUNCTIONS ---
    {"test_rpn_calc_duplicate"         , test_rpn_calc_duplicate         } ,
    {"test_rpn_calc_drop"              , test_rpn_calc_drop              } ,
    {"test_rpn_calc_swap"              , test_rpn_calc_swap              } ,
    {"test_rpn_calc_clear"             , test_rpn_calc_clear             } ,
    {"test_rpn_calc_stack_max"         , test_rpn_calc_stack_max         } ,

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
    {"test_rpn_calc_factorial_repeat"  , test_rpn_calc_factorial_repeat  } ,
    {"test_rpn_calc_factorial_over_max", test_rpn_calc_factorial_over_max} ,
    {"test_rpn_calc_fibonacci"         , test_rpn_calc_fibonacci         } ,
    {"test_rpn_calc_fibonacci_over_max", test_rpn_calc_fibonacci_over_max} ,
    {"test_rpn_calc_rand"              , test_rpn_calc_rand              } ,
    {"test_rpn_calc_randx"             , test_rpn_calc_randx             } ,
    {"Test_rpn_calc_is_prime"          , test_rpn_calc_is_prime          } ,

    // --- BITWISE OPERATIONS ---
    {"test_rpn_calc_bit_and"           , test_rpn_calc_bit_and           } ,
    {"test_rpn_calc_bit_or"            , test_rpn_calc_bit_or            } ,
    {"test_rpn_calc_bit_xor"           , test_rpn_calc_bit_xor           } ,
    {"test_rpn_calc_bit_left_shift"    , test_rpn_calc_bit_left_shift    } ,
    {"test_rpn_calc_bit_right_shift"   , test_rpn_calc_bit_right_shift   } ,

    // --- HIGHER LEVEL OPERATIONS ---
    {"test_rpn_calc_expr"  , test_rpn_calc_expr  } ,

    // Other
    {"test_itoa_negative"              , test_itoa_negative              } ,
    {"test_itoa_undefined_base"        , test_itoa_undefined_base        } ,
    {"test_itoa_base_2"                , test_itoa_base_2                } ,

    // --- REGRESSION ---
    {"test_rpn_calc_numbers_hold_precision"  , test_rpn_calc_numbers_hold_precision  } ,
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
