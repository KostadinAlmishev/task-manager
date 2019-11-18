//
// Created by Konstantin Pronin on 05.11.2019.
//

#ifndef TASKMANAGER_INCLUDE_TRACKING_NOTIFIER_H_
#define TASKMANAGER_INCLUDE_TRACKING_NOTIFIER_H_

#include <vector>

#include "database/commands/DbCommand.h"
#include "entity/Entity.h"
#include "tracking/Subscriber.h"

class Notifier {
 private:
  std::vector<Subscriber *> subscribers;

 public:
  Notifier(std::vector<Subscriber *> &);
  virtual void notifyAll(Entity &, DbCommand &) const;
  virtual void subscribe(Subscriber &) const;
  virtual void unsubscribe(Subscriber &) const;
  virtual ~Notifier() = default;
};

#endif //TASKMANAGER_INCLUDE_TRACKING_NOTIFIER_H_
