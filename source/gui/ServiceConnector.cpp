#include <iostream>
#include <memory>

#include "ServiceConnector.h"
#include "Request.h"
#include "Response.h"

ServiceConnector::ServiceConnector() {
    controller = std::make_shared<Controller>();
}


void ServiceConnector::sendCommand(std::shared_ptr<Request> request, std::shared_ptr<Response> response) {
    controller->checkRequest(request, response);
}
