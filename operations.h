#ifndef _OPERATIONS_H_
#define _OPERATIONS_H_

ret_codes duplicate();
ret_codes drop();
ret_codes plus();
ret_codes minus();
ret_codes multiply();
ret_codes divide();
ret_codes my_sqrt();

int whichOperation(char *s);
ret_codes performOperation(int op);

#endif // _OPERATIONS_H_
