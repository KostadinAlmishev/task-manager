//
// Created by Konstantin Pronin on 08.12.2019.
//

#ifndef TASKMANAGER_INCLUDE_DATABASE_COMMANDS_TASK_GETTASKBYNAMECOMMAND_H_
#define TASKMANAGER_INCLUDE_DATABASE_COMMANDS_TASK_GETTASKBYNAMECOMMAND_H_

#include <memory>
#include <utility>

#include "database/commands/DbCommand.h"
#include "entities/Task.h"

template<typename Callback>
class GetTaskByNameCommand : public DbCommand<Callback> {
 private:
  std::string _name;
  std::shared_ptr<Entity> &_task;

 public:
  GetTaskByNameCommand(DbConnector<Callback> &,
                       std::string,
                       std::shared_ptr<Entity> &);

  void saveBackUp() override;
  void undo() const override;
  void execute() const override;

  ~GetTaskByNameCommand() = default;
};

template<typename Callback>
GetTaskByNameCommand<Callback>::GetTaskByNameCommand(DbConnector<Callback> &dbConnector,
                                                     std::string name,
                                                     std::shared_ptr<Entity> &task)
    : DbCommand<Callback>(dbConnector),
      _name(std::move(name)),
      _task(task) {}

template<typename Callback>
void GetTaskByNameCommand<Callback>::saveBackUp() {}

template<typename Callback>
void GetTaskByNameCommand<Callback>::undo() const {}

template<typename Callback>
void GetTaskByNameCommand<Callback>::execute() const {
  std::string sql =
      "select * from \"" + this->_dbConnector.getDbName() + "\".\"TASKS\" where NAME = \'" + _name
          + "\';";
  auto result = this->executeQuery(sql);
  _task = std::move(Callback::parseToTask(result));
}

#endif //TASKMANAGER_INCLUDE_DATABASE_COMMANDS_TASK_GETTASKBYNAMECOMMAND_H_
