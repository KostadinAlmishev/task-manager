#include "controller/SecurityManager.h"

void SecurityManager::login(std::shared_ptr<User> user, std::string password, std::shared_ptr<Response> response) {
    validResponse vresponse = userService.Login(*user, password);
    if (!vresponse.Valid) {
        response->isError = true;
        response->errorBody = vresponse.ResponseERROR;
    }
}

void SecurityManager::logout(std::shared_ptr<User> user, std::shared_ptr<Response> response) {
    validResponse vresponse = userService.Logout(*user);
    if (!vresponse.Valid) {
        response->isError = true;
        response->errorBody = vresponse.ResponseERROR;
    }
}

bool SecurityManager::isUserAuthorized(std::shared_ptr<User> user) {
    return true;
}

bool SecurityManager::checkPriveleges(std::string userName, std::string command) {
    return true;
}

