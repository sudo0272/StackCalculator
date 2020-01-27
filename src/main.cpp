#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "../lib/convert_expression.h"
#include "../lib/ExpressionNodeType.h"
#include "../lib/ExpressionNode.h"

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
    convertInfixExpressionToPostfixExpression(expressionNodes, expression, &index);

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

            calculateStack.push_back(ExpressionNode(std::to_string(operateResult), NUMBER));

            break;
        
        case UNARY_OPERATOR:
            operands[0] = std::stod(calculateStack.back().getValue());
            calculateStack.pop_back();

            if ((*i).getValue() == "sqrt") {
                operateResult = sqrt(operands[0]);
            }

            calculateStack.push_back(ExpressionNode(std::to_string(operateResult), NUMBER));

        default:
            break;
        }
    }

    std::cout << "= " << calculateStack[0].getValue() << std::endl;

    return 0;
}
