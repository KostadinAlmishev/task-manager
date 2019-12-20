//
// Created by Konstantin Pronin on 06.12.2019.
//
#include <memory>
#include <string>
#include <stdexcept>
#include <utility>

#include "database/config/DbConfig.h"

Validator::Validator(std::shared_ptr<Validator> next) : _next(std::move(next)) {}

HostValidator::HostValidator(std::shared_ptr<Validator> next) : Validator(std::move(next)) {}

PortValidator::PortValidator(std::shared_ptr<Validator> next) : Validator(std::move(next)) {}

DbNameValidator::DbNameValidator(std::shared_ptr<Validator> next) : Validator(std::move(next)) {}

UserValidator::UserValidator(std::shared_ptr<Validator> next) : Validator(std::move(next)) {}

PasswordValidator::PasswordValidator(std::shared_ptr<Validator> next) : Validator(std::move(next)) {}

PoolSizeValidator::PoolSizeValidator(std::shared_ptr<Validator> next) : Validator(std::move(next)) {}

void HostValidator::validate(const std::string &parameter, const std::string &value, DbConfig &config) const {
  if (parameter == std::string("host")) {
    config.setHost(value);
  } else if (_next) {
    _next->validate(parameter, value, config);
  } else {
    throw std::invalid_argument("Invalid parameter in configuration file!");
  }
}

void PortValidator::validate(const std::string &parameter, const std::string &value, DbConfig &config) const {
  if (parameter == std::string("port")) {
    config.setPort(value);
  } else if (_next) {
    _next->validate(parameter, value, config);
  } else {
    throw std::invalid_argument("Invalid parameter in configuration file: " + parameter);
  }
}

void DbNameValidator::validate(const std::string &parameter, const std::string &value, DbConfig &config) const {
  if (parameter == std::string("name")) {
    config.setDbName(value);
  } else if (_next) {
    _next->validate(parameter, value, config);
  } else {
    throw std::invalid_argument("Invalid parameter in configuration file: " + parameter);
  }
}

void UserValidator::validate(const std::string &parameter, const std::string &value, DbConfig &config) const {
  if (parameter == std::string("user")) {
    config.setUser(value);
  } else if (_next) {
    _next->validate(parameter, value, config);
  } else {
    throw std::invalid_argument("Invalid parameter in configuration file: " + parameter);
  }
}

void PasswordValidator::validate(const std::string &parameter, const std::string &value, DbConfig &config) const {
  if (parameter == std::string("password")) {
    config.setPassword(value);
  } else if (_next) {
    _next->validate(parameter, value, config);
  } else {
    throw std::invalid_argument("Invalid parameter in configuration file: " + parameter);
  }
}

void PoolSizeValidator::validate(const std::string &parameter, const std::string &value, DbConfig &config) const {
  if (parameter == std::string("pool") && stoi(value) >= 0) {
    config.setPoolSize(stoi(value));
  } else if (_next) {
    _next->validate(parameter, value, config);
  } else {
    throw std::invalid_argument("Invalid parameter in configuration file: " + parameter);
  }
}
