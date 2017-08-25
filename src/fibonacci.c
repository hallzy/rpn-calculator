#include "fibonacci.h"

// Calculating more than fib(92) is no longer precise, so limit to fib(92)
#define MAX_FIBONACCI_INPUT 93

// Store Calcuated values here to recall answers quicker.
static long double fib_results[MAX_FIBONACCI_INPUT];

static long long fib_helper(int x) {
  if (x <= 0) {
    return 0;
  }
  if (x == 1) {
    return 1;
  }
  if (x >= MAX_FIBONACCI_INPUT) {
    return -1;
  }
  if (fib_results[x]) {
    return fib_results[x];
  }
  fib_results[x] = fibonacci(x-1) + fibonacci(x-2);
  return fib_results[x];
}

// This is the function that is called. It takes the argument in as a long
// double so that we can check it before casting it. This will help to prevent
// overflows.
long double fibonacci(long double x) {
  if (x >= MAX_FIBONACCI_INPUT) {
    return -1;
  }
  return fib_helper((int)x);
}
