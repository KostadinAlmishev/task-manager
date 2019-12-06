//
// Created by daniil on 16.11.2019.
//

#ifndef TASK_MANAGER_USER_H
#define TASK_MANAGER_USER_H


#include "Entity.h"

class User : public Entity {
protected:
    friend class UserService;
    bool login;
    std::string password;
public:
    std::string GetStatus() override ;
    User(){;}
    User(unsigned long int id, std::string name, std::string description, std::string password  );
};


#endif //TASK_MANAGER_USER_H
