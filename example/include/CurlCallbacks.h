//
// Created by Konstantin Pronin on 19.12.2019.
//

#ifndef TASKMANAGER_EXAMPLE_INCLUDE_CURLCALLBACKS_H_
#define TASKMANAGER_EXAMPLE_INCLUDE_CURLCALLBACKS_H_

#include <string>
#include <vector>
#include "tracking/Message.h"

static const char *payload_text[] = {
    "Date: Mon, 29 Nov 2010 21:54:29 +1100\r\n",
    "To: abc\r\n",
    "From: qwe\r\n",
    "Message-ID: <dcd7cb36-11db-487a-9f3a-e652a9458efd@"
    "rfcpedant.example.org>\r\n",
    "Subject: SMTP example message\r\n",
    "\r\n", /* empty line to divide headers from body, see RFC5322 */
    "The body of the message starts here.\r\n",
    "\r\n",
    "It could be a lot of lines, could be MIME encoded, whatever.\r\n",
    "Check RFC5322.\r\n",
    NULL
};

struct upload_status {
  int lines_read;
};

class CurlCallbacks {
 private:
  std::string _server;
  unsigned int _port;
  std::string _login;
  std::string _password;

  static std::vector<std::string> _payloadData;
  static void initPayloadData(std::string, std::string, std::string, std::string);
 public:
  CurlCallbacks(std::string, unsigned int, std::string, std::string);
  bool send(std::unique_ptr<Message> &&msg);
  static size_t read_callback(void *ptr, size_t size, size_t nmemb, void *userp);
};

#endif //TASKMANAGER_EXAMPLE_INCLUDE_CURLCALLBACKS_H_
