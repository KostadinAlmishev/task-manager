#ifndef TASKMANAGER_SECURITYMANAGER_H
#define TASKMANAGER_SECURITYMANAGER_H

#include <iostream>
#include <memory>
#include <vector>


#include "entities/Request.h"
#include "entities/Response.h"
#include "entities/User.h"

class SecurityManager {
private:
    std::vector<std::shared_ptr<User>> users;
public:
    void login(std::shared_ptr<User> user, std::string password, std::shared_ptr<Response> response);
    void logout(std::shared_ptr<User> user, std::shared_ptr<Response> response);

    bool isUserAuthorized(std::shared_ptr<User> user);
    bool checkPriveleges(std::string userName, std::string command);
    void changePassword(std::shared_ptr<User> user, std::string currentPassword, std::string newPassword);
    void setNewUserPassword(std::shared_ptr<User> user, std::string password);
};


#endif //TASKMANAGER_SECURITYMANAGER_H
