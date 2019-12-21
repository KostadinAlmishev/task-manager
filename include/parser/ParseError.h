#ifndef TASKMANAGER_PARSEERROR_H
#define TASKMANAGER_PARSEERROR_H

#include <iostream>
#include <memory>

class ParseError {
public:
    ParseError() : isQuit(false), quitBody(""), isError(false), errorBody("") {}

    bool isQuit;
    std::string quitBody;
    bool isError;
    std::string errorBody;
};

#endif //TASKMANAGER_PARSEERROR_H
