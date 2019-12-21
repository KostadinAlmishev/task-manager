
#ifndef TASK_MANAGER_REQUEST_H
#define TASK_MANAGER_REQUEST_H

#include <memory>
#include <vector>

#include "Entity.h"
#include "Project.h"
#include "Task.h"
#include "User.h"


enum class requestMode {
    _EMPTY,
    NEW,
    UPDATE,
    DELETE,
    GET,
    AUTHORIZATION,
    DEAUTHORIZATION,
};

enum class requestCode {
    _EMPTY,
    TASK,
    PROJECT,
    USER,
};

enum class requestFindBy {
    _EMPTY,
    ID,
    NAME,
};


class Request {
private:

public:
    Request() : mode(requestMode::_EMPTY), code(requestCode::_EMPTY), findBy(requestFindBy::_EMPTY) {}

    requestMode mode;
    requestCode code;

    requestFindBy findBy;
    std::string fbName;
    int fbId;

    std::string commandName;

    std::shared_ptr<User> currentUser;

    std::shared_ptr<Project> project;
    std::shared_ptr<User> user;
    std::shared_ptr<Task> task;
};

#endif //TASK_MANAGER_REQUEST_H
