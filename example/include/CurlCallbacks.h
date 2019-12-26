//
// Created by Konstantin Pronin on 19.12.2019.
//

#ifndef TASKMANAGER_EXAMPLE_INCLUDE_CURLCALLBACKS_H_
#define TASKMANAGER_EXAMPLE_INCLUDE_CURLCALLBACKS_H_

#include <string>
#include <vector>
#include "tracking/Message.h"

struct upload_status {
  int lines_read;
};

class CurlCallbacks {
 private:
  static std::vector<std::string> _payloadData;
  static void initPayloadData(std::string, std::string, std::string, std::string);
  std::string _server;
  unsigned int _port;
  std::string _login;
  std::string _password;

 public:
  CurlCallbacks(std::string, unsigned int, std::string, std::string);
  bool send(std::unique_ptr<Message> &&msg);
  static size_t read_callback(void *ptr, size_t size, size_t nmemb, void *userp);
  static size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp);
};

#endif //TASKMANAGER_EXAMPLE_INCLUDE_CURLCALLBACKS_H_
