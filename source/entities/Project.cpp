#include <vector>
#include "entities/Project.h"

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

std::string Project::toString() const {
  return "Name: " + name + " Description: " + description;
}


std::vector<Descriptor> Project::createDescriptors() const {
  std::vector<Descriptor> descriptors;
  descriptors.push_back({"ID", std::to_string(getId())});
  descriptors.push_back({"NAME", getName()});
  descriptors.push_back({"DESCRIPTION", getDescription()});
  return descriptors;
}
