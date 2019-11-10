//
// Created by Konstantin Pronin on 05.11.2019.
//

#ifndef TASKMANAGER_INCLUDE_DATABASE_DBCONNECTION_H_
#define TASKMANAGER_INCLUDE_DATABASE_DBCONNECTION_H_

#include <vector>

//здесь должен быть класс библиотеки (например, libpq++)
class DbConnection{
  virtual std::vector<std::string>* execute() const;
};

#endif //TASKMANAGER_INCLUDE_DATABASE_DBCONNECTION_H_
