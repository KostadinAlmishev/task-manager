//
// Created by Konstantin Pronin on 05.11.2019.
//

#ifndef TASKMANAGER_INCLUDE_TRACKING_NOTIFIER_H_
#define TASKMANAGER_INCLUDE_TRACKING_NOTIFIER_H_

#include <vector>
#include <memory>

#include "database/commands/DbCommand.h"
#include "entities/Entity.h"
#include "tracking/Subscriber.h"
#include "entities/User.h"

class NotificationManager {
 private:
  std::vector<std::shared_ptr<Subscriber>> _subscribers;

 public:
  NotificationManager() = default;
  explicit NotificationManager(std::vector<std::shared_ptr<Subscriber>>);
  virtual void notifyAll(User &, Entity &) const;
  virtual void subscribe(std::shared_ptr<Subscriber>);
  virtual void unsubscribe(std::shared_ptr<Subscriber>);
  virtual ~NotificationManager() = default;
};

#endif //TASKMANAGER_INCLUDE_TRACKING_NOTIFIER_H_
