#ifndef _STACK_H_
#define _STACK_H_

#define MAX_STK 128

typedef enum {
  SUCCESS,
  NOTHING_TO_PUSH,
  FAILED_TO_PUSH,
  FAILED_OPERATION,
} ret_codes;

typedef struct {
  float stk[MAX_STK];
  int top;
  int rad_mode;
} stack;

stack s;

ret_codes push(char *val, int val_size);
float  pop();
void stack_init();
int stack_size();
void add_to_stack(float f);
void print_stack();

#endif // _STACK_H_
