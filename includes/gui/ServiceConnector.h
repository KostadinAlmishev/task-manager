//
// Created by kotik on 25.11.2019.
//

#ifndef TASK_MANAGER_SERVICECONNECTOR_H
#define TASK_MANAGER_SERVICECONNECTOR_H

#include <iostream>
#include "Services.h"
#include "EntityContainer.h"
#include "TaskManager.h"

class ServiceConnector {
private:
    TaskManager taskManager;
    void getEntity(EntityContainer * entityContainer);
    void sendEntity(EntityContainer * entityContainer);
    void updateEntity(EntityContainer * entityContainer);
    void deleteEntity(EntityContainer * entityContainer);
public:
    ServiceConnector();


};

#endif //TASK_MANAGER_SERVICECONNECTOR_H
