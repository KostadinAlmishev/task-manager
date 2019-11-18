//
// Created by Konstantin Pronin on 06.11.2019.
//

#ifndef TASKMANAGER_INCLUDE_TRACKING_SUBSCRIBER_H_
#define TASKMANAGER_INCLUDE_TRACKING_SUBSCRIBER_H_

#include "entity/Entity.h"
#include "database/commands/DbCommand.h"

class Subscriber {
 public:
  virtual void update(Entity &, DbCommand &) = 0;
  virtual ~Subscriber() = default;
};
#endif //TASKMANAGER_INCLUDE_TRACKING_SUBSCRIBER_H_
