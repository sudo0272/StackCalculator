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
    bool hasDecimalPoint;

    while (*i < expression->size() && (*expression)[*i] != ')') {
        currentString = "";
        hasDecimalPoint = false;

        // TODO: throw exception when operator or number appears twice
        switch ((*expression)[*i]) {
            case '0' ... '9':
            case '.':
                if (lastestStackedElementType == NUMBER) {
                    throw Exceptions::Parsing::NoOperatorError();
                }

                while (*i < expression->size() && (isdigit((*expression)[*i]) || (*expression)[*i] == '.')) {
                    currentString += (*expression)[*i];

                    if ((*expression)[*i] == '.') {
                        if (hasDecimalPoint) {
                            throw Exceptions::Parsing::AbnormalFloatingNumberFormatError();
                        } else {
                            hasDecimalPoint = true;
                        }
                    }

                    (*i)++;
                }

                (*i)--;

                expressionNodes.push_back(ExpressionNode(currentString, NUMBER));

                lastestStackedElementType = NUMBER;

                break;
            
            case 'A' ... 'Z':
            case 'a' ... 'z':
                // TODO: distinguish functions and variables
                while (*i < expression->size() && isalpha((*expression)[*i])) {
                    currentString += (*expression)[*i];

                    (*i)++;
                }

                if (currentString == "sqrt") {
                    convertInfixExpressionToPostfixExpression(expressionNodes, expression, i);

                    expressionNodes.push_back(ExpressionNode(std::string("sqrt"), FUNCTION));
                } else {
                    throw Exceptions::Parsing::UnknownFunctionError(currentString);
                }
                
                if (*i <= expression->size()) {
                    (*i)--;
                }

                lastestStackedElementType = FUNCTION;

                break;
            
            case '*':
                if (lastestStackedElementType == BINARY_OPERATOR) {
                    throw Exceptions::Parsing::NoOperandError();
                }

                while (*i < expression->size() && (*expression)[*i] == '*') {
                    currentString += (*expression)[*i];
                    (*i)++;
                }

                (*i)--;

                while (!signs.empty() && (signs.back() == "*" || signs.back() == "/" || signs.back() == "%" || signs.back() == "**" || signs.back() == "//")) {
                    expressionNodes.push_back(ExpressionNode(signs.back(), BINARY_OPERATOR));

                    signs.pop_back();
                }
                
                signs.push_back(currentString);

                lastestStackedElementType = BINARY_OPERATOR;

                break;

            case '/':
                if (lastestStackedElementType == BINARY_OPERATOR) {
                    throw Exceptions::Parsing::NoOperandError();
                }

                while (*i < expression->size() && (*expression)[*i] == '/') {
                    currentString += (*expression)[*i];
                    (*i)++;
                }

                (*i)--;

                while (!signs.empty() && (signs.back() == "*" || signs.back() == "/" || signs.back() == "%" || signs.back() == "**" || signs.back() == "//")) {
                    expressionNodes.push_back(ExpressionNode(signs.back(), BINARY_OPERATOR));

                    signs.pop_back();
                }
                
                signs.push_back(currentString);

                lastestStackedElementType = BINARY_OPERATOR;

                break;

            case '%':
                if (lastestStackedElementType == BINARY_OPERATOR) {
                    throw Exceptions::Parsing::NoOperandError();
                }

                while (!signs.empty() && (signs.back() == "*" || signs.back() == "/" || signs.back() == "%" || signs.back() == "**" || signs.back() == "//")) {
                    expressionNodes.push_back(ExpressionNode(signs.back(), BINARY_OPERATOR));

                    signs.pop_back();
                }

                signs.push_back(std::string(1, (*expression)[*i]));

                lastestStackedElementType = BINARY_OPERATOR;

                break;
            
            case '+':
                if (lastestStackedElementType == BINARY_OPERATOR) {
                    throw Exceptions::Parsing::NoOperandError();
                }

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
                } else if (lastestStackedElementType == BINARY_OPERATOR) {
                    throw Exceptions::Parsing::NoOperandError();
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
