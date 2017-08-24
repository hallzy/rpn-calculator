#include <stdio.h>
#include <string.h>

#include "stack.h"
#include "test.h"
#include "operations.h"

#define input_size 128

static float actual_result() {
  return s.stk[s.top];
}

// --- STACK MANIPULATION FUNCTIONS ---

static int test_duplicate() {
  char input[input_size];

  strncpy(input, "5.5", input_size);
  push(input, strlen(input));

  strncpy(input, "\n", input_size);
  push(input, strlen(input));

  if (stack_size() == 2 && actual_result() == 5.5) {
    return 0;
  }
  return 1;
}

static int test_drop() {
  char input[input_size];

  strncpy(input, "1.0", input_size);
  push(input, strlen(input));

  strncpy(input, "2.0", input_size);
  push(input, strlen(input));

  strncpy(input, "drop", input_size);
  push(input, strlen(input));

  if (stack_size() == 1 && actual_result() == 1.0) {
    return 0;
  }
  return 1;
}

static int test_swap() {
  char input[input_size];

  strncpy(input, "1.0", input_size);
  push(input, strlen(input));

  strncpy(input, "2.0", input_size);
  push(input, strlen(input));

  strncpy(input, "swap", input_size);
  push(input, strlen(input));

  if (stack_size() == 2 && actual_result() == 1.0) {
    return 0;
  }
  return 1;
}

// --- MATHEMATICAL OPERATORS ---

static int test_plus() {
  char input[input_size];

  strncpy(input, "1.0", input_size);
  push(input, strlen(input));

  strncpy(input, "2.0", input_size);
  push(input, strlen(input));

  strncpy(input, "+", input_size);
  push(input, strlen(input));

  if (stack_size() == 1 && actual_result() == 3.0) {
    return 0;
  }
  return 1;
}

static int test_minus() {
  char input[input_size];

  strncpy(input, "1.0", input_size);
  push(input, strlen(input));

  strncpy(input, "2.0", input_size);
  push(input, strlen(input));

  strncpy(input, "-", input_size);
  push(input, strlen(input));

  if (stack_size() == 1 && actual_result() == -1.0) {
    return 0;
  }
  return 1;
}

static int test_neg() {
  char input[input_size];

  strncpy(input, "1.0", input_size);
  push(input, strlen(input));

  strncpy(input, "2.0", input_size);
  push(input, strlen(input));

  strncpy(input, "neg", input_size);
  push(input, strlen(input));

  if (stack_size() == 2 && actual_result() == -2.0) {
    return 0;
  }
  return 1;
}

static int test_multiply() {
  char input[input_size];

  strncpy(input, "3.0", input_size);
  push(input, strlen(input));

  strncpy(input, "2.0", input_size);
  push(input, strlen(input));

  strncpy(input, "*", input_size);
  push(input, strlen(input));

  if (stack_size() == 1 && actual_result() == 6.0) {
    return 0;
  }
  return 1;
}

static int test_divide() {
  char input[input_size];

  strncpy(input, "1.0", input_size);
  push(input, strlen(input));

  strncpy(input, "2.0", input_size);
  push(input, strlen(input));

  strncpy(input, "/", input_size);
  push(input, strlen(input));

  if (stack_size() == 1 && actual_result() == 0.5) {
    return 0;
  }
  return 1;
}

static int test_my_pow() {
  char input[input_size];

  strncpy(input, "2.0", input_size);
  push(input, strlen(input));

  strncpy(input, "4.0", input_size);
  push(input, strlen(input));

  strncpy(input, "**", input_size);
  push(input, strlen(input));

  if (stack_size() == 1 && actual_result() == 16.0) {
    return 0;
  }
  return 1;
}

static int test_squared() {
  char input[input_size];

  strncpy(input, "1.0", input_size);
  push(input, strlen(input));

  strncpy(input, "3.0", input_size);
  push(input, strlen(input));

  strncpy(input, "**2", input_size);
  push(input, strlen(input));

  if (stack_size() == 2 && actual_result() == 9.0) {
    return 0;
  }
  return 1;
}

static int test_cubed() {
  char input[input_size];

  strncpy(input, "1.0", input_size);
  push(input, strlen(input));

  strncpy(input, "2.0", input_size);
  push(input, strlen(input));

  strncpy(input, "**3", input_size);
  push(input, strlen(input));

  if (stack_size() == 2 && actual_result() == 8.0) {
    return 0;
  }
  return 1;
}

