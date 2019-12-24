//
// Created by Konstantin Pronin on 08.12.2019.
//

#ifndef TASKMANAGER_INCLUDE_DATABASE_COMMANDS_TASK_DELETETASKCOMMAND_H_
#define TASKMANAGER_INCLUDE_DATABASE_COMMANDS_TASK_DELETETASKCOMMAND_H_

#include <functional>
#include <memory>
#include <utility>

#include "database/commands/DbCommand.h"
#include "entities/Task.h"

template<typename Callback>
class DeleteTaskCommand : public DbCommand<Callback> {
 private:
  std::shared_ptr<Entity> _task;
  std::unique_ptr<Task> _backUp;

 public:
  DeleteTaskCommand(DbConnector<Callback> &, std::shared_ptr<Entity>);

  void saveBackUp() override;
  void undo() const override;
  void execute() const override;

  ~DeleteTaskCommand() = default;
};

template<typename Callback>
DeleteTaskCommand<Callback>::DeleteTaskCommand(DbConnector<Callback> &dbConnector,
                                               std::shared_ptr<Entity> task)
    : DbCommand<Callback>(dbConnector), _task(std::move(task)) {}

template<typename Callback>
void DeleteTaskCommand<Callback>::saveBackUp() {
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
void DeleteTaskCommand<Callback>::undo() const {
  std::string sql =
      "insert into \"" + this->_dbConnector.getDbName() + "\".\"TASKS\" VALUES ("
          + _backUp->getName() + ","
          + _backUp->getDescription() + ","
          + _backUp->getProjectId() + ","
          + _backUp->getCreatorId() + ");";
  this->executeQuery(sql);
}

template<typename Callback>
void DeleteTaskCommand<Callback>::execute() const {
  std::vector<Descriptor> descriptors = _task->createDescriptors();
  std::string sql =
      "delete from \"" + this->_dbConnector.getDbName() + "\".\"TASKS\" where "
          + descriptors[1].field + " = \'"
          + descriptors[1].value
          + "\';";
  this->executeQuery(sql);
}

#endif //TASKMANAGER_INCLUDE_DATABASE_COMMANDS_TASK_DELETETASKCOMMAND_H_
