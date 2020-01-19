#pragma once
#define _CONVERT_EXPRESSION_H_

#include <string>
#include <vector>
#include "ExpressionNodeType.h"
#include "ExpressionNode.h"

void convertInfixExpressionToPostfixExpression(std::vector<ExpressionNode> &, std::string, unsigned int *);
