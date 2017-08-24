#include "factorial.h"

// Calculating more than 25! is no longer precise, so limit to 25!
#define MAX_FACTORIAL_INPUT 26

// Store Calcuated values here to recall answers quicker.
static long double fact_results[MAX_FACTORIAL_INPUT];

static long double factorial_helper(int x) {
  if (x <= 1) {
    return 1;
  }
  if (x >= MAX_FACTORIAL_INPUT) {
    return -1;
  }
  if (fact_results[x]) {
    return fact_results[x];
  }
  fact_results[x] = x*factorial(x-1);
  return fact_results[x];
}

long double factorial(long double x) {
  if (x >= MAX_FACTORIAL_INPUT) {
    return -1;
  }
  return factorial_helper((int)x);
}
