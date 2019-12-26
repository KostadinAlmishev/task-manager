#ifndef TASK_MANAGER_CONTROLLER_H
#define TASK_MANAGER_CONTROLLER_H

#include <memory>
#include <vector>

#include "CommandManager.h"
#include "CurlCallbacks.h"
#include "entities/Entity.h"
#include "entities/Project.h"
#include "entities/Request.h"
#include "entities/Response.h"
#include "entities/Task.h"
#include "entities/User.h"
#include "PgCallbacks.h"
#include "SecurityManager.h"

class Controller {
private:
    std::shared_ptr<CommandManager> commandManager;
    std::shared_ptr<SecurityManager> securityManager;

    void getEntity(std::shared_ptr<Request> request, std::shared_ptr<Response> response);
    void addEntity(std::shared_ptr<Request> request, std::shared_ptr<Response> response);
    void updateEntity(std::shared_ptr<Request> request, std::shared_ptr<Response> response);
    void deleteEntity(std::shared_ptr<Request> request, std::shared_ptr<Response> response);

    void Authorization(std::shared_ptr<Request> request, std::shared_ptr<Response> response);
    void Deauthorization(std::shared_ptr<Request> request, std::shared_ptr<Response> response);
public:
    Controller();
    void checkRequest(std::shared_ptr<Request> request, std::shared_ptr<Response> response);
};




#endif //TASK_MANAGER_CONTROLLER_H
