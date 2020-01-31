#include <vector>
#include <string>
#include <cctype>
#include "convert_expression.h"
#include "ExpressionNodeType.h"
#include "ExpressionNode.h"
#include "Exceptions.h"

/**
 * convert infix-expression to postfix-expression
*/
void convertInfixExpressionToPostfixExpression(std::vector<ExpressionNode> &expressionNodes, std::string *expression, unsigned int *i) {
    std::vector<std::string> signs;
    std::string currentString;
    enum ExpressionNodeType lastestStackedElementType = BEGINNING;

    while (*i < expression->size() && (*expression)[*i] != ')') {
        currentString = "";

        // TODO: throw exception when operator or number appears twice
        switch ((*expression)[*i]) {
            case '0' ... '9':
            case '.':
                // TODO: throw exception when number is not matched with floating number's format
                while (*i < expression->size() && (isdigit((*expression)[*i]) || (*expression)[*i] == '.')) {
                    currentString += (*expression)[*i];

                    (*i)++;
                }

                (*i)--;

                expressionNodes.push_back(ExpressionNode(currentString, NUMBER));

                lastestStackedElementType = NUMBER;

                break;
            
            case 'a' ... 'z':
                // TODO: distinguish functions and variables
                // TODO: throw Exceptions::Parsing::BracketNotMatchError
                while (*i < expression->size() && (*expression)[*i] != '(') {
                    currentString += (*expression)[*i];

                    (*i)++;
                }

                if (currentString == "sqrt") {
                    convertInfixExpressionToPostfixExpression(expressionNodes, expression, i);

                    expressionNodes.push_back(ExpressionNode(std::string("sqrt"), UNARY_OPERATOR));
                }
                
                if (*i <= expression->size()) {
                    (*i)--;
                }

                lastestStackedElementType = FUNCTION;

                break;
            
            case '*':
                while (*i < expression->size() && (*expression)[*i] == '*') {
                    currentString += (*expression)[*i];
                    (*i)++;
                }

                (*i)--;

                if (currentString == "*") {
                    while (!signs.empty() && (signs.back() == "*" || signs.back() == "/" || signs.back() == "%" || signs.back() == "**" || signs.back() == "//")) {
                        expressionNodes.push_back(ExpressionNode(signs.back(), BINARY_OPERATOR));

                        signs.pop_back();
                    }
                }
                
                signs.push_back(currentString);

                lastestStackedElementType = BINARY_OPERATOR;

                break;

            case '/':
                while (*i < expression->size() && (*expression)[*i] == '/') {
                    currentString += (*expression)[*i];
                    (*i)++;
                }

                (*i)--;

                if (currentString == "*") {
                    while (!signs.empty() && (signs.back() == "*" || signs.back() == "/" || signs.back() == "%" || signs.back() == "**" || signs.back() == "//")) {
                        expressionNodes.push_back(ExpressionNode(signs.back(), BINARY_OPERATOR));

                        signs.pop_back();
                    }
                }
                
                signs.push_back(currentString);

                lastestStackedElementType = BINARY_OPERATOR;

                break;

            case '%':
                while (!signs.empty() && (signs.back() == "*" || signs.back() == "/" || signs.back() == "%" || signs.back() == "**" || signs.back() == "//")) {
                    expressionNodes.push_back(ExpressionNode(signs.back(), BINARY_OPERATOR));

                    signs.pop_back();
                }

                signs.push_back(std::string(1, (*expression)[*i]));

                lastestStackedElementType = BINARY_OPERATOR;

                break;
            
            case '+':
                while (!signs.empty()) {
                    expressionNodes.push_back(ExpressionNode(signs.back(), BINARY_OPERATOR));

                    signs.pop_back();
                }

                lastestStackedElementType = BINARY_OPERATOR;

                signs.push_back(std::string(1, (*expression)[*i]));

                break;

            case '-':
                if (lastestStackedElementType != NUMBER || lastestStackedElementType == BEGINNING) {
                    currentString = "-";

                    (*i)++;

                    while (*i < expression->size() && (isdigit((*expression)[*i]) || (*expression)[*i] == '.')) {
                        currentString += (*expression)[*i];

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

                    signs.push_back(std::string(1, (*expression)[*i]));
                }

                break;
            
            case '(':
                (*i)++;

                convertInfixExpressionToPostfixExpression(expressionNodes, expression, i);
                
                break;

            default:
                if ((*expression)[*i] != ' ') {
                    throw Exceptions::Parsing::UnknownOperatorError(std::string(1, (*expression)[*i]));
                }
                
                break;
        }

        (*i)++;
    }

    if (*i == expression->size() && (*expression)[*i] != ')') { // if upper while loop hasn't been finished beause the bracket has matched
        throw Exceptions::Parsing::BracketNotMatchError();
    }

    while (!signs.empty()) {
        expressionNodes.push_back(ExpressionNode(signs.back(), BINARY_OPERATOR));
        
        signs.pop_back();
    }
}
