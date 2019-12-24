//
// Created by Konstantin Pronin on 28.11.2019.
//

#include <stdexcept>
#include <utility>

#include "database/config/DbConfig.h"

DbConfig::DbConfig(std::streambuf& confFile) : _confFile(&confFile),
                                               _host(""),
                                               _port(""),
                                               _dbName(""),
                                               _user(""),
                                               _password(""),
                                               _poolSize(0) {

  auto poolSizeValidator = std::make_shared<PoolSizeValidator>(nullptr);
  auto passwordValidator = std::make_shared<PasswordValidator>(poolSizeValidator);
  auto userValidator = std::make_shared<UserValidator>(passwordValidator);
  auto dbNameValidator = std::make_shared<DbNameValidator>(userValidator);
  auto portValidator = std::make_shared<PortValidator>(dbNameValidator);
  _validator = std::make_unique<HostValidator>(portValidator);
}

void DbConfig::readConfigFromFile() noexcept(false) {
  std::lock_guard<std::mutex> lock(_mutex);
  std::string confLine;

  while (_confFile >> confLine) {

    size_t delimiterPosition = confLine.find('=');
    if (delimiterPosition == std::string::npos) {
      throw std::invalid_argument("Invalid format of configuration file!");
    }

    std::string parameter = confLine.substr(0, delimiterPosition);
    std::string value = confLine.substr(delimiterPosition + 1);

    _validator->validate(parameter, value, *this);
  }
}

std::string DbConfig::getHost() const noexcept {
  return _host;
}

std::string DbConfig::getPort() const noexcept {
  return _port;
}

std::string DbConfig::getDbName() const noexcept {
  return _dbName;
}

std::string DbConfig::getUser() const noexcept {
  return _user;
}

std::string DbConfig::getPassword() const noexcept {
  return _password;
}

int DbConfig::getPoolSize() const noexcept {
  return _poolSize;
}
void DbConfig::setHost(std::string host) {
  _host = host;
}
void DbConfig::setPort(std::string port) {
  _port = port;
}
void DbConfig::setDbName(std::string dbName) {
  _dbName = dbName;
}
void DbConfig::setUser(std::string user) {
  _user = user;
}
void DbConfig::setPassword(std::string password) {
  _password = password;
}
void DbConfig::setPoolSize(size_t poolSize) {
  _poolSize = poolSize;
}




