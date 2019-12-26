#include "controller/SecurityManager.h"

bool SecurityManager::login(std::shared_ptr<User> user, std::string password) {
  return user->getPassword() == password;
}

bool SecurityManager::logout(std::shared_ptr<User> user, std::shared_ptr<Response> response) {}

void SecurityManager::changePassword(std::shared_ptr<User> user, std::string newPassword) {
  user->setPassword(newPassword);
}
