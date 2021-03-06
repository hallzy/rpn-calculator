#ifndef _OPERATIONS_H_
#define _OPERATIONS_H_

/* ret_codes rpn_calc_help(); */

typedef struct {
  int operation_type_index;
  int operation_index;
} operation_location;

// Determines if the input to the calculator is an operation, and if it is,
// returns the index of that operation
operation_location whichOperation(char *op_string);

#ifndef TEST
ret_codes help();
#endif // TEST

// This function executes the operation with the index of op (returned from
// whichOperation())
ret_codes performOperation(operation_location op);

#endif // _OPERATIONS_H_
