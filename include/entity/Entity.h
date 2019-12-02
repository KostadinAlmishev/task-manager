//
// Created by Konstantin Pronin on 05.11.2019.
//

#ifndef TASKMANAGER_INCLUDE_ENTITY_ENTITY_H_
#define TASKMANAGER_INCLUDE_ENTITY_ENTITY_H_
#include <string>

class Entity {
 private:
  long _id;

 public:
  Entity() = default;
  explicit Entity(long id);
  Entity(const Entity &) = default;
  long getId() const noexcept;
  void setId(long id) noexcept;

  virtual std::string toString() const = 0;

  bool operator==(const Entity& rhs) const;

  virtual ~Entity() = default;
};
#endif //TASKMANAGER_INCLUDE_ENTITY_ENTITY_H_
