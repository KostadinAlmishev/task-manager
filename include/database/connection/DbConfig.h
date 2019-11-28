//
// Created by Konstantin Pronin on 05.11.2019.
//

#ifndef TASKMANAGER_INCLUDE_DATABASE_DBCONFIG_H_
#define TASKMANAGER_INCLUDE_DATABASE_DBCONFIG_H_

#include <mutex>
#include <string>

class DbConfig {
 private:
  static const size_t PARAMETERS_NUMBER = 6;
  std::mutex _mutex;
  std::string _confFilePath;
  std::string _host;
  int _port;
  std::string _dbName;
  std::string _user;
  std::string _password;
  int _poolSize;

 public:
  explicit DbConfig(std::string);
  DbConfig(const DbConfig &);
  virtual void readConfigFromFile();
  virtual std::string getHost() const noexcept;
  virtual int getPort() const noexcept;
  virtual std::string getDbName() const noexcept;
  virtual std::string getUser() const noexcept;
  virtual std::string getPassword() const noexcept;
  virtual int getPoolSize() const noexcept;
  virtual ~DbConfig() = default;
};
#endif //TASKMANAGER_INCLUDE_DATABASE_DBCONFIG_H_