static int test_my_sqrt() {
  char input[input_size];

  strncpy(input, "1.0", input_size);
  push(input, strlen(input));

  strncpy(input, "25.0", input_size);
  push(input, strlen(input));

  strncpy(input, "sqrt", input_size);
  push(input, strlen(input));

  if (stack_size() == 2 && actual_result() == 5.0) {
    return 0;
  }
  return 1;
}

static int test_my_cbrt() {
  char input[input_size];

  strncpy(input, "1.0", input_size);
  push(input, strlen(input));

  strncpy(input, "125.0", input_size);
  push(input, strlen(input));

  strncpy(input, "cbrt", input_size);
  push(input, strlen(input));

  if (stack_size() == 2 && actual_result() == 5.0) {
    return 0;
  }
  return 1;
}

static int test_xrt() {
  char input[input_size];

  strncpy(input, "32.0", input_size);
  push(input, strlen(input));

  strncpy(input, "5.0", input_size);
  push(input, strlen(input));

  strncpy(input, "//", input_size);
  push(input, strlen(input));

  if (stack_size() == 1 && actual_result() == 2.0) {
    return 0;
  }
  return 1;
}

static int test_my_abs() {
  char input[input_size];

  strncpy(input, "1.0", input_size);
  push(input, strlen(input));

  strncpy(input, "-2.0", input_size);
  push(input, strlen(input));

  strncpy(input, "abs", input_size);
  push(input, strlen(input));

  if (stack_size() == 2 && actual_result() == 2.0) {
    return 0;
  }
  return 1;
}

static int test_inv() {
  char input[input_size];

  strncpy(input, "1.0", input_size);
  push(input, strlen(input));

  strncpy(input, "3.0", input_size);
  push(input, strlen(input));

  strncpy(input, "inv", input_size);
  push(input, strlen(input));

  if (stack_size() == 2 && actual_result() > 0.33332 &&
      actual_result() < 0.33334) {
    return 0;
  }
  return 1;
}

static int test_sine_deg() {
  char input[input_size];

  strncpy(input, "deg", input_size);
  push(input, strlen(input));

  strncpy(input, "30", input_size);
  push(input, strlen(input));

  strncpy(input, "sin", input_size);
  push(input, strlen(input));

  if (stack_size() == 1 && actual_result() == 0.5) {
    return 0;
  }
  return 1;
}

static int test_sine_rad() {
  char input[input_size];

  strncpy(input, "rad", input_size);
  push(input, strlen(input));

  strncpy(input, "pi", input_size);
  push(input, strlen(input));

  strncpy(input, "6", input_size);
  push(input, strlen(input));

  strncpy(input, "/", input_size);
  push(input, strlen(input));

  strncpy(input, "sin", input_size);
  push(input, strlen(input));

  if (stack_size() == 1 && actual_result() == 0.5) { //&&
      //actual_result() < 0.33334) {
    return 0;
  }
  return 1;
}

static int test_cosine_deg() {
  char input[input_size];

  strncpy(input, "deg", input_size);
  push(input, strlen(input));

  strncpy(input, "60", input_size);
  push(input, strlen(input));

  strncpy(input, "cos", input_size);
  push(input, strlen(input));

  if (stack_size() == 1 && actual_result() == 0.5) {
    return 0;
  }
  return 1;
}

static int test_cosine_rad() {
  char input[input_size];

  strncpy(input, "rad", input_size);
  push(input, strlen(input));

  strncpy(input, "pi", input_size);
  push(input, strlen(input));

  strncpy(input, "3", input_size);
  push(input, strlen(input));

  strncpy(input, "/", input_size);
  push(input, strlen(input));

  strncpy(input, "cos", input_size);
  push(input, strlen(input));

  if (stack_size() == 1 && actual_result() > 0.4999 &&
      actual_result() < 0.50001) {
    return 0;
  }
  return 1;
}

static int test_tangent_deg() {
  char input[input_size];

  strncpy(input, "deg", input_size);
  push(input, strlen(input));

  strncpy(input, "45", input_size);
  push(input, strlen(input));

  strncpy(input, "tan", input_size);
  push(input, strlen(input));

  if (stack_size() == 1 && actual_result() == 1.0) {
    return 0;
  }
  return 1;
}

static int test_tangent_rad() {
  char input[input_size];

  strncpy(input, "rad", input_size);
  push(input, strlen(input));

  strncpy(input, "pi", input_size);
  push(input, strlen(input));

  strncpy(input, "4", input_size);
  push(input, strlen(input));

  strncpy(input, "/", input_size);
  push(input, strlen(input));

  strncpy(input, "tan", input_size);
  push(input, strlen(input));

  if (stack_size() == 1 && actual_result() == 1.0) {
    return 0;
  }
  return 1;
}

