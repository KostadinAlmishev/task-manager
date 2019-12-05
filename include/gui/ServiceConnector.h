#ifndef TASK_MANAGER_SERVICECONNECTOR_H
#define TASK_MANAGER_SERVICECONNECTOR_H

#include <iostream>
#include <memory>

#include "Request.h"
#include "TaskManager.h"
#include "Response.h"

class ServiceConnector {
private:
    TaskManager taskManager;
public:
    ServiceConnector();
    void sendCommand(std::shared_ptr<Request> request, std::shared_ptr<Response> response);
};

#endif //TASK_MANAGER_SERVICECONNECTOR_H
