#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "Pile.h"
#include <string>
#include <stdexcept>

template <typename T>
class Expression {
public:
    bool checkEquation(const string& expr);
    double solveEquation(const string& expr);
    double appliquerOperation(double a, double b, char op);
    int precedence(char op) const;
};

#endif // EXPRESSION_H
