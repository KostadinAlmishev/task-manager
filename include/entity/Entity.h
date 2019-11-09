//
// Created by Konstantin Pronin on 05.11.2019.
//

#ifndef TASKMANAGER_INCLUDE_ENTITY_ENTITY_H_
#define TASKMANAGER_INCLUDE_ENTITY_ENTITY_H_

class Entity {
 private:
  long _id;

 public:
  long getId() const noexcept;
  void setId() noexcept;
};
#endif //TASKMANAGER_INCLUDE_ENTITY_ENTITY_H_
