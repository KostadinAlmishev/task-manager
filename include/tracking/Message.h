//
// Created by Konstantin Pronin on 09.11.2019.
//

#ifndef TASKMANAGER_INCLUDE_TRACKING_MESSAGE_H_
#define TASKMANAGER_INCLUDE_TRACKING_MESSAGE_H_

#include <string>

class Message {
 private:
  std::string _from;
  std::string _to;
  std::string _subject;
  std::string _body;
 public:
  Message(std::string from, std::string to, std::string subject, std::string body);

  std::string getFrom() const;
  std::string getTo() const;
  std::string getSubject() const;
  std::string getBody() const;
};

#endif //TASKMANAGER_INCLUDE_TRACKING_MESSAGE_H_
