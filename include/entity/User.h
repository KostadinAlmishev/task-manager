//
// Created by Konstantin Pronin on 05.11.2019.
//

#ifndef TASKMANAGER_INCLUDE_ENTITY_USER_H_
#define TASKMANAGER_INCLUDE_ENTITY_USER_H_

class User : public Entity {
 public:
  std::string getName() const;
};

#endif //TASKMANAGER_INCLUDE_ENTITY_USER_H_
