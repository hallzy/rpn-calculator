#ifndef _STACK_H_
#define _STACK_H_

#define MAX_STK 128

typedef enum {
  FLOAT,
  PLUS,
  MINUS,
  MULT,
  DIV
} input_type;

typedef enum {
  SUCCESS,
  NOTHING_TO_PUSH,
  FAILED_TO_PUSH,
  FAILED_OPERATION,
} ret_codes;

typedef struct {
  float stk[MAX_STK];
  int top;
} stack;

stack s;

ret_codes push(char *val, int val_size);
float  pop();
void stack_init();
void add_to_stack(float f);
void print_stack();
/* int isNumber(char *s, int s_len); */

#endif // _STACK_H_
