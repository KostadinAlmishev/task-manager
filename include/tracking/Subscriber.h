//
// Created by Konstantin Pronin on 06.11.2019.
//

#ifndef TASKMANAGER_INCLUDE_TRACKING_SUBSCRIBER_H_
#define TASKMANAGER_INCLUDE_TRACKING_SUBSCRIBER_H_

#include "entities/Entity.h"
#include "database/commands/DbCommand.h"
#include "entities/User.h"

class Subscriber {
 public:
  Subscriber() = default;
  Subscriber(const Subscriber &) = default;
  virtual void update(const User &, const Entity &) = 0;
  virtual ~Subscriber() = default;
};
#endif //TASKMANAGER_INCLUDE_TRACKING_SUBSCRIBER_H_
