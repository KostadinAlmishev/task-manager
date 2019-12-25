#ifndef TASK_MANAGER_COMMANDMANAGER_H
#define TASK_MANAGER_COMMANDMANAGER_H

#include <fstream>
#include <memory>

#include "database/factories/DbCommandFactory.h"
#include "database/factories/ProjectDbCommandFactory.h"
#include "database/factories/TaskDbCommandFactory.h"
#include "database/factories/UserDbCommandFactory.h"
#include "entities/Entity.h"
#include "entities/Project.h"
#include "entities/Task.h"
#include "entities/User.h"
#include "managers/DbManager.h"
#include "PgCallbacks.h"

class CommandManager {
 private:
  std::unique_ptr<DbConfig> _dbConfig;
  std::unique_ptr<DbConnector<PgCallbacks>> _dbConnector;
  std::unique_ptr<DbCommandFactory<PgCallbacks>> _userDbCommandFactory;
  std::unique_ptr<DbCommandFactory<PgCallbacks>> _taskDbCommandFactory;
  std::unique_ptr<DbCommandFactory<PgCallbacks>> _projectDbCommandFactory;
  std::unique_ptr<DbManager> _dbManager;
  std::unique_ptr<NotificationManager> _notificationManager;
  std::unique_ptr<HistoryManager> _historyManager;

 public:
  explicit CommandManager(const std::string&);

  void addSubscriber(std::shared_ptr<Subscriber>);
  void removeSubscriber(std::shared_ptr<Subscriber>);

  void addUser(std::shared_ptr<User>, std::shared_ptr<User>);
  std::shared_ptr<Entity> getUserByName(std::string);
  std::shared_ptr<Entity> getUserById(int);
  void updateUser(std::shared_ptr<User>, std::shared_ptr<Entity>);
  void deleteUser(std::shared_ptr<User>, std::shared_ptr<Entity>);

  void addTask(std::shared_ptr<User>, std::shared_ptr<Task> addedTask);
  std::shared_ptr<Entity> getTaskByName(std::string);
  std::shared_ptr<Entity> getTaskById(int);
  void updateTask(std::shared_ptr<User>, std::shared_ptr<Entity>);
  void deleteTask(std::shared_ptr<User>, std::shared_ptr<Entity>);

  void addProject(std::shared_ptr<User>, std::shared_ptr<Project>);
  std::shared_ptr<Entity> getProjectByName(std::string);
  std::shared_ptr<Entity> getProjectById(int);
  void updateProject(std::shared_ptr<User>, std::shared_ptr<Entity>);
  void deleteProject(std::shared_ptr<User>, std::shared_ptr<Entity>);

  void undo(std::string);
};

#endif //TASK_MANAGER_COMMANDMANAGER_H
