#ifndef _EXPR_H_
#define _EXPR_H_

#include "stack.h"
#include "bool.h"

#define EXPRESSION_CHAR 'e'

bool expression_is_running;

ret_codes parseExpression(char *val);

#endif // _EXPR_H_
