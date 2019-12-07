//
// Created by daniil on 16.11.2019.
//

#ifndef TASK_MANAGER_PROJECT_H
#define TASK_MANAGER_PROJECT_H


#include "Entity.h"

class Project: public Entity {
private:
    friend class ProjectService;
};


#endif //TASK_MANAGER_PROJECT_H
