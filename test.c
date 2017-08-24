#include <stdio.h>
#include <string.h>

#include "stack.h"
#include "test.h"

#define input_size 128

static float actual_result() {
  return s.stk[s.top];
}

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



// LIST OF TESTS
const static struct {
  const char *name;
  int (*func)(void);

} test_functions [] = {
  // Stack Manipulations
    {"test_duplicate"   , test_duplicate } ,
    {"test_drop"        , test_drop      } ,
    {"test_swap"        , test_swap      } ,
    {"test_plus"        , test_plus      } ,
    {"test_minus"       , test_minus     } ,
    {"test_neg"         , test_neg       } ,
    {"test_multiply"    , test_multiply  } ,
    {"test_divide"      , test_divide    } ,
    {"test_my_pow"      , test_my_pow    } ,
    {"test_squared"     , test_squared   } ,
    {"test_cubed"       , test_cubed     } ,
    {"test_my_sqrt"     , test_my_sqrt   } ,
    {"test_my_cbrt"     , test_my_cbrt   } ,
    {"test_xrt"         , test_xrt       } ,
    {"test_my_abs"      , test_my_abs    } ,
    {"test_inv"         , test_inv       } ,
  };

// PERFORM THE TESTS
int performTests() {
  stack_init();

  // Ret holds the number of failed tests
  int ret = 0;

  int num_of_tests = sizeof(test_functions)/sizeof(test_functions[0]);

  for (int i = 0; i < num_of_tests; i++) {
    if (test_functions[i].func) {
      if (ret += test_functions[i].func()) {
        printf("%s() FAILED!\n", test_functions[i].name);
      }
      else {
        printf("%s() SUCCEEDED!\n", test_functions[i].name);
      }
    }
    stack_init();
  }
  printf("\nNumber of Failed Tests: %d\n", ret);
  return ret;
}