static int test_asine_deg() {
  char input[input_size];

  strncpy(input, "deg", input_size);
  push(input, strlen(input));

  strncpy(input, "0.5", input_size);
  push(input, strlen(input));

  strncpy(input, "asin", input_size);
  push(input, strlen(input));

  if (stack_size() == 1 && actual_result() == 30) {
    return 0;
  }
  return 1;
}

static int test_asine_rad() {
  char input[input_size];

  strncpy(input, "rad", input_size);
  push(input, strlen(input));

  strncpy(input, "0.5", input_size);
  push(input, strlen(input));

  strncpy(input, "asin", input_size);
  push(input, strlen(input));

  if (stack_size() == 1 && actual_result() >= 0.523598
      && actual_result() <= 0.523600) {
    return 0;
  }
  return 1;
}

static int test_acosine_deg() {
  char input[input_size];

  strncpy(input, "deg", input_size);
  push(input, strlen(input));

  strncpy(input, "0.5", input_size);
  push(input, strlen(input));

  strncpy(input, "acos", input_size);
  push(input, strlen(input));

  if (stack_size() == 1 && actual_result() == 60) {
    return 0;
  }
  return 1;
}

static int test_acosine_rad() {
  char input[input_size];

  strncpy(input, "rad", input_size);
  push(input, strlen(input));

  strncpy(input, "0.5", input_size);
  push(input, strlen(input));

  strncpy(input, "cos", input_size);
  push(input, strlen(input));

  if (stack_size() == 1 && actual_result() >= 0.877582 &&
      actual_result() < 0.877584) {
    return 0;
  }
  return 1;
}

static int test_atangent_deg() {
  char input[input_size];

  strncpy(input, "deg", input_size);
  push(input, strlen(input));

  strncpy(input, "1.0", input_size);
  push(input, strlen(input));

  strncpy(input, "atan", input_size);
  push(input, strlen(input));

  if (stack_size() == 1 && actual_result() == 45) {
    return 0;
  }
  return 1;
}

static int test_atangent_rad() {
  char input[input_size];

  strncpy(input, "rad", input_size);
  push(input, strlen(input));

  strncpy(input, "1.0", input_size);
  push(input, strlen(input));

  strncpy(input, "atan", input_size);
  push(input, strlen(input));

  if (stack_size() == 1 && actual_result() >= 1.557407 &&
      actual_result() <= 1.557409) {
    return 0;
  }
  return 1;
}

// --- CALUCLATOR SETTINGS ---

// --- CONSTANTS ---


// LIST OF TESTS
const static struct {
  const char *name;
  int (*func)(void);

} test_functions [] = {
  // Stack Manipulations
    {"test_duplicate"    , test_duplicate    } ,
    {"test_drop"         , test_drop         } ,
    {"test_swap"         , test_swap         } ,
    {"test_plus"         , test_plus         } ,
    {"test_minus"        , test_minus        } ,
    {"test_neg"          , test_neg          } ,
    {"test_multiply"     , test_multiply     } ,
    {"test_divide"       , test_divide       } ,
    {"test_my_pow"       , test_my_pow       } ,
    {"test_squared"      , test_squared      } ,
    {"test_cubed"        , test_cubed        } ,
    {"test_my_sqrt"      , test_my_sqrt      } ,
    {"test_my_cbrt"      , test_my_cbrt      } ,
    {"test_xrt"          , test_xrt          } ,
    {"test_my_abs"       , test_my_abs       } ,
    {"test_inv"          , test_inv          } ,
    {"test_sine_deg"     , test_sine_deg     } ,
    {"test_sine_rad"     , test_sine_rad     } ,
    {"test_cosine_deg"   , test_cosine_deg   } ,
    {"test_cosine_rad"   , test_cosine_rad   } ,
    {"test_tangent_deg"  , test_tangent_deg  } ,
    {"test_tangent_rad"  , test_tangent_rad  } ,
    {"test_asine_deg"    , test_asine_deg    } ,
    {"test_asine_rad"    , test_asine_rad    } ,
    {"test_acosine_deg"  , test_acosine_deg  } ,
    {"test_acosine_rad"  , test_acosine_rad  } ,
    {"test_atangent_deg" , test_atangent_deg } ,
    {"test_atangent_rad" , test_atangent_rad } ,
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
        printf("%s() FAILED!\n", test_functions[i].name);
      }
      else {
        printf("%s() SUCCEEDED!\n", test_functions[i].name);
      }
    }
    ret = 0;
    stack_init();
  }
  printf("\nNumber of Failed Tests: %d\n", ret);
  return ret;
}
