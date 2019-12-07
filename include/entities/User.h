//
// Created by Konstantin Pronin on 05.11.2019.
//

#ifndef TASKMANAGER_INCLUDE_ENTITY_USER_H_
#define TASKMANAGER_INCLUDE_ENTITY_USER_H_

#include <string>

#include "entities/Entity.h"

class User : public Entity {
 private:
  std::string _name;
  std::string _password;
  std::string _email;
 public:
  User(const User &user) = default;
  void setName(std::string name);
  void setPassword(std::string password);
  void setEmail(std::string email);
  std::string getName() const;
  std::string getPassword() const;
  std::string getEmail() const;
  std::string toString() const override;
};

#endif //TASKMANAGER_INCLUDE_ENTITY_USER_H_
