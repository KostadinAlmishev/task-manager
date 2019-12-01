//
// Created by Konstantin Pronin on 30.11.2019.
//


#include "tracking/Email.h"
#include "entity/User.h"

void Email::update(const Entity & user, const Entity & current) {
  Message msg = createMessage(user, current);
  sendMessage(msg);
}

Message Email::createMessage(const Entity &user, const Entity &info) const {
  std::string to = dynamic_cast<const User&> (user).getName();
}

bool Email::sendMessage(Message &msg) {
  //use boost asio
  return _sendCallback(_server, _port, _user, _password, msg);
}

