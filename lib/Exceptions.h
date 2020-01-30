#pragma once
#define _EXCEPTIONS_H_

#include <string>
#include <sstream>
#include <exception>

class Exceptions:public std::exception {
    public:
        class Parsing {
            public:
                class BracketNotMatchError { public: const char *what() const throw() { return "Bracket is not matched"; } };

                class UnknownOperatorError {
                    private:
                        std::string operatorSign;

                    public:
                        UnknownOperatorError(std::string operatorSign) {
                            this->operatorSign = operatorSign;
                        }

                        std::string what() const throw() {
                            std::stringstream errorMessage;

                            errorMessage << "Operator " << this->operatorSign << " is unknown";
                            
                            return errorMessage.str();
                        }
                };
        };

        class Calculating {
            public:
                class ComplexError { public: const char *what() const throw() { return "Complex is not supported"; } };
        };
};
