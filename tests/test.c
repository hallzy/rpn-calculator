#include <stdio.h>
#include <string.h>

#include "ctrl_codes.h"
#include "stack.h"
#include "test.h"
#include "operations.h"
#include "ui.h"

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

/* static void push_command(char command) { */
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
  push_number("5.5");
  push_command('\n');
  if (get_stack_size() == 3 && actual_result() == 5.5) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_drop() {
  push_number("1.0");
  push_number("2.0");
  push_command('d');
  push_command('d');
  if (get_stack_size() == 1 && actual_result() == 1.0) {
    return 0;
  }
  return 1;
}

/* static int test_rpn_calc_dropx() { */
/*   char input[input_size]; */

/*   strncpy(input, "5.0", input_size); */
/*   processUserInput(input, strlen(input)); */

/*   strncpy(input, "6.0", input_size); */
/*   processUserInput(input, strlen(input)); */

/*   strncpy(input, "7.0", input_size); */
/*   processUserInput(input, strlen(input)); */

/*   strncpy(input, "8.0", input_size); */
/*   processUserInput(input, strlen(input)); */

/*   strncpy(input, "2.0", input_size); */
/*   processUserInput(input, strlen(input)); */

/*   strncpy(input, "D", input_size); */
/*   processUserInput(input, strlen(input)); */

/*   if (get_stack_size() == 3 && */
/*       get_stack_value_at_index(0) == 5.0 && */
/*       get_stack_value_at_index(1) == 7.0 && */
/*       get_stack_value_at_index(2) == 8.0) { */
/*     return 0; */
/*   } */
/*   return 1; */
/* } */

