#ifndef FINAL_CALCULATOR_H
#define FINAL_CALCULATOR_H

#include "models.h"
#include "logs.h"


class Calculator {
public:
    // calculate(): calculate the given expression (should be postfix expression)
    // @exp -> ElementExpression*: the expression to be calculated.
    static double calculate(ElementExpression *exp);
};


#endif //FINAL_CALCULATOR_H
