#ifndef _STACK_H_
#define _STACK_H_

// Defines the maximum size of the stack which is completely arbitrary. Doubt I
// will need it bigger. To emulate the feel of a scientific RPN calculator you
// can reduce this to something like 4.
#define MAX_STK 128

// Return codes used for several functions just to make it clear what is being
// returned.
typedef enum {
  SUCCESS,
  NOTHING_TO_PUSH,
  FAILED_TO_PUSH,
  FAILED_OPERATION,
} ret_codes;

typedef enum {
  RADIANS,
  DEGREES,
} angle_modes;

typedef enum {
  HEXADECIMAL,
  DECIMAL,
  OCTAL,
  BINARY,
} base_modes;

// All the elements of the stack.
// angle_modes and base_modes are here also because depending on their state,
// they affect how the stack looks.
typedef struct {
  long double stk[MAX_STK];
  // if top == -1, the stack is empty. It is this way because it makes using it
  // in arrays easier, as if there is 1 element top is 0.
  int top;
  angle_modes angle_mode;
  base_modes base_mode;
} stack;

// This is a high level function that sends a user inputed string to be parsed.
// If the string is found to be a number, it is pushed to the stack, otherwise
// it finds the operation that was specified, or fails.
ret_codes processUserInput(char *val, int val_size);

// Functions to set the base and angle of the stack
void set_angle_mode(angle_modes angle);
void set_base_mode(base_modes base);

// Functions to get the base and angle of the stack
angle_modes get_angle_mode();
base_modes get_base_mode();

// Return the value on the stack at index i
long double get_stack_value_at_index(int i);

// Set Stack Size, so long as it is a lower value than the current s.top
void set_stack_size(int size);

// This takes a value off the stack and reduces s.top to move the stack pointer
long double  pop();

// Initializes the elements of the stack.
void stack_init();

// just changes s.top into a more reasonable number for determining size
int get_stack_size();

// Adds a new number to the stack and increments s.top stack pointer
void push(long double f);

// Removes the stack element at index j and reorganizes the stack.
void remove_from_stack_index(unsigned int j);

#endif // _STACK_H_
