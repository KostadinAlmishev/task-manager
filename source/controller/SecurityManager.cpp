#include "controller/SecurityManager.h"

void SecurityManager::login(std::shared_ptr<User> user, std::string password, std::shared_ptr<Response> response) {
    if (user->getPassword() == password) {
        users.push_back(user);
    }
    else {
        response->isError = true;
        response->errorBody = "There is no user with such password or name";
    }
}

void SecurityManager::logout(std::shared_ptr<User> user, std::shared_ptr<Response> response) {
    if (isUserAuthorized(user)) {
        int i = 0;
        while (users[i]->getName() != user->getName()) i++;
        users[i] = nullptr;
        if (users[users.size() - 1] != nullptr) {
            users[i] = users[users.size() - 1];
            users[i]->setId(i);
        }
        users.resize(users.size() - 1);
    }
}

bool SecurityManager::isUserAuthorized(std::shared_ptr<User> user) {
    for (auto it : users) {
        if (it->getName() == user->getName()) return true;
    }
    return false;
}

bool SecurityManager::checkPriveleges(std::string userName, std::string command) {
    return true;
}

