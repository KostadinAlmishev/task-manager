#include <iostream>
#include <memory>

#include "gui/State.h"
#include "entities/Entity.h"
#include "entities/Project.h"
#include "entities/Task.h"
#include "entities/User.h"


State::State() : _isAuthorized(false) {

}

void State::authorize(std::shared_ptr<User> user) {
    this->user = user;
    _isAuthorized = true;
}
void State::deauthorize() {
    this->user = nullptr;
    _isAuthorized = false;
}
bool State::isAuthorized() {
    return _isAuthorized;
}
std::shared_ptr<User> State::getCurrentUser() {
    return user;
}

