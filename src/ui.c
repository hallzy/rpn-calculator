#include "ui.h"
#include "itoa.h"
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

// Clears the screen to keep the UI clean.
static void clear_screen() {
  #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
    system("clear");
  #endif
  #if defined(_WIN32) || defined(_WIN64)
    system("cls");
  #endif

  // Otherwise just leave it
  return;
}


// Print all of my calculator information and stack info.
void print_stack() {
  clear_screen();
  printf("===============================================================\n");
  // Is my calculator in Radians or Degrees?
  if (s.angle_mode == RADIANS) {
    printf("+---+\n");
    printf("|RAD|  DEG\n");
    printf("+---+\n");
  }
  else {
    printf("      +---+\n");
    printf(" RAD  |DEG|\n");
    printf("      +---+\n");
  }

  // What base am I in?
  // Make sure to print the stack info to respect the base.
  if (s.base_mode == HEXADECIMAL) {
    printf("+---+\n");
    printf("|HEX|  DEC   OCT   BIN\n");
    printf("+---+\n");
    printf("\n");
    // Iterate through the whole stack and print out each number as a hex value.
    for (int i = 0; i <= s.top; i++) {
      printf("%d:  %x", i+1, (unsigned int)s.stk[i]);
      printf("\n");
    }
  }
  else if (s.base_mode == DECIMAL) {
    printf("      +---+\n");
    printf(" HEX  |DEC|  OCT   BIN\n");
    printf("      +---+\n");
    printf("\n");
    // Iterate through the whole stack and print out each number as a decimal
    // value.
    for (int i = 0; i <= s.top; i++) {
      printf("%d:  %Lf", i+1, s.stk[i]);
      printf("\n");
    }
  }
  else if (s.base_mode == OCTAL) {
    printf("            +---+\n");
    printf(" HEX   DEC  |OCT|  BIN\n");
    printf("            +---+\n");
    printf("\n");
    // Iterate through the whole stack and print out each number as an octal
    // value.
    for (int i = 0; i <= s.top; i++) {
      printf("%d:  %o", i+1, (unsigned int)s.stk[i]);
      printf("\n");
    }
  }
  else {
    printf("                  +---+\n");
    printf(" HEX   DEC   OCT  |BIN|\n");
    printf("                  +---+\n");
    printf("\n");
    // Iterate through the whole stack and print out each number as a binary
    // value.
    for (int i = 0; i <= s.top; i++) {
      // I need to use itoa to do this since C doesn't have any built-in way to
      // print binary numbers
      // This converts the number into a string represented as a binary number
      char buf[128];
      itoa((unsigned int)s.stk[i], buf, 2);
      printf("%d:  %s", i+1, buf);
      printf("\n");
    }
  }
  printf("===============================================================\n");
}
