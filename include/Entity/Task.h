//
// Created by daniil on 16.11.2019.
//

#ifndef TASK_MANAGER_TASK_H
#define TASK_MANAGER_TASK_H


#include "Entity.h"

class Task : public Entity{
private:
    friend class TaskService;
};


#endif //TASK_MANAGER_TASK_H
