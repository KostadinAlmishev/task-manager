#ifndef TASK_MANAGER_PARSER_H
#define TASK_MANAGER_PARSER_H

#include <iostream>

#include "entities/Request.h"
#include "stringFunctions/StringFunctions.h"


class ParseError {
public:
    ParseError() : isQuit(false), quitBody(""), isError(false), errorBody("") {}

    bool isQuit;
    std::string quitBody;
    bool isError;
    std::string errorBody;
};



class Parser {
private:
    void parseProject(std::string command, std::shared_ptr<Request> request, std::shared_ptr<ParseError> parseError);
    void parseTask(std::string command, std::shared_ptr<Request> request, std::shared_ptr<ParseError> parseError);
    void parseUser(std::string command, std::shared_ptr<Request> request, std::shared_ptr<ParseError> parseError);
public:

    void parse(std::string command, std::shared_ptr<Request> request, std::shared_ptr<ParseError> parseError);
};



#endif //TASK_MANAGER_PARSER_H
