#include "entities/Task.h"


void Task::setCreatorId(int creatorId) {
    this->creatorId = creatorId;
}
int Task::getCreatorId() const {
    return creatorId;
}
void Task::setProjectId(int projectId) {
    this->projectId = projectId;
}
int Task::getProjectId() const {
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

