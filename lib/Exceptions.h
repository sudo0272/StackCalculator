#pragma once
#define _EXCEPTIONS_H_

#include <string>
#include <exception>

class Exceptions:public std::exception {
    public:
        class Parsing {
            public:
        };

        class Calculating {
            public:
                class ComplexError { public: const char* what() const throw() { return "Complex is not supported"; } };
        };
};
