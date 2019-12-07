//
// Created by kotik on 24.11.2019.
//

#ifndef TASK_MANAGER_REQUEST_H
#define TASK_MANAGER_REQUEST_H

#include <vector>
#include <memory>

#include "Entity.h"
#include "Task.h"
#include "User.h"
#include "Project.h"


enum class requestMode {
    _EMPTY,
    SAVE,
    UPDADE,
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
    TASK_LIST,
    PROJECT_LIST,
    USER_LIST
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

    std::shared_ptr<Project> project;
    std::shared_ptr<User> user;
    std::shared_ptr<Task> task;
};

#endif //TASK_MANAGER_REQUEST_H
