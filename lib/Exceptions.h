#pragma once
#define _EXCEPTIONS_H_

#include <string>
#include <sstream>
#include <exception>

class Exceptions:public std::exception {
    public:
        class Parsing {
            public:
                class BracketNotMatchError {
                    public:
                        const std::string what() const throw() {
                            return "Bracket is not matched";
                        }
                };

                class UnknownOperatorError {
                    private:
                        std::string operatorSign;

                    public:
                        UnknownOperatorError(std::string operatorSign) {
                            this->operatorSign = operatorSign;
                        }

                        const std::string what() const throw() {
                            std::stringstream errorMessage;

                            errorMessage << "Operator " << this->operatorSign << " is unknown";

                            return errorMessage.str();
                        }
                };

                class UnknownFunctionError {
                    private:
                        std::string functionName;

                    public:
                        UnknownFunctionError(std::string functionName) {
                            this->functionName = functionName;
                        }

                        const std::string what() const throw() {
                            std::stringstream errorMessage;

                            errorMessage << "Function " << this->functionName << " is unknown";

                            return errorMessage.str();
                        }
                };

                class AbnormalFloatingNumberFormatError {
                    public:
                        const std::string what() const throw() {
                            return "The format of floating number is abnormal";
                        }
                };

                class NoOperatorError {
                    public:
                        const std::string what() const throw() {
                            return "No operator found";
                        }
                };

                class NoOperandError {
                    public:
                        const std::string what() const throw() {
                            return "No operand found";
                        }
                };
        };

        class Runtime {
            public:
                class ComplexError {
                    public:
                        const std::string what() const throw() {
                            return "Complex is not supported";
                        }
                };

                class NoOperandError {
                    public:
                        const std::string what() const throw() {
                            return "No operand found in stack";
                        }
                };
        };
};
