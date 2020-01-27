#include <vector>
#include <string>
#include <cctype>
#include "convert_expression.h"
#include "ExpressionNodeType.h"
#include "ExpressionNode.h"

/**
 * convert infix-expression to postfix-expression
*/
void convertInfixExpressionToPostfixExpression(std::vector<ExpressionNode> &expressionNodes, std::string expression, unsigned int *i) {
    std::vector<std::string> signs;
    std::string functionName;
    std::string operatorSign;

    while (*i < expression.size() && expression[*i] != ')') {
        functionName = "";
        operatorSign = "";

        switch (expression[*i]) {
            case '0' ... '9':
            case '.':
                if (*i > 0 && (('0' <= expression[(*i) - 1] && expression[(*i) - 1] <= '9') || expression[(*i) - 1] == '.')) {
                    expressionNodes.back().setValue(expressionNodes.back().getValue() + expression[*i]);
                    expressionNodes.back().setType(NUMBER);
                } else {
                    expressionNodes.push_back(ExpressionNode(std::string(1, expression[*i]), NUMBER));
                }

                break;
            
            case 'a' ... 'z':
                while (*i < expression.size() && expression[*i] != '(') {
                    functionName += expression[*i];

                    (*i)++;
                }

                if (functionName == "sqrt") {
                    convertInfixExpressionToPostfixExpression(expressionNodes, expression, i);

                    expressionNodes.push_back(ExpressionNode(std::string("sqrt"), UNARY_OPERATOR));
                }
                
                if (*i <= expression.size()) {
                    (*i)--;
                }

                break;
            
            case '*':
                operatorSign = "";
                while (*i < expression.size() && expression[*i] == '*') {
                    operatorSign += expression[*i];
                    (*i)++;
                }

                (*i)--;

                if (operatorSign == "*") {
                    while (!signs.empty() && (signs.back() == "*" || signs.back() == "/" || signs.back() == "%" || signs.back() == "**")) {
                        expressionNodes.push_back(ExpressionNode(signs.back(), BINARY_OPERATOR));

                        signs.pop_back();
                    }
                }
                
                signs.push_back(operatorSign);

                break;

            case '/':
            case '%':
                while (!signs.empty() && (signs.back() == "*" || signs.back() == "/" || signs.back() == "%" || signs.back() == "**")) {
                    expressionNodes.push_back(ExpressionNode(signs.back(), BINARY_OPERATOR));

                    signs.pop_back();
                }

                signs.push_back(std::string(1, expression[*i]));

                break;
            
            case '+':
            case '-':
                while (!signs.empty()) {
                    expressionNodes.push_back(ExpressionNode(signs.back(), BINARY_OPERATOR));

                    signs.pop_back();
                }

                signs.push_back(std::string(1, expression[*i]));

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
        expressionNodes.push_back(ExpressionNode(signs.back(), BINARY_OPERATOR));
        
        signs.pop_back();
    }
}
