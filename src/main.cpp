#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "../lib/convert_expression.h"
#include "../lib/ExpressionNodeType.h"
#include "../lib/ExpressionNode.h"
#include "../lib/Exceptions.h"

int main() {
    std::string expression;
    std::vector<ExpressionNode> expressionNodes;
    std::vector<ExpressionNode> calculateStack;
    unsigned int index = 0;
    double operands[2];
    double operateResult;
    
    std::getline(std::cin, expression);

    expression += ')';

    // convert infix expression to postfix expression
    try {
        convertInfixExpressionToPostfixExpression(expressionNodes, &expression, &index);
    } catch (Exceptions::Parsing::BracketNotMatchError &e) {
        std::cerr << e.what() << std::endl;

        return ENOEXEC;
    } catch (Exceptions::Parsing::UnknownOperatorError &e) {
        std::cerr << e.what() << std::endl;

        return ENOEXEC;
    } catch (Exceptions::Parsing::UnknownFunctionError &e) {
        std::cerr << e.what() << std::endl;

        return ENOEXEC;
    } catch (Exceptions::Parsing::AbnormalFloatingNumberFormatError &e) {
        std::cerr << e.what() << std::endl;

        return ENOEXEC;
    } catch (Exceptions::Parsing::NoOperatorError &e) {
        std::cerr << e.what() << std::endl;

        return ENOEXEC;
    } catch (Exceptions::Parsing::NoOperandError &e) {
        std::cerr << e.what() << std::endl;

        return ENOEXEC;
    }

    for (int i = 0; i < expressionNodes.size(); i++) {
        std::cout << expressionNodes[i].getValue() << ' ';
    }

    std::cout << std::endl;

    for (auto i = expressionNodes.begin(); i != expressionNodes.end(); i++) {
        switch ((*i).getType()) {
        case NUMBER:
            calculateStack.push_back(*i);
            
            break;
        
        case BINARY_OPERATOR:
            if (calculateStack.size() < 2) {
                try {
                    throw Exceptions::Runtime::NoOperandError();
                } catch (Exceptions::Runtime::NoOperandError &e) {
                    std::cerr << e.what() << std::endl;

                    return ENOSPC;
                }
            }

            operands[1] = std::stod(calculateStack.back().getValue());
            calculateStack.pop_back();

            operands[0] = std::stod(calculateStack.back().getValue());
            calculateStack.pop_back();

                 if ((*i).getValue() == "*") operateResult = operands[0] * operands[1];
            else if ((*i).getValue() == "/") operateResult = operands[0] / operands[1];
            else if ((*i).getValue() == "%") operateResult = std::fmod(operands[0], operands[1]);
            else if ((*i).getValue() == "+") operateResult = operands[0] + operands[1];
            else if ((*i).getValue() == "-") operateResult = operands[0] - operands[1];
            else if ((*i).getValue() == "**") operateResult = pow(operands[0], operands[1]);
            else if ((*i).getValue() == "//") operateResult = floor(operands[0] / operands[1]);
            else {
                try {
                    throw Exceptions::Parsing::UnknownOperatorError((*i).getValue());
                } catch (Exceptions::Parsing::UnknownOperatorError &e) {
                    std::cerr << e.what() << std::endl;

                    return ENOEXEC;
                }
            }

            calculateStack.push_back(ExpressionNode(std::to_string(operateResult), NUMBER));

            break;
        
        case FUNCTION:
                if (calculateStack.size() < 1) {
                    try {
                        throw Exceptions::Runtime::NoOperandError();
                    } catch (Exceptions::Runtime::NoOperandError &e) {
                        std::cerr << e.what() << std::endl;

                        return ENOSPC;
                    }
                }

            operands[0] = std::stod(calculateStack.back().getValue());
            calculateStack.pop_back();

            if ((*i).getValue() == "sqrt") {
                if (operands[0] >= 0) { // if operand is positive number
                    operateResult = sqrt(operands[0]);
                } else {
                    try {
                        throw Exceptions::Runtime::ComplexError();
                    } catch(Exceptions::Runtime::ComplexError &e) {
                        std::cerr << e.what() << std::endl;

                        return ERANGE;
                    }
                }
            }

            calculateStack.push_back(ExpressionNode(std::to_string(operateResult), NUMBER));

        default:
            break;
        }
    }

    std::cout << "= " << calculateStack[0].getValue() << std::endl;

    return 0;
}
