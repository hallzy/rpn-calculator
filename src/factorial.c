#include <limits.h>
#include "factorial.h"


// Calculating more than 34 results in inf anyways, so no point in going bigger.
#define MAX_FACTORIAL_INPUT 36

// Store Calcuated values here to recall answers quicker.
static float fact_results[MAX_FACTORIAL_INPUT];

float factorial(int x) {
  if (x <= 1) {
    return 1;
  }
  if (x >= MAX_FACTORIAL_INPUT) {
    return factorial(35);
  }
  if (fact_results[x]) {
    return fact_results[x];
  }
  fact_results[x] = x*factorial(x-1);
  return fact_results[x];

}