static int test_rpn_calc_swap() {
  push_number("1.0");
  push_number("2.0");
  push_command('d');
  push_command('s');
  if (get_stack_size() == 2 && actual_result() == 1.0) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_clear() {
  push_number("1.0");
  push_number("2.0");
  push_number("3.0");
  push_number("4.0");
  push_number("5.0");
  push_number("6.0");
  push_command(ESCAPE);
  if (get_stack_size() == 0) {
    return 0;
  }
  return 1;
}

/* static int test_rpn_calc_clearx() { */
/*   char input[input_size]; */

/*   strncpy(input, "1.0", input_size); */
/*   processUserInput(input, strlen(input)); */

/*   strncpy(input, "2.0", input_size); */
/*   processUserInput(input, strlen(input)); */

/*   strncpy(input, "9.0", input_size); */
/*   processUserInput(input, strlen(input)); */

/*   strncpy(input, "4.0", input_size); */
/*   processUserInput(input, strlen(input)); */

/*   strncpy(input, "5.0", input_size); */
/*   processUserInput(input, strlen(input)); */

/*   strncpy(input, "6.0", input_size); */
/*   processUserInput(input, strlen(input)); */

/*   strncpy(input, "2.0", input_size); */
/*   processUserInput(input, strlen(input)); */

/*   strncpy(input, "C", input_size); */
/*   processUserInput(input, strlen(input)); */

/*   if (get_stack_size() == 2 && actual_result() == 2.0) { */
/*     return 0; */
/*   } */
/*   return 1; */
/* } */

// --- MATHEMATICAL OPERATORS ---

static int test_rpn_calc_plus() {
  push_number("1.0");
  push_number("2.0");
  push_command('d');
  push_command('+');
  if (get_stack_size() == 1 && actual_result() == 3.0) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_minus() {
  push_number("1.0");
  push_number("2.0");
  push_command('d');
  push_command('-');
  if (get_stack_size() == 1 && actual_result() == -1.0) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_neg() {
  push_number("1.0");
  push_number("2.0");
  push_command('d');
  push_command('n');
  if (get_stack_size() == 2 && actual_result() == -2.0) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_multiply() {
  push_number("3.0");
  push_number("2.0");
  push_command('d');
  push_command('*');
  if (get_stack_size() == 1 && actual_result() == 6.0) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_divide() {
  push_number("1.0");
  push_number("2.0");
  push_command('d');
  push_command('/');
  if (get_stack_size() == 1 && actual_result() == 0.5) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_pow() {
  push_number("2.0");
  push_number("4.0");
  push_command('d');
  push_command_string("Ep");
  if (get_stack_size() == 1 && actual_result() == 16.0) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_squared() {
  push_number("1.0");
  push_number("3.0");
  push_command('d');
  push_command_string("E2");
  if (get_stack_size() == 2 && actual_result() == 9.0) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_cubed() {
  push_number("1.0");
  push_number("2.0");
  push_command('d');
  push_command_string("E3");
  if (get_stack_size() == 2 && actual_result() == 8.0) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_sqrt() {
  push_number("1.0");
  push_number("25.0");
  push_command('d');
  push_command_string("R2");
  if (get_stack_size() == 2 && actual_result() == 5.0) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_cbrt() {
  push_number("1.0");
  push_number("125.0");
  push_command('d');
  push_command_string("R3");
  if (get_stack_size() == 2 && actual_result() == 5.0) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_xrt() {
  push_number("32.0");
  push_number("5.0");
  push_command('d');
  push_command_string("Rr");
  if (get_stack_size() == 1 && actual_result() == 2.0) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_inv() {
  push_number("1.0");
  push_number("3.0");
  push_command('d');
  push_command('i');
  if (get_stack_size() == 2 && actual_result() > 0.33332 &&
      actual_result() < 0.33334) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_sin_deg() {
  // Change to Degrees
  push_command(CTRL_E);
  push_number("30");
  push_command('d');
  push_command_string("Ts");
  if (get_stack_size() == 1 && actual_result() > 0.499999 &&
      actual_result() < 0.500001) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_sin_rad() {
  // Pi
  push_command_string("Cp");
  push_number("6");
  push_command('d');
  push_command('/');
  push_command_string("Ts");
  if (get_stack_size() == 1 && actual_result() > 0.499999 &&
      actual_result() < 0.500001) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_cos_deg() {
  // Change to Degrees
  push_command(CTRL_E);
  push_number("60");
  push_command('d');
  push_command_string("Tc");
  if (get_stack_size() == 1 && actual_result() > 0.499999 &&
      actual_result() < 0.500001) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_cos_rad() {
  // Pi
  push_command_string("Cp");
  push_number("3");
  push_command('d');
  push_command('/');
  push_command_string("Tc");
  if (get_stack_size() == 1 && actual_result() > 0.4999 &&
      actual_result() < 0.50001) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_tan_deg() {
  // Change to Degrees
  push_command(CTRL_E);
  push_number("45");
  push_command('d');
  push_command_string("Tt");
  if (get_stack_size() == 1 && actual_result() > 0.999999 &&
      actual_result() < 1.000001) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_tan_rad() {
  // Pi
  push_command_string("Cp");
  push_number("4");
  push_command('d');
  push_command('/');
  push_command_string("Tt");
  if (get_stack_size() == 1 && actual_result() > 0.999999 &&
      actual_result() < 1.000001) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_asin_deg() {
  // Change to Degrees
  push_command(CTRL_E);
  push_number("0.5");
  push_command('d');
  push_command_string("TS");
  if (get_stack_size() == 1 && actual_result() > 29.999999 &&
      actual_result() < 30.000001) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_asin_rad() {
  push_number("0.5");
  push_command('d');
  push_command_string("TS");
  if (get_stack_size() == 1 && actual_result() > 0.523598
      && actual_result() < 0.523600) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_acos_deg() {
  // Change to Degrees
  push_command(CTRL_E);
  push_number("0.5");
  push_command('d');
  push_command_string("TC");
  if (get_stack_size() == 1 && actual_result() > 59.999999 &&
      actual_result() < 60.000001) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_acos_rad() {
  push_number("0.5");
  push_command('d');
  push_command_string("TC");
  if (get_stack_size() == 1 && actual_result() > 0.877582 &&
      actual_result() < 0.877584) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_atan_deg() {
  // Change to Degrees
  push_command(CTRL_E);
  push_number("1.0");
  push_command('d');
  push_command_string("TT");
  if (get_stack_size() == 1 && actual_result() == 45) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_atan_rad() {
  push_number("1.0");
  push_command('d');
  push_command_string("TT");
  if (get_stack_size() == 1 && actual_result() > 1.557407 &&
      actual_result() < 1.557409) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_log() {
  push_number("100");
  push_command('d');
  push_command_string("Ll");
  if (get_stack_size() == 1 && actual_result() == 2) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_ln() {
  // e constant
  push_command_string("Ce");
  push_command_string("Le");
  if (get_stack_size() == 1 && actual_result() > 0.999999 &&
      actual_result() < 1.000001) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_logx() {
  push_number("2");
  push_number("8");
  push_command('d');
  push_command_string("Lx");
  if (get_stack_size() == 1 && actual_result() > 2.999999 &&
      actual_result() < 3.000001) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_exp() {
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
    return 0;
  }
  return 1;
}

/* static int test_rpn_calc_sumstack() { */
/*   char input[input_size]; */

/*   strncpy(input, "5", input_size); */
/*   processUserInput(input, strlen(input)); */

/*   strncpy(input, "10", input_size); */
/*   processUserInput(input, strlen(input)); */

/*   strncpy(input, "7", input_size); */
/*   processUserInput(input, strlen(input)); */

/*   strncpy(input, "3", input_size); */
/*   processUserInput(input, strlen(input)); */

/*   strncpy(input, "5", input_size); */
/*   processUserInput(input, strlen(input)); */

/*   strncpy(input, "2", input_size); */
/*   processUserInput(input, strlen(input)); */

/*   strncpy(input, "4", input_size); */
/*   processUserInput(input, strlen(input)); */

/*   strncpy(input, "sumstack", input_size); */
/*   processUserInput(input, strlen(input)); */


/*   if (get_stack_size() == 3 && actual_result() == 20.0 && */
/*       get_stack_value_at_index(0) == 5 && get_stack_value_at_index(1) == 5) { */
/*     return 0; */
/*   } */
/*   return 1; */
/* } */

/* static int test_rpn_calc_sum() { */
/*   char input[input_size]; */

/*   strncpy(input, "5", input_size); */
/*   processUserInput(input, strlen(input)); */

/*   strncpy(input, "1", input_size); */
/*   processUserInput(input, strlen(input)); */

/*   strncpy(input, "100", input_size); */
/*   processUserInput(input, strlen(input)); */

/*   strncpy(input, "sum", input_size); */
/*   processUserInput(input, strlen(input)); */

/*   if (get_stack_size() == 2 && actual_result() == 5050.0) { */
/*     return 0; */
/*   } */
/*   return 1; */
/* } */

/* static int test_rpn_calc_avgstack() { */
/*   char input[input_size]; */

/*   strncpy(input, "11", input_size); */
/*   processUserInput(input, strlen(input)); */

/*   strncpy(input, "3", input_size); */
/*   processUserInput(input, strlen(input)); */

/*   strncpy(input, "3", input_size); */
/*   processUserInput(input, strlen(input)); */

/*   strncpy(input, "5", input_size); */
/*   processUserInput(input, strlen(input)); */

/*   strncpy(input, "7", input_size); */
/*   processUserInput(input, strlen(input)); */

/*   strncpy(input, "4", input_size); */
/*   processUserInput(input, strlen(input)); */

/*   strncpy(input, "6", input_size); */
/*   processUserInput(input, strlen(input)); */

/*   strncpy(input, "8", input_size); */
/*   processUserInput(input, strlen(input)); */

/*   strncpy(input, "93", input_size); */
/*   processUserInput(input, strlen(input)); */

/*   strncpy(input, "2", input_size); */
/*   processUserInput(input, strlen(input)); */

/*   strncpy(input, "5", input_size); */
/*   processUserInput(input, strlen(input)); */

/*   strncpy(input, "7", input_size); */
/*   processUserInput(input, strlen(input)); */

/*   strncpy(input, "9", input_size); */
/*   processUserInput(input, strlen(input)); */

/*   strncpy(input, "2", input_size); */
/*   processUserInput(input, strlen(input)); */

/*   strncpy(input, "12", input_size); */
/*   processUserInput(input, strlen(input)); */

/*   strncpy(input, "avgstack", input_size); */
/*   processUserInput(input, strlen(input)); */


/*   if (get_stack_size() == 3 && get_stack_value_at_index(0) == 11.0 && */
/*       get_stack_value_at_index(1) == 9 && get_stack_value_at_index(2) == 13) { */
/*     return 0; */
/*   } */
/*   return 1; */
/* } */

static int test_rpn_calc_factorial() {
  push_number("7");
  push_command('d');
  push_command('!');
  if (get_stack_size() == 1 && actual_result() == 5040) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_fibonacci() {
  push_number("30");
  push_command('d');
  push_command('f');
  if (get_stack_size() == 1 && actual_result() == 832040) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_rand() {
  int r = 0;

  push_command_string("rr");
  if (!(get_stack_size() == 1 && actual_result() >= 0 &&
        actual_result() <= 1)) {
    r = 1;
  }

  push_command_string("rr");
  if (!(get_stack_size() == 2 && actual_result() >= 0 &&
        actual_result() <= 1)) {
    r = 1;
  }

  push_command_string("rr");
  if (!(get_stack_size() == 3 && actual_result() >= 0 &&
        actual_result() <= 1)) {
    r = 1;
  }

  push_command_string("rr");
  if (!(get_stack_size() == 4 && actual_result() >= 0 &&
        actual_result() <= 1)) {
    r = 1;
  }
  return r;
}

static int test_rpn_calc_randx() {
  int r = 0;

  push_number("1");
  push_number("10");
  push_command('d');
  push_command_string("rx");
  if (!(get_stack_size() == 1 && actual_result() >= 1 &&
        actual_result() <= 10)) {
    r = 1;
  }

  push_number("1");
  push_number("10");
  push_command('d');
  push_command_string("rx");
  if (!(get_stack_size() == 2 && actual_result() >= 1 &&
        actual_result() <= 10)) {
    r = 1;
  }

  push_number("1");
  push_number("10");
  push_command('d');
  push_command_string("rx");
  if (!(get_stack_size() == 3 && actual_result() >= 1 &&
        actual_result() <= 10)) {
    r = 1;
  }

  push_number("1");
  push_number("10");
  push_command('d');
  push_command_string("rx");
  if (!(get_stack_size() == 4 && actual_result() >= 1 &&
        actual_result() <= 10)) {
    r = 1;
  }

  return r;
}

// --- BITWISE OPERATIONS ---

static int test_rpn_calc_bit_and() {
  push_number("0b1010");
  push_number("0b11");
  push_command('d');
  push_command('&');
  if (get_stack_size() == 1 && actual_result() == 2) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_bit_or() {
  push_number("0b1010");
  push_number("0b11");
  push_command('d');
  push_command('|');
  if (get_stack_size() == 1 && actual_result() == 11) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_bit_xor() {
  push_number("0b1010");
  push_number("0b11");
  push_command('d');
  push_command('^');
  if (get_stack_size() == 1 && actual_result() == 9) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_bit_left_shift() {
  push_number("0b1010");
  push_number("0b10");
  push_command('d');
  push_command('<');
  if (get_stack_size() == 1 && actual_result() == 40) {
    return 0;
  }
  return 1;
}

static int test_rpn_calc_bit_right_shift() {
  push_number("0b1010");
  push_number("3");
  push_command('d');
  push_command('>');
  if (get_stack_size() == 1 && actual_result() == 1) {
    return 0;
  }
  return 1;
}

/* static int test_rpn_calc_bit_left_shift1() { */
/*   char input[input_size]; */

/*   strncpy(input, "0b1010", input_size); */
/*   processUserInput(input, strlen(input)); */

/*   strncpy(input, "<<1", input_size); */
/*   processUserInput(input, strlen(input)); */

/*   if (get_stack_size() == 1 && actual_result() == 20) { */
/*     return 0; */
/*   } */
/*   return 1; */
/* } */

/* static int test_rpn_calc_bit_right_shift1() { */
/*   char input[input_size]; */

/*   strncpy(input, "0b1010", input_size); */
/*   processUserInput(input, strlen(input)); */

/*   strncpy(input, ">>1", input_size); */
/*   processUserInput(input, strlen(input)); */

/*   if (get_stack_size() == 1 && actual_result() == 5) { */
/*     return 0; */
/*   } */
/*   return 1; */
/* } */

// --- HIGHER LEVEL OPERATIONS ---

static int test_rpn_calc_expr() {
  char input[input_size];

  // 4+(4*(2+6))/2 = 20
  strncpy(input, "e 2 6 + 4 * 2 / 4 +", input_size);
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
    {"test_rpn_calc_swap"              , test_rpn_calc_swap              } ,
    {"test_rpn_calc_clear"             , test_rpn_calc_clear             } ,

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
    /* {"test_rpn_calc_sumstack"          , test_rpn_calc_sumstack          } , */
    /* {"test_rpn_calc_sum"               , test_rpn_calc_sum               } , */
    /* {"test_rpn_calc_avgstack"          , test_rpn_calc_avgstack          } , */
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
