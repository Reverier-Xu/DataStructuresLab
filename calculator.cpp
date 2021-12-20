#include "calculator.h"


// calc(): calculate the two elements with the given operator.
// @x -> Element: Operand1
// @op -> Element: Operator
// @y -> Element: Operand2
// tips: this function can just be called by the function at this source file.
Element calc(Element x, Element op, Element y) {

    // get the Operator
    auto opc = (ElementOperator)op.getOperator();
    Element res{};

    // calculate
    switch (opc) {
        case ADD:
            res.setValue(x.getValue()+y.getValue());
            break;
        case SUBTRACT:
            res.setValue(x.getValue()-y.getValue());
            break;
        case MULTIPLY:
            res.setValue(x.getValue()*y.getValue());
            break;
        case DIVIDE:
            res.setValue(x.getValue()/y.getValue());
            break;
        default:
            // the Operator is not support.
            throw std::string("operator not support.");
    }
    return res;
}

double Calculator::calculate(ElementExpression *exp) {
    ElementStack stack;
    for (int i = 0; i < exp->size(); i++) {
        // get the current item.
        // because the function ElementExpression::operator[]() is O(n), so we
        // assign @crt to reduce the call times of this function.
        auto crt = (*exp)[i];

        // if current element is an operand, push it into stack directly.
        if (crt.getElementType() == ElementType::OPERAND) {
            stack.push(crt);
        } else { // else if the current element is an operator, we should get the operand
                 // from stack, calculate it and push the result into stack.

            // if the stack is empty, the operator has no operands.
            // so the expression must be illegal.
            if (stack.empty()) {
                throw std::string("expression is illegal.");
            }

            // get the first operand.
            // if we input x-y, the postfix expression is < x y - >,
            // and x will be pushed into stack first, so when we get the operator '-',
            // the stack top is 'y'.
            Element y = stack.top();
            stack.pop();

            // if there is just one operand to operate
            if (stack.empty() && crt.getOperator() == ElementOperator::SUBTRACT) {
                y.setValue(-y.getValue());
                stack.push(y);
            } else if (stack.empty() && crt.getOperator() == ElementOperator::ADD) {
                stack.push(y);
            } else if (stack.empty()) {
                // other operators like '*' and '/' couldn't work with single operand.
                throw std::string("expression is illegal.");
            } else {

                // get another operand, calculate the result, then push result into stack.
                Element x = stack.top();
                stack.pop();
                stack.push(calc(x, crt, y));
            }
        }
    }
    // there should be only one element in the stack, this element is the final answer.
    Element res = stack.top();
    stack.pop();
    if (!stack.empty()) { // if stack is not empty, there must be some errors in the expression.
        throw std::string("expression is illegal.");
    }

    // return the value as double variable.
    return res.getValue();
}
