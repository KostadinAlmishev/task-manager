#include <iostream>
#include <memory>

#include "gui/ServiceConnector.h"
#include "entities/Request.h"
#include "entities/Response.h"
#include "controller/Controller.h"

ServiceConnector::ServiceConnector() {
    controller = std::make_shared<Controller>();
}


void ServiceConnector::sendCommand(std::shared_ptr<Request> request, std::shared_ptr<Response> response) {
    controller->checkRequest(request, response);
}
