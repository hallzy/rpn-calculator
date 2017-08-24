#ifndef _OPERATIONS_H_
#define _OPERATIONS_H_

// Determines if the input to the calculator is an operation, and if it is,
// returns the index of that operation
int whichOperation(char *s);

// This function executes the operation with the index of op (returned from
// whichOperation())
ret_codes performOperation(int op);

#endif // _OPERATIONS_H_
