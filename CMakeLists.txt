project(StackCalculator)
cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES src/main.cpp lib/convert_expression.h lib/convertInfixExpressionToPostfixExpression.cpp)

add_executable(StackCalculator ${SOURCE_FILES})
