#pragma once
#define _EXPRESSION_NODE_H_

#include <string>
#include "ExpressionNodeType.h"

class ExpressionNode {
    private:
        std::string value;
        enum ExpressionNodeType type;
    
    public:
        ExpressionNode(std::string value, enum ExpressionNodeType type) {
            this->value = value;
            this->type = type;
        }

        std::string getValue();
        void setValue(std::string);

        enum ExpressionNodeType getType();
        void setType(enum ExpressionNodeType);
};
