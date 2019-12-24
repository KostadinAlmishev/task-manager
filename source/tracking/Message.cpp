//
// Created by Konstantin Pronin on 30.11.2019.
//

#include <string>
#include <utility>

#include "tracking/Message.h"

Message::Message(std::string from, std::string to, std::string subject, std::string body) : _from(std::move(
    from)), _to(std::move(to)), _subject(std::move(subject)), _body(std::move(body)) {}

std::string Message::getFrom() const {
  return _from;
}

std::string Message::getTo() const {
  return _to;
}

std::string Message::getSubject() const {
  return _subject;
}

std::string Message::getBody() const {
  return _body;
}
