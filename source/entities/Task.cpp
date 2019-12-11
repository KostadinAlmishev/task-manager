//
// Created by daniil on 16.11.2019.
//

#include "entities/Task.h"
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
