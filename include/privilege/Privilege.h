//
// Created by daniil on 11.12.2019.
//

#ifndef TASK_MANAGER_PRIVILEGE_H
#define TASK_MANAGER_PRIVILEGE_H

#include <iostream>
#include <set>
#include <map>
#include <string>
#include "entities/Request.h"
class  Privelege{
public:
    static inline const std::map< const std::string, const std::set< std::string> >  map_of_privelege = {
            std::pair<std::string, std::set<std::string>>{"user", {"testUser1", "testUser2"}},
            std::pair<std::string, std::set<std::string>>{"admin", {"testAdmin1", "testAdmin2"}}
    };

    static inline bool check(std::string status, std::string command){
        auto statusCommands =  Privelege::map_of_privelege.find(status)->second;
        return statusCommands.find(command) != statusCommands.end();
    }


};


#endif //TASK_MANAGER_PRIVILEGE_H
