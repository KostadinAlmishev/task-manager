//
// Created by daniil on 16.11.2019.
//

#ifndef TASK_MANAGER_USER_H
#define TASK_MANAGER_USER_H


#include "Entity.h"

class User : public Entity {
private:
    friend class UserService;
};


#endif //TASK_MANAGER_USER_H
