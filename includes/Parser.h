//
// Created by kotik on 25.11.2019.
//

#ifndef TASK_MANAGER_PARSER_H
#define TASK_MANAGER_PARSER_H

#include <iostream>
#include "EntityContainer.h"



class Parser {
private:

public:
    EntityContainer * parseProjectEntity(std::string command);
    EntityContainer * parseTaskEntity(std::string command);
    EntityContainer * parseUserEntity(std::string command);
    EntityContainer * parseGroupEntity(std::string command);
    EntityContainer * parse(std::string command);
};

#endif //TASK_MANAGER_PARSER_H
