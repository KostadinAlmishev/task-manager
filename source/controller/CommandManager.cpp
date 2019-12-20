#include <fstream>

#include "controller/CommandManager.h"
#include "database/factories/ProjectDbCommandFactory.h"
#include "database/factories/TaskDbCommandFactory.h"
#include "database/factories/UserDbCommandFactory.h"

template<typename Connection, typename ResultSet, typename DbCallback, typename HistoryCallback>
CommandManager<Connection, ResultSet, DbCallback, HistoryCallback>::CommandManager(std::string dbConfigPath) {
  std::ifstream dbProperties(dbConfigPath);

  if (!dbProperties) {
    return;
  }

  std::streambuf *buffer = dbProperties.rdbuf();
  _dbConfig(*buffer);
  _dbConfig.readConfigFromFile();
  _dbConnector = std::make_unique<DbConnector<Connection, ResultSet, DbCallback>>(_dbConfig);
  _userDbCommandFactory = std::make_unique<UserDbCommandFactory<Connection, ResultSet, DbCallback>>(*_dbConnector);
  _taskDbCommandFactory = std::make_unique<TaskDbCommandFactory<Connection, ResultSet, DbCallback>>(*_dbConnector);
  _projectDbCommandFactory = std::make_unique<ProjectDbCommandFactory<Connection, ResultSet, DbCallback>>(*_dbConnector);
  _dbManager = std::make_unique<DbManager<Connection, ResultSet, DbCallback>>();
  _notificationManager = std::make_unique<NotificationManager>();
  _historyManager = std::make_unique<HistoryManager<HistoryCallback>>();
}

template<typename Connection, typename ResultSet, typename DbCallback, typename HistoryCallback>
void CommandManager<Connection, ResultSet, DbCallback, HistoryCallback>::addSubscriber(std::shared_ptr<Subscriber> subscriber) {
  _notificationManager->subscribe(subscriber);
}

template<typename Connection, typename ResultSet, typename DbCallback, typename HistoryCallback>
void CommandManager<Connection, ResultSet, DbCallback, HistoryCallback>::removeSubscriber(std::shared_ptr<Subscriber> subscriber) {
  _notificationManager->unsubscribe(subscriber);
}

template<typename Connection, typename ResultSet, typename DbCallback, typename HistoryCallback>
bool CommandManager<Connection, ResultSet, DbCallback, HistoryCallback>::addUser(std::shared_ptr<User> currentUser, std::shared_ptr<User> user) {
  std::shared_ptr<DbCommand<Connection, ResultSet, DbCallback>> command = _userDbCommandFactory->createAddCommand(user);
  _dbManager.setCommand(command);
  _dbManager.executeCommand();
  _notificationManager->notifyAll(*currentUser, *user);
  _historyManager->push(user);
}




