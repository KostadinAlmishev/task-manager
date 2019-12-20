#ifndef TASK_MANAGER_USER_H
#define TASK_MANAGER_USER_H

#include <string>

#include "entities/Entity.h"

class User : public Entity {
 private:
  std::string _name;
  std::string _password;
  std::string _email;
  std::string _status;
 public:
  User() = default;
  User(const User &user) = default;
  void setName(std::string name);
  void setPassword(std::string password);
  void setEmail(std::string email);
  std::string getName() const;
  std::string getPassword() const;
  std::string getEmail() const;
  std::string toString() const override;
  std::vector<Descriptor> createDescriptors() const override;
  void setStatus(std::string status);
  std::string getStatus() const;

  bool operator==(const User& right){return this->getName() == right.getName();}
};
#endif //TASK_MANAGER_USER_H
