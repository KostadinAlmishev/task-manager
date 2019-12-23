//
// Created by Konstantin Pronin on 18.12.2019.
//

#ifndef TASKMANAGER_EXAMPLE_INCLUDE_PGCALLBACKS_H_
#define TASKMANAGER_EXAMPLE_INCLUDE_PGCALLBACKS_H_

#include <libpq-fe.h>

#include "database/config/DbConfig.h"
#include "entities/User.h"
#include "entities/Project.h"
#include "entities/Task.h"

class PgCallbacks {
 public:
  using ResultSet = PGresult;
  using Connection = PGconn;
  static PGconn *connect(const DbConfig &);
  static PGresult *execute(PGconn *conn, std::string);
  static void free(PGconn *);
  static void clearResult(PGresult *);
  static std::unique_ptr<User> parseToUser(PGresult *);
  static std::unique_ptr<Project> parseToProject(PGresult *);
  static std::unique_ptr<Task> parseToTask(PGresult *);
};

#endif //TASKMANAGER_EXAMPLE_INCLUDE_PGCALLBACKS_H_
