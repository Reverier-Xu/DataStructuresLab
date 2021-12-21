#include <iostream>
#include "parser.h"
#include "models.h"
#include "calculator.h"
#include "logs.h"

// read a expression with regulations of the subject.
std::string read_exp(){
    std::string res = "";
    char buf;
    while (true) {
        buf = getchar();
        if (buf == '\n' || buf == '\r') break; // skip the return character.
        res += buf;
    }
    return res;
}

int main() {
    // show welcome information.
    std::cout << "Welcome to Simple Calculator.\n"
                 "Type '\033[31mexit\033[0m' to exit the program.\n\n";
    std::string input;
    double res;
    while (true) { // infinity loop, until user input 'exit'
        std::cout << "[\033[32m In\033[0m]: ";
        input = read_exp();
        // log(LogLevel::MESSAGE, "your input is", input);
        if (input == "exit") { // exit
            std::cout << "Bye.\n\n";
            exit(0);
        }
        try { // proceed the input
            ElementExpression* p = Parser::stringToExpression(input);
            res = Calculator::calculate(p);
            delete p;
            std::cout << "[\033[36mOut\033[0m]: " << input << " = " << res << std::endl << std::endl;
        } catch (std::runtime_error& e) {
            log(LogLevel::ERROR, e.what()); // log the error.
        }
    }
}
