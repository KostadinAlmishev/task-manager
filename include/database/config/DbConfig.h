//
// Created by Konstantin Pronin on 05.11.2019.
//

#ifndef TASKMANAGER_INCLUDE_DATABASE_DBCONFIG_H_
#define TASKMANAGER_INCLUDE_DATABASE_DBCONFIG_H_

#include <memory>
#include <mutex>
#include <string>
#include <iostream>

#include "database/config/Validator.h"

class DbConfig {
 private:
  std::unique_ptr<Validator> _validator;
  std::mutex _mutex;
  std::istream _confFile;
  std::string _host;
  std::string _port;
  std::string _dbName;
  std::string _user;
  std::string _password;
  int _poolSize;

 public:
  explicit DbConfig(std::streambuf&);

  virtual void readConfigFromFile();

  virtual std::string getHost() const noexcept;
  virtual std::string getPort() const noexcept;
  virtual std::string getDbName() const noexcept;
  virtual std::string getUser() const noexcept;
  virtual std::string getPassword() const noexcept;
  virtual int getPoolSize() const noexcept;

  void setHost(std::string);
  void setPort(std::string);
  void setDbName(std::string);
  void setUser(std::string);
  void setPassword(std::string);
  void setPoolSize(size_t);

  virtual ~DbConfig() = default;
};
#endif //TASKMANAGER_INCLUDE_DATABASE_DBCONFIG_H_
