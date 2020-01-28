#pragma once
#define _EXPRESSION_NODE_TYPE_H_

enum ExpressionNodeType {
    BEGINNING,
    NUMBER,
    BINARY_OPERATOR,
    UNARY_OPERATOR,
    FUNCTION
};
