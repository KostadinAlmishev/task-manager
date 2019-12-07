#include "entities/User.h"

void User::setName(std::string name) {
    this->name = name;
}

std::string User::getName() const {
    return name;
}

void User::setPassword(std::string password) {
    this->password = password;
}

std::string User::getPassword() const {
    return password;
}

void User::setEmail(std::string email) {
    this->email = email;
}

std::string User::getEmail() const {
    return email;
}

void User::setStatus(std::string status) {
    this->status = status;
}

std::string User::getStatus() const {
    return status;
}