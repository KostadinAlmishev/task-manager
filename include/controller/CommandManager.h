#ifndef TASK_MANAGER_COMMANDMANAGER_H
#define TASK_MANAGER_COMMANDMANAGER_H

#include <fstream>
#include <memory>

#include "database/factories/ProjectDbCommandFactory.h"
#include "database/factories/TaskDbCommandFactory.h"
#include "database/factories/UserDbCommandFactory.h"
#include "entities/Entity.h"
#include "entities/Project.h"
#include "entities/Task.h"
#include "entities/User.h"
#include "managers/DbManager.h"
#include "database/factories/DbCommandFactory.h"

template<typename Connection, typename ResultSet, typename DbCallback>
class CommandManager {
 private:
  DbConfig _dbConfig;
  std::unique_ptr<DbConnector<Connection, ResultSet, DbCallback>> _dbConnector;
  std::unique_ptr<DbCommandFactory<Connection, ResultSet, DbCallback>> _userDbCommandFactory;
  std::unique_ptr<DbCommandFactory<Connection, ResultSet, DbCallback>> _taskDbCommandFactory;
  std::unique_ptr<DbCommandFactory<Connection, ResultSet, DbCallback>> _projectDbCommandFactory;
  std::unique_ptr<DbManager<Connection, ResultSet, DbCallback>> _dbManager;
  std::unique_ptr<NotificationManager> _notificationManager;

 public:
  explicit CommandManager(std::string);

  void addSubscriber(std::shared_ptr<Subscriber>);
  void removeSubscriber(std::shared_ptr<Subscriber>);

  bool addUser(std::shared_ptr<User>, std::shared_ptr<User> user);
  std::shared_ptr<User> getUserByName(std::string name);
//  std::shared_ptr<User> getUserById(int id);
//  bool updateUserByName(std::shared_ptr<User> user, std::string name);
//  bool deleteUserByName(std::string name);
//  bool deleteUserById(int id);

//  bool addProject(std::shared_ptr<Task> task);
//  std::shared_ptr<Task> getProjectById(int id);
//  bool updateProjectById(std::shared_ptr<Task> task, int id);
//  bool deleteProjectById(int id);

  bool addTask(std::shared_ptr<User>, std::shared_ptr<Task> task);
  std::shared_ptr<Task> getTaskByName(std::string);
//  std::shared_ptr<Task> getTaskById(int id);
//  bool updateTaskById(std::shared_ptr<Task> task, int id);
//  bool deleteTaskById(int id);
};


template<typename Connection, typename ResultSet, typename DbCallback>
CommandManager<Connection, ResultSet, DbCallback>::CommandManager(std::string dbConfigPath) {
  std::ifstream dbProperties(dbConfigPath);
  std::streambuf *buffer = dbProperties.rdbuf();
  _dbConfig(*buffer);
  _dbConfig.readConfigFromFile();
  _dbConnector = std::make_unique<DbConnector<Connection, ResultSet, DbCallback>>(_dbConfig);
  _userDbCommandFactory = std::make_unique<UserDbCommandFactory<Connection, ResultSet, DbCallback>>(*_dbConnector);
  _taskDbCommandFactory = std::make_unique<TaskDbCommandFactory<Connection, ResultSet, DbCallback>>(*_dbConnector);
  _projectDbCommandFactory = std::make_unique<ProjectDbCommandFactory<Connection, ResultSet, DbCallback>>(*_dbConnector);
  _dbManager = std::make_unique<DbManager<Connection, ResultSet, DbCallback>>();
  _notificationManager = std::make_unique<NotificationManager>();
}

template<typename Connection, typename ResultSet, typename DbCallback>
void CommandManager<Connection, ResultSet, DbCallback>::addSubscriber(std::shared_ptr<Subscriber> subscriber) {
  _notificationManager->subscribe(subscriber);
}

template<typename Connection, typename ResultSet, typename DbCallback>
void CommandManager<Connection, ResultSet, DbCallback>::removeSubscriber(std::shared_ptr<Subscriber> subscriber) {
  _notificationManager->unsubscribe(subscriber);
}

template<typename Connection, typename ResultSet, typename DbCallback>
bool CommandManager<Connection, ResultSet, DbCallback>::addUser(std::shared_ptr<User> currentUser, std::shared_ptr<User> user) {
  std::shared_ptr<DbCommand<Connection, ResultSet, DbCallback>> command = _userDbCommandFactory->createAddCommand(user);
  _dbManager.setCommand(command);
  _dbManager.executeCommand();
  _notificationManager->notifyAll(*currentUser, *user);
}

template<typename Connection, typename ResultSet, typename DbCallback>
std::shared_ptr<User> CommandManager<Connection,
                                     ResultSet,
                                     DbCallback>::getUserByName(std::string name) {
  std::shared_ptr<User> user = std::make_shared<User>();
  std::shared_ptr<DbCommand<Connection, ResultSet, DbCallback>> command = _userDbCommandFactory->createGetCommand(name, user);
  _dbManager.setCommand(command);
  _dbManager.executeCommand();
  return user;
}

template<typename Connection, typename ResultSet, typename DbCallback>
bool CommandManager<Connection, ResultSet, DbCallback>::addTask(std::shared_ptr<User> currentUser, std::shared_ptr<Task> task) {
  std::shared_ptr<DbCommand<Connection, ResultSet, DbCallback>> command = _taskDbCommandFactory->createAddCommand(task);
  _dbManager.setCommand(command);
  _dbManager.executeCommand();
  _notificationManager->notifyAll(*currentUser, *task);
}

template<typename Connection, typename ResultSet, typename DbCallback>
std::shared_ptr<Task> CommandManager<Connection, ResultSet, DbCallback>::getTaskByName(std::string name) {
  std::shared_ptr<Task> task = std::make_shared<Task>();
  std::shared_ptr<DbCommand<Connection, ResultSet, DbCallback>> command = _userDbCommandFactory->createGetCommand(name, task);
  _dbManager.setCommand(command);
  _dbManager.executeCommand();
  return task;
}

#endif //TASK_MANAGER_COMMANDMANAGER_H
