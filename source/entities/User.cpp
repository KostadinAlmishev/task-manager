#include <string>
#include <vector>
#include <utility>

#include "entities/Entity.h"
#include "entities/User.h"

void User::setName(std::string name) {
  _name = std::move(name);
}
void User::setPassword(std::string password) {
  _password = std::move(password);

void User::setStatus(std::string status) {
    this->status = status;
}

std::string User::getStatus() const {
    return status;
}

void User::setEmail(std::string email) {
  _email = std::move(email);
}

std::string User::getName() const {
  return _name;
}

std::string User::getPassword() const {
  return _password;
}

std::string User::getEmail() const {
  return _email;
}

std::string User::toString() const {
  return "Name: " + _name + " Password: " + _password + " Email: " + _email;
}

std::vector<Descriptor> User::createDescriptors() const {
  std::vector<Descriptor> descriptors;
  descriptors.push_back({"ID", std::to_string(getId())});
  descriptors.push_back({"NAME", getName()});
  descriptors.push_back({"PASSWORD", getPassword()});
  descriptors.push_back({"EMAIL", getEmail()});
  return descriptors;
}
