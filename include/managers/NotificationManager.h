//
// Created by Konstantin Pronin on 05.11.2019.
//

#ifndef TASKMANAGER_INCLUDE_TRACKING_NOTIFIER_H_
#define TASKMANAGER_INCLUDE_TRACKING_NOTIFIER_H_

#include <vector>
#include <memory>

#include "database/commands/DbCommand.h"
#include "entity/Entity.h"
#include "tracking/Subscriber.h"

class NotificationManager {
 private:
  std::vector<std::shared_ptr<Subscriber>> _subscribers;

 public:
  NotificationManager() = default;
  explicit NotificationManager(std::vector<std::shared_ptr<Subscriber>>);
  virtual void notifyAll(Entity &, Entity &) const;
  virtual void subscribe(Subscriber &);
  virtual void unsubscribe(Subscriber &);
  virtual ~NotificationManager() = default;
};

#endif //TASKMANAGER_INCLUDE_TRACKING_NOTIFIER_H_
