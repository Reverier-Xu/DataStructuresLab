#include "parser.h"

ElementExpression *Parser::stringToExpression(const std::string &exp) {

    // the result expression
    auto *res = new ElementExpression;
    // log(LogLevel::MESSAGE, "when constructed, result's size is", std::to_string(res->size()));

    // the stack to convert the input (infix expression) to @ElementExpression(postfix expression).
    auto *stack = new ElementStack;
    std::string temp; // save the multi number
    for (int i = 0; i < exp.length(); i++) {
        temp = "";
        if (isdigit(exp[i])) {

            // read the entire number.
            while (isdigit(exp[i + 1]) || exp[i + 1] == '.') {
                temp += exp[i];
                i = i + 1;
            }
            temp += exp[i];
            auto e = stringToElement(temp);
            res->append(e);

            // read an operator.
        } else if (exp[i] == '+') {
            auto e = stringToElement("+");

            // pop all operators which priority is greater than current one,
            // append them to the end of result expression,
            // then push current operator into stack.
            while (!stack->empty() && stack->top().getOperator() != '(' && e <= stack->top()) {
                res->append(stack->top());
                stack->pop();
            }
            stack->push(e);
        } else if (exp[i] == '-') {
            auto e = stringToElement("-");
            while (!stack->empty() && stack->top().getOperator() != '(' && e <= stack->top()) {
                res->append(stack->top());
                stack->pop();
            }
            stack->push(e);
        } else if (exp[i] == '*') {
            auto e = stringToElement("*");
            while (!stack->empty() && stack->top().getOperator() != '(' && e <= stack->top()) {
                res->append(stack->top());
                stack->pop();
            }
            stack->push(e);
        } else if (exp[i] == '/') {
            auto e = stringToElement("/");
            while (!stack->empty() && stack->top().getOperator() != '(' && e <= stack->top()) {
                res->append(stack->top());
                stack->pop();
            }
            stack->push(e);

            // if the operator is '(', push it into stack directly.
        } else if (exp[i] == '(') {
            Element e{};
            e.setOperator('(');
            stack->push(e);

            // if the operator is ')', do not put it into expression or stack.
            // we just need pop operators and append them to the expression until we meet '('.
            // then pop the '(' and discard it.
        } else if (exp[i] == ')') {
            while (!stack->empty() && stack->top().getOperator() != '(') {
                res->append(stack->top());
                stack->pop();
            }
            if (!stack->empty()) stack->pop();
            else {

                // if the stack is empty, so it doesn't contains a '('
                throw std::string("could not find a '(' to match the ')'.");
            }
        } else if (exp[i] == ' ') {
            // escape black characters.
            continue;
        } else {
            throw std::string("input contains characters that not recognized.");
        }
        // log(LogLevel::MESSAGE, "after a loop, result's size is", std::to_string(res->size()));
    }

    // append all operators in the stack to expression, and delete the stack.
    while (!stack->empty()) {
        if (stack->top().getOperator() != '(')
            res->append(stack->top());
        stack->pop();
    }
    delete stack;
    return res;
}

Element Parser::stringToElement(const std::string &obj) {
    Element res{};

    // cast the string object to @Element.

    // if it is an operator:
    if (obj.length() == 1 && !isdigit(obj[0])) {
        switch (obj[0]) {
            case '+':
                res.setOperator(ElementOperator::ADD);
                break;
            case '-':
                res.setOperator(ElementOperator::SUBTRACT);
                break;
            case '*':
                res.setOperator(ElementOperator::MULTIPLY);
                break;
            case '/':
                res.setOperator(ElementOperator::DIVIDE);
                break;
            default:
                log(LogLevel::WARNING, "Input letter not recognized.");
                res.setOperator(-1);
        }
        return res;
    } else { // if it is an operand
        try {
            double val = stringToNum(obj);
            res.setValue(val);
        } catch (std::string &e) {
            log(LogLevel::WARNING, "Input letter not recognized", e);
            res.setOperator(-1);
        }
        return res;
    }
}

double Parser::stringToNum(const std::string &obj) {
    int res = 0;
    if (obj.length() <= 0) { return -1; }
    int i;
    for (i = 0; i < obj.length() && obj[i] != '.'; i++) {
        res *= 10;
        res += obj[i] - '0';
    }
    i++;
    int j = 1;
    int min = 0;
    while (i < obj.length()) {
        min *= 10;
        min += obj[i] - '0';
        i++;
        j*=10;
    }
    return double(res) + double(min) / double(j);
}
