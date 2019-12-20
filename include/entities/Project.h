#ifndef TASK_MANAGER_PROJECT_H
#define TASK_MANAGER_PROJECT_H

#include "entities/Entity.h"

class Project : public Entity {
 private:
  std::string name;
  std::string description;
 public:
  Project() = default;
  Project(const Project &) = default;
  std::string getName() const;
  std::string getDescription() const;
  void setName(std::string name);
  void setDescription(std::string description);
  std::string toString() const override;
  std::vector<Descriptor> createDescriptors() const override;
};

#endif //TASK_MANAGER_PROJECT_H

