//
// Created by daniil on 16.11.2019.
//
#include "IValidator.h"
#include "Entity/User.h"
Entity* Validator::CheckValidation(std::string login, std::string password) {
    return  new User();
}

