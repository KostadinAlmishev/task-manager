//
// Created by Konstantin Pronin on 08.12.2019.
//

#ifndef TASKMANAGER_INCLUDE_DATABASE_COMMANDS_TASK_MODIFYTASKCOMMAND_H_
#define TASKMANAGER_INCLUDE_DATABASE_COMMANDS_TASK_MODIFYTASKCOMMAND_H_

#include <functional>
#include <memory>
#include <utility>

#include "database/commands/DbCommand.h"
#include "entities/Task.h"

template<typename Callback>
class ModifyTaskCommand : public DbCommand<Callback> {
 private:
  std::shared_ptr<Entity> _task;
  std::unique_ptr<Task> _backUp;

 public:
  ModifyTaskCommand(DbConnector<Callback> &, std::shared_ptr<Entity>);

  void saveBackUp() override;
  void undo() const override;
  void execute() const override;

  ~ModifyTaskCommand() = default;
};

template<typename Callback>
ModifyTaskCommand<Callback>::ModifyTaskCommand(DbConnector<Callback> &dbConnector,
                                               std::shared_ptr<Entity> task)
    : DbCommand<Callback>(dbConnector), _task(std::move(task)) {}

template<typename Callback>
void ModifyTaskCommand<Callback>::saveBackUp() {
  std::vector<Descriptor> descriptors = _task->createDescriptors();
  std::string sql =
      "select * from \"" + this->_dbConnector.getDbName() + "\".\"TASKS\" where "
          + descriptors[1].field + " = \'"
          + descriptors[1].value
          + "\';";
  auto result = this->executeQuery(sql);
  _backUp = std::move(Callback::parseToTask(result));
}

template<typename Callback>
void ModifyTaskCommand<Callback>::undo() const {
  std::vector<Descriptor> descriptors = _backUp->createDescriptors();
  std::string sql =
      "update \"" + this->_dbConnector.getDbName() + "\".\"TASKS\" set "
          + descriptors[1].field + " = \'"
          + descriptors[1].value + "\', "
          + descriptors[2].field + " = \'"
          + descriptors[2].value + "\', "
          + descriptors[3].field + " = \'"
          + descriptors[3].value + "\', "
          + descriptors[4].field + " = \'"
          + descriptors[4].value + "\' where "
          + descriptors[0].field + " = \'"
          + descriptors[0].value + "\';";
  this->executeQuery(sql);
}

template<typename Callback>
void ModifyTaskCommand<Callback>::execute() const {
  std::vector<Descriptor> descriptors = _task->createDescriptors();
  std::string sql =
      "update \"" + this->_dbConnector.getDbName() + "\".\"TASKS\" set "
          + descriptors[1].field + " = \'"
          + descriptors[1].value + "\', "
          + descriptors[2].field + " = \'"
          + descriptors[2].value + "\', "
          + descriptors[3].field + " = \'"
          + descriptors[3].value + "\', "
          + descriptors[4].field + " = \'"
          + descriptors[4].value + "\' where "
          + descriptors[0].field + " = \'"
          + descriptors[0].value + "\';";
  this->executeQuery(sql);
}

#endif //TASKMANAGER_INCLUDE_DATABASE_COMMANDS_TASK_MODIFYTASKCOMMAND_H_
