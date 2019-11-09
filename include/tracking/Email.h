//
// Created by Konstantin Pronin on 05.11.2019.
//

#ifndef TASKMANAGER_INCLUDE_TRACKING_EMAIL_H_
#define TASKMANAGER_INCLUDE_TRACKING_EMAIL_H_

#include "tracking/Subscriber.h"

class Email : public Subscriber {
 private:
  std::string server;
 public:
  void update(Entity, DbCommand) override;
  virtual Message createMessage(Entity, DbCommand) const;
  virtual void sendMessage(Message);
};
#endif //TASKMANAGER_INCLUDE_TRACKING_EMAIL_H_
