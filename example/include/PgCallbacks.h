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
  static Connection *connect(const DbConfig &);
  static ResultSet *execute(Connection *conn, std::string);
  static void free(Connection *);
  static void clearResult(ResultSet *);
  static std::unique_ptr<User> parseToUser(ResultSet *);
  static std::unique_ptr<Project> parseToProject(ResultSet *);
  static std::unique_ptr<Task> parseToTask(ResultSet *);
};

#endif //TASKMANAGER_EXAMPLE_INCLUDE_PGCALLBACKS_H_
