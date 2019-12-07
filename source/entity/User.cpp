//
// Created by daniil on 16.11.2019.
//

#include "include/entities/User.h"

User::User(unsigned long int id, std::string name, std::string description, std::string password) {
    this->name =name;
    this->description =description;
    this->password = password;
    this->id = id;
}
std::string User::GetStatus() {
    return "";
}