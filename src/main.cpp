#include <iostream>
#include <string>
#include <vector>
#include "../lib/convert_expression.h"
#include "../lib/ExpressionNodeType.h"
#include "../lib/ExpressionNode.h"

int main() {
    std::string expression;
    std::vector<ExpressionNode> expressionNodes;
    unsigned int i = 0;
    
    std::getline(std::cin, expression);

    expression += ')';

    // convert infix expression to postfix expression
    convertInfixExpressionToPostfixExpression(expressionNodes, expression, &i);

    for (i = 0; i < expressionNodes.size(); i++) {
        std::cout << expressionNodes[i].getValue() << ' ';
    }

    std::cout << std::endl;

    return 0;
}
