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
    std::string currentString;
    enum ExpressionNodeType lastestStackedElementType;

    while (*i < expression.size() && expression[*i] != ')') {
        currentString = "";

        switch (expression[*i]) {
            case '0' ... '9':
            case '.':
                while (*i < expression.size() && (isdigit(expression[*i]) || expression[*i] == '.')) {
                    currentString += expression[*i];

                    (*i)++;
                }

                (*i)--;

                expressionNodes.push_back(ExpressionNode(currentString, NUMBER));

                lastestStackedElementType = NUMBER;

                break;
            
            case 'a' ... 'z':
                while (*i < expression.size() && expression[*i] != '(') {
                    currentString += expression[*i];

                    (*i)++;
                }

                if (currentString == "sqrt") {
                    convertInfixExpressionToPostfixExpression(expressionNodes, expression, i);

                    expressionNodes.push_back(ExpressionNode(std::string("sqrt"), UNARY_OPERATOR));
                }
                
                if (*i <= expression.size()) {
                    (*i)--;
                }

                lastestStackedElementType = FUNCTION;

                break;
            
            case '*':
                while (*i < expression.size() && expression[*i] == '*') {
                    currentString += expression[*i];
                    (*i)++;
                }

                (*i)--;

                if (currentString == "*") {
                    while (!signs.empty() && (signs.back() == "*" || signs.back() == "/" || signs.back() == "%" || signs.back() == "**")) {
                        expressionNodes.push_back(ExpressionNode(signs.back(), BINARY_OPERATOR));

                        signs.pop_back();
                    }
                }
                
                signs.push_back(currentString);

                lastestStackedElementType = BINARY_OPERATOR;

                break;

            case '/':
            case '%':
                while (!signs.empty() && (signs.back() == "*" || signs.back() == "/" || signs.back() == "%" || signs.back() == "**")) {
                    expressionNodes.push_back(ExpressionNode(signs.back(), BINARY_OPERATOR));

                    signs.pop_back();
                }

                signs.push_back(std::string(1, expression[*i]));

                lastestStackedElementType = BINARY_OPERATOR;

                break;
            
            case '+':
                while (!signs.empty()) {
                    expressionNodes.push_back(ExpressionNode(signs.back(), BINARY_OPERATOR));

                    signs.pop_back();
                }

                lastestStackedElementType = BINARY_OPERATOR;

                signs.push_back(std::string(1, expression[*i]));

                break;

            case '-':
                if (lastestStackedElementType != NUMBER) {
                    currentString = "-";

                    (*i)++;

                    while (*i < expression.size() && (isdigit(expression[*i]) || expression[*i] == '.')) {
                        currentString += expression[*i];

                        (*i)++;
                    }

                    (*i)--;
                    
                    lastestStackedElementType = NUMBER;

                    expressionNodes.push_back(ExpressionNode(currentString, NUMBER));
                } else {
                    while (!signs.empty()) {
                        expressionNodes.push_back(ExpressionNode(signs.back(), BINARY_OPERATOR));

                        signs.pop_back();
                    }

                    lastestStackedElementType = BINARY_OPERATOR;

                    signs.push_back(std::string(1, expression[*i]));
                }

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
