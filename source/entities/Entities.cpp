//
// Created by kotik on 03.12.2019.
//

#include "Entities.h"


long Entity::getId() const {
    return id;
}
void Entity::setId(long id) {
    this->id = id;
}


std::string Project::getName() const {
    return name;
}
void Project::setName(std::string name) {
    this->name = name;
}
void Project::setDescription(std::string description) {
    this->description = description;
}
std::string Project::getDescription() const {
    return description;
}



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



void Task::setCreatorId(long creatorId) {
    this->creatorId = creatorId;
}
long Task::getCreatorId() const {
    return creatorId;
}
void Task::setProjectId(long projectId) {
    this->projectId = projectId;
}
long Task::getProjectId() const {
    return projectId;
}
void Task::setName(std::string name) {
    this->name = name;
}
std::string Task::getName() const {
    return name;
}
void Task::setDescription(std::string description) {
    this->description = description;
}
std::string Task::getDescription() const {
    return description;
}


