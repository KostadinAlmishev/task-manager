#include <iostream>

#include "ServiceConnector.h"
#include "Request.h"
#include "Response.h"

ServiceConnector::ServiceConnector() {

}


void ServiceConnector::sendCommand(std::shared_ptr<Request> request, std::shared_ptr<Response> response) {
    taskManager.executeCommand(request, response);
}
