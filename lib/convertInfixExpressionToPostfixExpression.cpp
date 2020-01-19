#include <vector>
#include <string>
#include "convert_expression.h"
#include "ExpressionNodeType.h"
#include "ExpressionNode.h"

/**
 * convert infix-expression to postfix-expression
*/
void convertInfixExpressionToPostfixExpression(std::vector<ExpressionNode> &expressionNodes, std::string expression, unsigned int *i) {
    std::vector<char> signs;

    while (expression[*i] != ')') {
        switch (expression[*i]) {
            case '0' ... '9':
                if (*i > 0 && '0' <= expression[*i] && expression[*i] <= '9') {
                    expressionNodes.back().setValue(expressionNodes.back().getValue() + expression[*i]);
                } else {
                    expressionNodes.push_back(ExpressionNode(std::string(1, expression[*i]), NUMBER));
                }

                break;
            
            case '*':
            case '/':
                while (!signs.empty() && (signs.back() == '*' || signs.back() == '/')) {
                    expressionNodes.push_back(ExpressionNode(std::string(1, signs.back()), SIGN));

                    signs.pop_back();
                }

                signs.push_back(expression[*i]);

                break;
            
            case '+':
            case '-':
                while (!signs.empty() && (signs.back() == '+' || signs.back() == '-' || signs.back() == '*' || signs.back() == '/')) {
                    expressionNodes.push_back(ExpressionNode(std::string(1, signs.back()), SIGN));

                    signs.pop_back();
                }

                signs.push_back(expression[*i]);

                break;
            
            case '(':
                (*i)++;

                convertInfixExpressionToPostfixExpression(expressionNodes, expression, i);
                
                break;

            default:
                break;
        }

        (*i)++;
    }

    while (!signs.empty()) {
        expressionNodes.push_back(ExpressionNode(std::string(1, signs.back()), SIGN));
        
        signs.pop_back();
    }
}
