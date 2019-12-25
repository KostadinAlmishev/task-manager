#ifndef TASK_MANAGER_PARSER_H
#define TASK_MANAGER_PARSER_H

#include <iostream>

#include "entities/Request.h"
#include "ParseError.h"
#include "ParseHandler.h"
#include "stringFunctions/StringFunctions.h"

class Parser {
private:
public:
    void parse(std::string command, std::shared_ptr<Request> request, std::shared_ptr<ParseError> parseError);
};



#endif //TASK_MANAGER_PARSER_H
