//
// Created by reverier on 2020/12/21.
//

#ifndef FINAL_PARSER_H
#define FINAL_PARSER_H

#include "models.h"
#include "logs.h"

class Parser {
public:

    // stringToExpression(): this function convert the
    // input string into a postfix expression.
    // @exp -> std::string&: the input string.
    static ElementExpression* stringToExpression(const std::string& exp);

    // stringToElement(): this function convert a string to an element.
    // @obj -> std::string&: the input string.
    static Element stringToElement(const std::string& obj);

    // stringToNum(): this function convert a string into number.
    // @obj -> std::string&: the input string.
    // this function supports float numbers.
    static double stringToNum(const std::string& obj);
};


#endif //FINAL_PARSER_H
