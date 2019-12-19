//
// Created by Konstantin Pronin on 05.11.2019.
//
#include <iostream>
#include <fstream>
#include <memory>
#include <CurlCallbacks.h>

#include "database/connection/DbConnector.h"
#include "database/factories/UserDbCommandFactory.h"
#include "managers/DbManager.h"
#include "PgCallbacks.h"
#include "tracking/Email.h"


void showDBExamples() {
  //example of execution db user commands
  std::ifstream dbProperties("../resources/dbProperties.txt");

  if (!dbProperties) {
    return;
  }
  std::streambuf *buffer = dbProperties.rdbuf();

  DbConfig dbConfig(*buffer);
  dbConfig.readConfigFromFile();

  DbConnector<PGconn, PGresult, PgCallbacks> dbConnector(dbConfig);
  dbConnector.initializeConnectionPool();
  auto userDbCommandFactory = new UserDbCommandFactory<PGconn, PGresult, PgCallbacks>(dbConnector);
  DbManager<PGconn, PGresult, PgCallbacks> dbManager;

  auto user = std::make_shared<User>();
  user->setName("test");
  user->setPassword("test");
  user->setEmail("sayfer97@yandex.ru");

  //add
  std::shared_ptr<DbCommand<PGconn, PGresult, PgCallbacks>> command = userDbCommandFactory->createAddCommand(user);
  dbManager.setCommand(command);
  dbManager.executeCommand();

  //getByName
  std::shared_ptr<Entity> stored = std::make_shared<User>();
  command = userDbCommandFactory->createGetCommand(user->getName(), stored);
  dbManager.setCommand(command);
  dbManager.executeCommand();
  std::cout << stored->toString() << std::endl;

  //modify
  user->setId(stored->getId());
  user->setPassword("CipherPassword");
  command = userDbCommandFactory->createModifyCommand(user);
  dbManager.setCommand(command);
  dbManager.executeCommand();

  //getById
  command = userDbCommandFactory->createGetCommand(stored->getId(), stored, -1);
  dbManager.setCommand(command);
  dbManager.executeCommand();
  std::cout << stored->toString() << std::endl;

  //delete
  command = userDbCommandFactory->createDeleteCommand(user);
  dbManager.setCommand(command);
  dbManager.executeCommand();

  dbProperties.close();
}

void showEmailExamples() {
  //example of sending emails
  std::string host = "smtp.yandex.ru";
  unsigned int port = 465;
  std::string login = "technopark-project-test@yandex.ru";
  std::string password = "closed$PSWD";
  std::shared_ptr<Subscriber> email = std::make_shared<Email<CurlCallbacks>>(host, port, login, password);
  NotificationManager notificationManager;
  notificationManager.subscribe(email);

  auto user = std::make_shared<User>();
  user->setName("test");
  user->setPassword("test");
  user->setEmail("sayfer97@yandex.ru");
  notificationManager.notifyAll(*user, *user);
}

int main() {
  showDBExamples();
  showEmailExamples();
  return 0;
}