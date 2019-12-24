#include <utility>

#include "controller/CommandManager.h"

CommandManager::CommandManager(const std::string& dbConfigPath) {
  std::ifstream dbProperties(dbConfigPath);
  std::streambuf *buffer = dbProperties.rdbuf();
  _dbConfig = std::make_unique<DbConfig>(*buffer);
  _dbConfig->readConfigFromFile();
  _dbConnector = std::make_unique<DbConnector<PgCallbacks>>(*_dbConfig);
  _userDbCommandFactory = std::make_unique<UserDbCommandFactory<PgCallbacks>>(*_dbConnector);
  _taskDbCommandFactory = std::make_unique<TaskDbCommandFactory<PgCallbacks>>(*_dbConnector);
  _projectDbCommandFactory = std::make_unique<ProjectDbCommandFactory<PgCallbacks>>(*_dbConnector);
  _dbManager = std::make_unique<DbManager>();
  _notificationManager = std::make_unique<NotificationManager>();
  _historyManager = std::make_unique<HistoryManager>();
}

void CommandManager::addSubscriber(std::shared_ptr<Subscriber> subscriber) {
  _notificationManager->subscribe(std::move(subscriber));
}

void CommandManager::removeSubscriber(std::shared_ptr<Subscriber> subscriber) {
  _notificationManager->unsubscribe(std::move(subscriber));
}

void CommandManager::addUser(std::shared_ptr<User> currentUser, std::shared_ptr<User> addedUser) {
  std::shared_ptr<IDbCommand> command = _userDbCommandFactory->createAddCommand(addedUser);
  _dbManager->setCommand(command);
  _dbManager->executeCommand();
  _notificationManager->notifyAll(*currentUser, *addedUser);
  _historyManager->push(currentUser->getName(), command);
}

std::shared_ptr<Entity> CommandManager::getUserByName(std::string name) {
  std::shared_ptr<Entity> user = std::make_shared<User>();
  std::shared_ptr<IDbCommand> command = _userDbCommandFactory->createGetCommand(name, user);
  _dbManager->setCommand(command);
  _dbManager->executeCommand();
  return user;
}

std::shared_ptr<Entity> CommandManager::getUserById(int id) {
  std::shared_ptr<Entity> user = std::make_shared<User>();
  std::shared_ptr<IDbCommand> command = _userDbCommandFactory->createGetCommand(id, user, -1);
  _dbManager->setCommand(command);
  _dbManager->executeCommand();
  return user;
}

void CommandManager::updateUser(std::shared_ptr<User> currentUser, std::shared_ptr<User> updatedUser) {
  std::shared_ptr<IDbCommand> command = _userDbCommandFactory->createModifyCommand(updatedUser);
  _dbManager->setCommand(command);
  _dbManager->executeCommand();
  _notificationManager->notifyAll(*currentUser, *updatedUser);
  _historyManager->push(currentUser->getName(), command);
}

void CommandManager::deleteUser(std::shared_ptr<User> currentUser, std::shared_ptr<User> deletedUser) {
  std::shared_ptr<IDbCommand> command = _userDbCommandFactory->createDeleteCommand(deletedUser);
  _dbManager->setCommand(command);
  _dbManager->executeCommand();
  _notificationManager->notifyAll(*currentUser, *deletedUser);
  _historyManager->push(currentUser->getName(), command);
}

void CommandManager::addTask(std::shared_ptr<User> currentUser, std::shared_ptr<Task> addedTask) {
  std::shared_ptr<IDbCommand> command = _taskDbCommandFactory->createAddCommand(addedTask);
  _dbManager->setCommand(command);
  _dbManager->executeCommand();
  _notificationManager->notifyAll(*currentUser, *addedTask);
  _historyManager->push(currentUser->getName(), command);
}

std::shared_ptr<Entity> CommandManager::getTaskByName(std::string name) {
  std::shared_ptr<Entity> task = std::make_shared<Task>();
  std::shared_ptr<IDbCommand> command = _taskDbCommandFactory->createGetCommand(name, task);
  _dbManager->setCommand(command);
  _dbManager->executeCommand();
  return task;
}

std::shared_ptr<Entity> CommandManager::getTaskById(int id) {
  std::shared_ptr<Entity> task = std::make_shared<Task>();
  std::shared_ptr<IDbCommand> command = _taskDbCommandFactory->createGetCommand(id, task, -1);
  _dbManager->setCommand(command);
  _dbManager->executeCommand();
  return task;
}

void CommandManager::updateTask(std::shared_ptr<User> currentUser, std::shared_ptr<Task> updatedTask) {
  std::shared_ptr<IDbCommand> command = _taskDbCommandFactory->createModifyCommand(updatedTask);
  _dbManager->setCommand(command);
  _dbManager->executeCommand();
  _notificationManager->notifyAll(*currentUser, *updatedTask);
  _historyManager->push(currentUser->getName(), command);
}

void CommandManager::deleteTask(std::shared_ptr<User> currentUser, std::shared_ptr<Task> deletedTask) {
  std::shared_ptr<IDbCommand> command = _taskDbCommandFactory->createDeleteCommand(deletedTask);
  _dbManager->setCommand(command);
  _dbManager->executeCommand();
  _notificationManager->notifyAll(*currentUser, *deletedTask);
  _historyManager->push(currentUser->getName(), command);
}

void CommandManager::addProject(std::shared_ptr<User> currentUser, std::shared_ptr<Project> addedProject) {
  std::shared_ptr<IDbCommand> command = _projectDbCommandFactory->createAddCommand(addedProject);
  _dbManager->setCommand(command);
  _dbManager->executeCommand();
  _notificationManager->notifyAll(*currentUser, *addedProject);
  _historyManager->push(currentUser->getName(), command);
}

std::shared_ptr<Entity> CommandManager::getProjectByName(std::string name) {
  std::shared_ptr<Entity> project = std::make_shared<Project>();
  std::shared_ptr<IDbCommand> command = _projectDbCommandFactory->createGetCommand(name, project);
  _dbManager->setCommand(command);
  _dbManager->executeCommand();
  return project;
}

std::shared_ptr<Entity> CommandManager::getProjectById(int id) {
  std::shared_ptr<Entity> project = std::make_shared<Project>();
  std::shared_ptr<IDbCommand> command = _projectDbCommandFactory->createGetCommand(id, project, -1);
  _dbManager->setCommand(command);
  _dbManager->executeCommand();
  return project;
}

void CommandManager::updateProject(std::shared_ptr<User> currentUser, std::shared_ptr<Project> updatedProject) {
  std::shared_ptr<IDbCommand> command = _projectDbCommandFactory->createModifyCommand(updatedProject);
  _dbManager->setCommand(command);
  _dbManager->executeCommand();
  _notificationManager->notifyAll(*currentUser, *updatedProject);
  _historyManager->push(currentUser->getName(), command);
}

void CommandManager::deleteProject(std::shared_ptr<User> currentUser, std::shared_ptr<Project> deletedProject) {
  std::shared_ptr<IDbCommand> command = _projectDbCommandFactory->createDeleteCommand(deletedProject);
  _dbManager->setCommand(command);
  _dbManager->executeCommand();
  _notificationManager->notifyAll(*currentUser, *deletedProject);
  _historyManager->push(currentUser->getName(), command);
}

void CommandManager::undo(std::string username) {
  _historyManager->pop(username);
}







