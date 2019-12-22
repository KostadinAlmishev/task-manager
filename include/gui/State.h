#ifndef TASK_MANAGER_STATE_H
#define TASK_MANAGER_STATE_H

#include <iostream>
#include <memory>

#include "entities/Entity.h"
#include "entities/Project.h"
#include "entities/Task.h"
#include "entities/User.h"


class State {
private:
    std::shared_ptr<User> user;
    bool _isAuthorized;

public:
    State();
    void authorize(std::shared_ptr<User> user);
    void deauthorize();
    bool isAuthorized();
    std::shared_ptr<User> getCurrentUser();
};



#endif //TASK_MANAGER_STATE_H
