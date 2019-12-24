//
// Created by Konstantin Pronin on 08.12.2019.
//

#ifndef TASKMANAGER_INCLUDE_DATABASE_COMMANDS_TASK_ADDTASKCOMMAND_H_
#define TASKMANAGER_INCLUDE_DATABASE_COMMANDS_TASK_ADDTASKCOMMAND_H_

#include <functional>
#include <memory>
#include <utility>

#include "database/commands/DbCommand.h"
#include "entities/Task.h"

template<typename Callback>
class AddTaskCommand : public DbCommand<Callback> {
 private:
  std::shared_ptr<Entity> _task;

 public:
  AddTaskCommand(DbConnector<Callback> &, std::shared_ptr<Entity>);

  void saveBackUp() override;
  void undo() const override;
  void execute() const override;

  ~AddTaskCommand() = default;
};

template<typename Callback>
AddTaskCommand<Callback>::AddTaskCommand(DbConnector<Callback> &dbConnector,
                                         std::shared_ptr<Entity> task)
    : DbCommand<Callback>(dbConnector), _task(std::move(task)) {}

template<typename Callback>
void AddTaskCommand<Callback>::saveBackUp() {}

template<typename Callback>
void AddTaskCommand<Callback>::undo() const {
  std::vector<Descriptor> descriptors = _task->createDescriptors();
  std::string sql =
      "delete from \"" + this->_dbConnector.getDbName() + "\".\"TASKS\" where "
          + descriptors[1].field + " = \'"
          + descriptors[1].value
          + "\';";
  this->executeQuery(sql);
}

template<typename Callback>
void AddTaskCommand<Callback>::execute() const {
  std::vector<Descriptor> descriptors = _task->createDescriptors();
  std::string sql =
      "insert into \"" + this->_dbConnector.getDbName() + "\".\"TASKS\" ("
          + descriptors[1].field + ", "
          + descriptors[2].field + ", "
          + descriptors[3].field + ", "
          + descriptors[4].field + ") VALUES (\'"
          + descriptors[1].value + "\',\'"
          + descriptors[2].value + "\',\'"
          + descriptors[3].value + "\',\'"
          + descriptors[4].value + "\');";
  this->executeQuery(sql);
}
#endif //TASKMANAGER_INCLUDE_DATABASE_COMMANDS_TASK_ADDTASKCOMMAND_H_
