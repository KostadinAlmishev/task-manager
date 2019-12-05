#ifndef TASK_MANAGER_RESPONSE_H
#define TASK_MANAGER_RESPONSE_H

#include <vector>
#include <memory>

#include "Entities.h"

enum class responseCode {
    _EMPTY,
    TASK,
    PROJECT,
    USER,
    TASK_LIST,
    PROJECT_LIST,
    USER_LIST
};


class Response {
private:

public:
    Response() : isError(false),  code(responseCode::_EMPTY), errorBody("") {}

    responseCode code;
    bool isError;
    std::string errorBody;

    std::shared_ptr<Project> project;
    std::shared_ptr<std::vector<Project>> projects;
    std::shared_ptr<User> user;
    std::shared_ptr<std::vector<User>> users;
    std::shared_ptr<Task> task;
    std::shared_ptr<std::vector<Task>> tasks;
};



#endif //TASK_MANAGER_RESPONSE_H
