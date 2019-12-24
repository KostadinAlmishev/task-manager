//
// Created by Konstantin Pronin on 21.12.2019.
//

#ifndef TASKMANAGER_INCLUDE_DATABASE_COMMANDS_IDBCOMMAND_H_
#define TASKMANAGER_INCLUDE_DATABASE_COMMANDS_IDBCOMMAND_H_

class IDbCommand {
 public:
  virtual void saveBackUp() = 0;
  virtual void undo() const = 0;
  virtual void execute() const = 0;
  virtual ~IDbCommand() = default;
};

#endif //TASKMANAGER_INCLUDE_DATABASE_COMMANDS_IDBCOMMAND_H_
