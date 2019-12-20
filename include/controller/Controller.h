#ifndef TASK_MANAGER_CONTROLLER_H
#define TASK_MANAGER_CONTROLLER_H

#include <memory>
#include <vector>

#include "CommandManager.h"
#include "entities/Entity.h"
#include "entities/Project.h"
#include "entities/Request.h"
#include "entities/Response.h"
#include "entities/Task.h"
#include "entities/User.h"





class Controller {
private:
    std::shared_ptr<CommandManager> commandManager;

public:
    Controller();
    void checkRequest(std::shared_ptr<Request> request, std::shared_ptr<Response> response);

    void getEntity(std::shared_ptr<Request> request, std::shared_ptr<Response> response);
    void addEntity(std::shared_ptr<Request> request, std::shared_ptr<Response> response);
    void updateEntity(std::shared_ptr<Request> request, std::shared_ptr<Response> response);
    void deleteEntity(std::shared_ptr<Request> request, std::shared_ptr<Response> response);
    void checkAuthorization(std::shared_ptr<Request> request, std::shared_ptr<Response> response);
    void checkDeauthorization(std::shared_ptr<Request> request, std::shared_ptr<Response> response);
};




#endif //TASK_MANAGER_CONTROLLER_H
