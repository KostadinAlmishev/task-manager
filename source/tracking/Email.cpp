//
// Created by Konstantin Pronin on 30.11.2019.
//


#include "tracking/Email.h"
#include "entity/User.h"

void Email::update(const Entity & user, const Entity & current) {
  auto msg = createMessage(user, current);
  sendMessage(std::move(msg));
}

std::unique_ptr<Message> Email::createMessage(const Entity &user, const Entity &info) const {
  User castUser = dynamic_cast<const User&> (user);
  std::string to = castUser.getEmail();
  std::string subject = "Changes by " + castUser.getName();
  std::string body = "Changes:\n" + info.toString();

  return std::make_unique<Message>(_user, to, subject, body);
}

bool Email::sendMessage(std::unique_ptr<Message> &&msg) {
  //use boost asio
  return _sendCallback(_server, _port, _user, _password, std::move(msg));
}

