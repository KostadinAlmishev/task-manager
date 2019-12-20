//
// Created by Konstantin Pronin on 05.11.2019.
//

#ifndef TASKMANAGER_INCLUDE_TRACKING_EMAIL_H_
#define TASKMANAGER_INCLUDE_TRACKING_EMAIL_H_

#include <memory>

#include "tracking/Message.h"
#include "tracking/Subscriber.h"
#include <entities/User.h>

template<typename Callback>
class Email : public Subscriber {
 private:
  std::string _server;
  unsigned int _port;
  std::string _user;
  std::string _password;
 public:
  Email(std::string, unsigned int, std::string, std::string);
  void update(const User &, const Entity &) override;
  virtual std::unique_ptr<Message> createMessage(const User &, const Entity &) const;
  virtual bool sendMessage(std::unique_ptr<Message> &&);
};

template<typename Callback>
Email<Callback>::Email(std::string server, unsigned int port, std::string user, std::string password) :
    _server(server), _port(port), _user(user), _password(password) {}

template<typename Callback>
void Email<Callback>::update(const User &user, const Entity &current) {
  auto msg = createMessage(user, current);
  sendMessage(std::move(msg));
}

template<typename Callback>
std::unique_ptr<Message> Email<Callback>::createMessage(const User &user, const Entity &info) const {
  std::string to = user.getEmail();
  std::string subject = "Changes by " + user.getName();
  std::string body = "Changes:\n" + info.toString();

  return std::make_unique<Message>(_user, to, subject, body);
}

template<typename Callback>
bool Email<Callback>::sendMessage(std::unique_ptr<Message> &&msg) {
  Callback callback(_server, _port, _user, _password);
  return callback.send(std::move(msg));
}

#endif //TASKMANAGER_INCLUDE_TRACKING_EMAIL_H_
