//
// Created by Konstantin Pronin on 30.11.2019.
//


#include "tracking/Email.h"
#include "entities/User.h"

void Email::update(const User & user, const Entity & current) {
  auto msg = createMessage(user, current);
  sendMessage(std::move(msg));
}

std::unique_ptr<Message> Email::createMessage(const User &user, const Entity &info) const {
  std::string to = user.getEmail();
  std::string subject = "Changes by " + user.getName();
  std::string body = "Changes:\n" + info.toString();

  return std::make_unique<Message>(_user, to, subject, body);
}

bool Email::sendMessage(std::unique_ptr<Message> &&msg) {
  //use boost asio
  return _sendCallback(_server, _port, _user, _password, std::move(msg));
}

