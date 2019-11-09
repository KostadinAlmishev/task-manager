//
// Created by Konstantin Pronin on 08.11.2019.
//

#ifndef TASKMANAGER_INCLUDE_DATABASE_COMMANDS_DELETEPROJECTCOMMAND_H_
#define TASKMANAGER_INCLUDE_DATABASE_COMMANDS_DELETEPROJECTCOMMAND_H_

#include "database/commands/DbCommand.h"

class DeleteProjectCommand : public DbCommand {
 public:
  DeleteProjectCommand(DbConnector *);
  void saveBackUp() override;
  void execute() const override;
};

#endif //TASKMANAGER_INCLUDE_DATABASE_COMMANDS_DELETEPROJECTCOMMAND_H_
