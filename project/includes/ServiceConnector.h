//
// Created by kotik on 25.11.2019.
//

#ifndef TASK_MANAGER_SERVICECONNECTOR_H
#define TASK_MANAGER_SERVICECONNECTOR_H

#include <iostream>
#include "Services.h"
#include "EntityContainer.h"


class ServiceConnector {
private:
    ProjectService *projectService;
    TaskService *taskService;
    UserService *userService;
    GroupService *groupService;
public:
    ServiceConnector(ProjectService *projectService,
                     TaskService *taskService,
                     UserService *userService,
                     GroupService *groupService);

    void getEntityFromBack(EntityContainer *entityContainer);

    void sendEntityToBack(EntityContainer *entityContainer);
};

#endif //TASK_MANAGER_SERVICECONNECTOR_H
