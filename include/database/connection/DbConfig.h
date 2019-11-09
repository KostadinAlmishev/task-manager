//
// Created by Konstantin Pronin on 05.11.2019.
//

#ifndef TASKMANAGER_INCLUDE_DATABASE_DBCONFIG_H_
#define TASKMANAGER_INCLUDE_DATABASE_DBCONFIG_H_

#include <string>
#include <fstream>

class DbConfig {
 private:
  std::istream &configFile;
  std::string host;
  int port;
  std::string dbName;
  std::string user;
  std::string password;
  int poolSize;

 public:
  DbConfig(const std::istream&);
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
