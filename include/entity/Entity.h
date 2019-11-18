//
// Created by Konstantin Pronin on 05.11.2019.
//

#ifndef TASKMANAGER_INCLUDE_ENTITY_ENTITY_H_
#define TASKMANAGER_INCLUDE_ENTITY_ENTITY_H_

class Entity {
 private:
  long _id;

 public:
  Entity();
  Entity(const Entity &);
  long getId() const noexcept;
  void setId() noexcept;

  bool operator==(const Entity& rhs) const;
};
#endif //TASKMANAGER_INCLUDE_ENTITY_ENTITY_H_
