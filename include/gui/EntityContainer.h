//
// Created by kotik on 24.11.2019.
//

#ifndef TASK_MANAGER_ENTITYCONTAINER_H
#define TASK_MANAGER_ENTITYCONTAINER_H

#include "Entities.h"
#include <vector>




class EntityContainer {
private:

public:
    enum mode {
        MODE_SAVE,
        MODE_UPDADE,
        MODE_DELETE,
        MODE_GET
    };

    EntityContainer() : isQuit(false) {}
    bool isQuit;


    int mode;
    Project * project;
    std::vector<Project> * projectList;
    User * user;
    std::vector<User> * userList;
    Task * task;
    std::vector<Task> * taskList;
};

#endif //TASK_MANAGER_ENTITYCONTAINER_H
