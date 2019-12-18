//
// Created by Konstantin Pronin on 05.11.2019.
//

#ifndef TASKMANAGER_INCLUDE_ENTITY_TASK_H_
#define TASKMANAGER_INCLUDE_ENTITY_TASK_H_

#include "entities/Entity.h"

class Task : public Entity {
 private:
  long creatorId;
  long projectId;
  std::string name;
  std::string description;
 public:
  Task() : creatorId(-1), projectId(-1) {}
  Task(const Task&) = default;
  void setCreatorId(long creatorId);
  long getCreatorId() const;
  void setProjectId(long projectId);
  long getProjectId() const;
  void setName(std::string name);
  std::string getName() const;
  void setDescription(std::string description);
  std::string getDescription() const;
  std::vector<Descriptor> createDescriptors() const override;
};

#endif //TASKMANAGER_INCLUDE_ENTITY_TASK_H_
