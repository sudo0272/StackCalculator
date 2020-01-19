#include <iostream>
#include <string>
#include "../lib/convert_expression.h"

int main() {
    std::string expression;
    std::string result;
    unsigned int i;
    
    std::getline(std::cin, expression);

    // convert infix expression to postfix expression
    convertInfixExpressionToPostfixExpression(&result, expression, &i);

    std::cout << result << std::endl;

    return 0;
}
