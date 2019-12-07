//
// Created by Konstantin Pronin on 05.11.2019.
//

#ifndef TASKMANAGER_INCLUDE_ENTITY_PROJECT_H_
#define TASKMANAGER_INCLUDE_ENTITY_PROJECT_H_

#include "entities/Entity.h"

class Project : public Entity {
 private:
  std::string name;
  std::string description;
 public:
  std::string getName() const;
  std::string getDescription() const;
  void setName(std::string name);
  void setDescription(std::string description);
};

#endif //TASKMANAGER_INCLUDE_ENTITY_PROJECT_H_
