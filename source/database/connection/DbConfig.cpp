//
// Created by Konstantin Pronin on 28.11.2019.
//

#include <fstream>
#include <stdexcept>
#include <utility>

#include "database/connection/DbConfig.h"

DbConfig::DbConfig(std::streambuf& confFile) : _confFile(&confFile),
                                               _host(""),
                                               _port(0),
                                               _dbName(""),
                                               _user(""),
                                               _password(""),
                                               _poolSize(0) {}

void DbConfig::readConfigFromFile() noexcept(false) {
  std::lock_guard<std::mutex> lock(_mutex);

//  if (!_confFile.is_open()) {
//    throw std::ios_base::failure("Error when try to open db configuration file!");
//  }

  for (size_t i = 0; i < PARAMETERS_NUMBER; ++i) {
    if (_confFile.eof()) {
      throw std::invalid_argument("Not enough parameters in configuration file!");
    }

    std::string confLine;
    _confFile >> confLine;

    size_t delimiterPosition = confLine.find('=');
    if (delimiterPosition == std::string::npos) {
      throw std::invalid_argument("Invalid format of configuration file!");
    }

    std::string parameter = confLine.substr(0, delimiterPosition);
    std::string value = confLine.substr(delimiterPosition);

    if (parameter == "host") {
      _host = value;
    } else if (parameter == "port") {
      _port = stoi(value);
    } else if (parameter == "name") {
      _dbName = value;
    } else if (parameter == "user") {
      _user = value;
    } else if (parameter == "password") {
      _password = value;
    } else if (parameter == "pool") {
      _poolSize = stoi(value);
    } else {
      throw std::invalid_argument("Invalid parameter in configuration file!");
    }
  }
}

std::string DbConfig::getHost() const noexcept {
  return _host;
}

int DbConfig::getPort() const noexcept {
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




