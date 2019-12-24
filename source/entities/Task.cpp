#include <vector>
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

std::string Task::toString() const {
  return "|Name=" + name + "|Description=" + description + "|ProjectId=" + std::to_string(projectId) + "|CreatorId="
      + std::to_string(creatorId) + "|\n";
}

std::vector<Descriptor> Task::createDescriptors() const {
  std::vector<Descriptor> descriptors;
  descriptors.push_back({"ID", std::to_string(getId())});
  descriptors.push_back({"NAME", getName()});
  descriptors.push_back({"DESCRIPTION", getDescription()});
  descriptors.push_back({"PROJECT_ID", std::to_string(getProjectId())});
  descriptors.push_back({"USER_ID", std::to_string(getCreatorId())});
  return descriptors;
}
