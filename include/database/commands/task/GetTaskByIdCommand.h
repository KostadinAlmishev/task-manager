//
// Created by Konstantin Pronin on 08.12.2019.
//

#ifndef TASKMANAGER_INCLUDE_DATABASE_COMMANDS_TASK_GETTASKBYIDCOMMAND_H_
#define TASKMANAGER_INCLUDE_DATABASE_COMMANDS_TASK_GETTASKBYIDCOMMAND_H_

#include <memory>
#include <utility>

#include "database/commands/DbCommand.h"
#include "entities/Task.h"

template<typename Callback>
class GetTaskByIdCommand : public DbCommand<Callback> {
 private:
  long _id;
  std::shared_ptr<Entity> &_task;

 public:
  GetTaskByIdCommand(DbConnector<Callback> &,
                     long,
                     std::shared_ptr<Entity> &);

  void saveBackUp() override;
  void undo() const override;
  void execute() const override;

  ~GetTaskByIdCommand() = default;
};

template<typename Callback>
GetTaskByIdCommand<Callback>::GetTaskByIdCommand(DbConnector<Callback> &dbConnector,
                                                 long id,
                                                 std::shared_ptr<Entity> &task)
    : DbCommand<Callback>(dbConnector),
      _id(id),
      _task(task) {}

template<typename Callback>
void GetTaskByIdCommand<Callback>::saveBackUp() {}

template<typename Callback>
void GetTaskByIdCommand<Callback>::undo() const {}

template<typename Callback>
void GetTaskByIdCommand<Callback>::execute() const {
  std::string sql =
      "select * from \"" + this->_dbConnector.getDbName() + "\".\"TASKS\" where ID = \'" + std::to_string(_id)
          + "\';";
  auto result = this->executeQuery(sql);
  _task = std::move(Callback::parseToTask(result));
}
#endif //TASKMANAGER_INCLUDE_DATABASE_COMMANDS_TASK_GETTASKBYIDCOMMAND_H_
