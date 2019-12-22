#ifndef TASK_MANAGER_SERVICECONNECTOR_H
#define TASK_MANAGER_SERVICECONNECTOR_H

#include <iostream>
#include <memory>

#include "controller/Controller.h"
#include "entities/Request.h"
#include "entities/Response.h"

class ServiceConnector {
private:
    std::shared_ptr<Controller> controller;
public:
    ServiceConnector();
    void sendCommand(std::shared_ptr<Request> request, std::shared_ptr<Response> response);
};

#endif //TASK_MANAGER_SERVICECONNECTOR_H
