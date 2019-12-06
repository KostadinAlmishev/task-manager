//
// Created by Konstantin Pronin on 05.11.2019.
//

#ifndef TASKMANAGER_INCLUDE_TRACKING_EMAIL_H_
#define TASKMANAGER_INCLUDE_TRACKING_EMAIL_H_

#include <memory>

#include "tracking/Message.h"
#include "tracking/Subscriber.h"
#include <entity/User.h>

class Email : public Subscriber {
 private:
  std::string _server;
  unsigned int _port;
  std::string _user;
  std::string _password;
  std::function<bool(std::string, int, std::string, std::string, std::unique_ptr<Message> &&)> _sendCallback;
 public:
  void update(const User &, const Entity &) override;
  virtual std::unique_ptr<Message> createMessage(const User &, const Entity &) const;
  virtual bool sendMessage(std::unique_ptr<Message> &&);
};
#endif //TASKMANAGER_INCLUDE_TRACKING_EMAIL_H_
