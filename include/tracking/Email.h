//
// Created by Konstantin Pronin on 05.11.2019.
//

#ifndef TASKMANAGER_INCLUDE_TRACKING_EMAIL_H_
#define TASKMANAGER_INCLUDE_TRACKING_EMAIL_H_

#include "tracking/Subscriber.h"
#include "tracking/Message.h"

class Email : public Subscriber {
 private:
  std::string _server;
  unsigned int _port;
  std::string _user;
  std::string _password;
  std::function<bool(std::string, int, std::string, std::string, const Message&)> _sendCallback;
 public:
  void update(const Entity &, const Entity &) override;
  virtual Message createMessage(const Entity &, const Entity &) const;
  virtual bool sendMessage(Message &);
};
#endif //TASKMANAGER_INCLUDE_TRACKING_EMAIL_H_
