#include <iostream>
#include <memory>

#include "State.h"
#include <Entities.h>

State::State() : _isAuthorized(false) {

}

void State::authorize(std::shared_ptr<User> user) {
    this->user = user;
    _isAuthorized = true;
}
void State::deauthorize() {
    _isAuthorized = false;
}
bool State::isAuthorized() {
    return _isAuthorized;
}
std::string State::getUserName() {
    return user->getName();
}

