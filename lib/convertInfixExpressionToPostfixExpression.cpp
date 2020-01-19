#include <vector>
#include <string>
#include "convert_expression.h"

/**
 * convert infix-expression to postfix-expression
*/
void convertInfixExpressionToPostfixExpression(std::string *result, std::string expression, unsigned int *i) {
    std::vector<char> signs;

    while (expression[*i] != ')') {
        switch (expression[*i]) {
            case '0' ... '9':
                (*result) += expression[*i];

                break;
            
            case '*':
            case '/':
                while (!signs.empty() && (signs.back() == '*' || signs.back() == '/')) {
                    (*result) += signs.back();

                    signs.pop_back();
                }

                signs.push_back(expression[*i]);

                break;
            
            case '+':
            case '-':
                while (!signs.empty() && (signs.back() == '+' || signs.back() == '-' || signs.back() == '*' || signs.back() == '/')) {
                    (*result) += signs.back();

                    signs.pop_back();
                }

                signs.push_back(expression[*i]);

                break;
            
            case '(':
                (*i)++;

                convertInfixExpressionToPostfixExpression(result, expression, i);
                
                break;

            default:
                break;
        }

        (*i)++;
    }

    while (!signs.empty()) {
        (*result) += signs.back();
        
        signs.pop_back();
    }
}
