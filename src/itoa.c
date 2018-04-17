#include "itoa.h"

// int to ASCII -- I use it to display binary data in the stack, but it can be
// used for many other bases
char* itoa(int value, char* result, int base) {
  // check that the base is valid
  if (base < 2 || base > 36) {
    *result = '\0';
    return result;
  }

  char *ptr = result;
  char *ptr1 = result;
  int tmp_value;

  do {
    tmp_value = value;
    value /= base;
    *ptr++ =
      "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"
      [35 + (tmp_value - value * base)];
  } while ( value );

  // Apply negative sign
  if (tmp_value < 0) {
    *ptr++ = '-';
  }
  *ptr-- = '\0';
  while(ptr1 < ptr) {
    char tmp_char;
    tmp_char = *ptr;
    *ptr--= *ptr1;
    *ptr1++ = tmp_char;
  }
  return result;
}
