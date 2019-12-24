//
// Created by Konstantin Pronin on 18.12.2019.
//
#include "PgCallbacks.h"

PgCallbacks::Connection *PgCallbacks::connect(const DbConfig &dbConfig) {
  auto conn = PQsetdbLogin(dbConfig.getHost().c_str(),
                           dbConfig.getPort().c_str(),
                           nullptr,
                           nullptr,
                           dbConfig.getDbName().c_str(),
                           dbConfig.getUser().c_str(),
                           dbConfig.getPassword().c_str());

  if (PQstatus(conn) != CONNECTION_OK) {
    free(conn);
    throw std::runtime_error(PQerrorMessage(conn));
  }

  return conn;
}

PgCallbacks::ResultSet *PgCallbacks::execute(Connection *conn, std::string query) {
  PQsendQuery(conn, query.c_str());

  while (auto result = PQgetResult(conn)) {
    if (PQresultStatus(result) == PGRES_FATAL_ERROR) {
      clearResult(result);
      free(conn);
      throw std::runtime_error(PQresultErrorMessage(result));
    }
    return result;
  }

  return nullptr;
}

void PgCallbacks::free(Connection *conn) {
  PQfinish(conn);
}

void PgCallbacks::clearResult(ResultSet *result) {
  PQclear(result);
}

std::unique_ptr<User> PgCallbacks::parseToUser(ResultSet *result) {
  if (PQresultStatus(result) != PGRES_TUPLES_OK) {
    clearResult(result);
    throw std::runtime_error(PQresultErrorMessage(result));
  }

  int rowsCount = PQntuples(result);
  int fieldsCount = PQnfields(result);
  std::unique_ptr<User> user = std::make_unique<User>();
  user->setId(-1);


  if (rowsCount < 1 || fieldsCount != 4) {
    return user;
  }

  char *end;
  long id = strtol(PQgetvalue(result, 0, 0), &end, 10);
  user->setId(id);
  user->setName(PQgetvalue(result, 0, 1));
  user->setPassword(PQgetvalue(result, 0, 2));
  user->setEmail(PQgetvalue(result, 0, 3));

  clearResult(result);
  return user;
}

std::unique_ptr<Project> PgCallbacks::parseToProject(ResultSet *result) {
  if (PQresultStatus(result) != PGRES_TUPLES_OK) {
    clearResult(result);
    throw std::runtime_error(PQresultErrorMessage(result));
  }

  int rowsCount = PQntuples(result);
  int fieldsCount = PQnfields(result);
  std::unique_ptr<Project> project = std::make_unique<Project>();
  project->setId(-1);

  if (rowsCount < 1 || fieldsCount != 3) {
    return project;
  }

  char *end;
  long id = strtol(PQgetvalue(result, 0, 0), &end, 10);
  project->setId(id);
  project->setName(PQgetvalue(result, 0, 1));
  project->setDescription(PQgetvalue(result, 0, 2));

  clearResult(result);
  return project;
}

std::unique_ptr<Task> PgCallbacks::parseToTask(ResultSet *result) {
  if (PQresultStatus(result) != PGRES_TUPLES_OK) {
    clearResult(result);
    throw std::runtime_error(PQresultErrorMessage(result));
  }

  int rowsCount = PQntuples(result);
  int fieldsCount = PQnfields(result);
  std::unique_ptr<Task> task = std::make_unique<Task>();
  task->setId(-1);

  if (rowsCount < 1 || fieldsCount != 5) {
    return task;
  }

  char *end;
  long id = strtol(PQgetvalue(result, 0, 0), &end, 10);
  long project_id = strtol(PQgetvalue(result, 0, 3), &end, 10);
  long user_id = strtol(PQgetvalue(result, 0, 4), &end, 10);
  task->setId(id);
  task->setProjectId(project_id);
  task->setCreatorId(user_id);
  task->setName(PQgetvalue(result, 0, 1));
  task->setDescription(PQgetvalue(result, 0, 2));

  clearResult(result);
  return task;
}