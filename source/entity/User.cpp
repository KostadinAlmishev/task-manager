//
// Created by Konstantin Pronin on 01.12.2019.
//

#include <string>
#include <utility>
#include <entity/User.h>
void User::setName(std::string name) {
  _name = std::move(name);
}
void User::setPassword(std::string password) {
  _password = std::move(password);
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
