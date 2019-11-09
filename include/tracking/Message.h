//
// Created by Konstantin Pronin on 09.11.2019.
//

#ifndef TASKMANAGER_INCLUDE_TRACKING_MESSAGE_H_
#define TASKMANAGER_INCLUDE_TRACKING_MESSAGE_H_

class Message {
 private:
  std::string subject;
  std::string body;
 public:
  virtual std::string toString() const;
};

#endif //TASKMANAGER_INCLUDE_TRACKING_MESSAGE_H_
