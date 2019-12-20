#ifndef TASK_MANAGER_COMMANDMANAGER_H
#define TASK_MANAGER_COMMANDMANAGER_H

#include <memory>

#include "entities/Entity.h"
#include "entities/Project.h"
#include "entities/Task.h"
#include "entities/User.h"
#include "managers/DbManager.h"
#include "database/factories/DbCommandFactory.h"

template<typename Connection, typename ResultSet, typename DbCallback, typename HistoryCallback>
class CommandManager {
 private:
  DbConfig _dbConfig;
  std::unique_ptr<DbConnector<Connection, ResultSet, DbCallback>> _dbConnector;
  std::unique_ptr<DbCommandFactory<Connection, ResultSet, DbCallback>> _userDbCommandFactory;
  std::unique_ptr<DbCommandFactory<Connection, ResultSet, DbCallback>> _taskDbCommandFactory;
  std::unique_ptr<DbCommandFactory<Connection, ResultSet, DbCallback>> _projectDbCommandFactory;
  std::unique_ptr<DbManager<Connection, ResultSet, DbCallback>> _dbManager;
  std::unique_ptr<NotificationManager> _notificationManager;
  std::unique_ptr<HistoryManager<HistoryCallback>> _historyManager;

 public:
  explicit CommandManager(std::string);

  void addSubscriber(std::shared_ptr<Subscriber>);
  void removeSubscriber(std::shared_ptr<Subscriber>);

  bool addUser(std::shared_ptr<User>, std::shared_ptr<User> user);
  std::shared_ptr<User> getUserByName(std::string name);
  std::shared_ptr<User> getUserById(int id);
  bool updateUserByName(std::shared_ptr<User> user, std::string name);
  bool deleteUserByName(std::string name);
  bool deleteUserById(int id);

  bool addProject(std::shared_ptr<Task> task);
  std::shared_ptr<Task> getProjectById(int id);
  bool updateProjectById(std::shared_ptr<Task> task, int id);
  bool deleteProjectById(int id);

  bool addTask(std::shared_ptr<Task> task);
  std::shared_ptr<Task> getTaskById(int id);
  bool updateTaskById(std::shared_ptr<Task> task, int id);
  bool deleteTaskById(int id);
};
#endif //TASK_MANAGER_COMMANDMANAGER_H
