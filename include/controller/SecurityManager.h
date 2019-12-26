#ifndef TASKMANAGER_SECURITYMANAGER_H
#define TASKMANAGER_SECURITYMANAGER_H

#include <iostream>
#include <memory>
#include <vector>


#include "entities/Request.h"
#include "entities/Response.h"
#include "entities/User.h"
#include "services/UserService.h"
#include "services/validResponse.h"

class SecurityManager {
private:
    UserService userService;
public:
    bool login(std::shared_ptr<User> user, std::string password);
    bool logout(std::shared_ptr<User> user, std::shared_ptr<Response> response);
    void changePassword(std::shared_ptr<User> user, std::string newPassword);
};


#endif //TASKMANAGER_SECURITYMANAGER_H
