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
    // here will be meta data

    int mode;
    Group * group;
    std::vector<Group> * groupList;
    Project * project;
    std::vector<Project> * projectList;
    User * user;
    std::vector<User> * userList;
    Task * task;
    std::vector<Task> * taskList;
};

#endif //TASK_MANAGER_ENTITYCONTAINER_H
