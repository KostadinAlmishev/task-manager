//
// Created by Konstantin Pronin on 19.12.2019.
//

#ifndef TASKMANAGER_EXAMPLE_INCLUDE_BOOSTEMAILCALLBACKS_H_
#define TASKMANAGER_EXAMPLE_INCLUDE_BOOSTEMAILCALLBACKS_H_
#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <boost/archive/iterators/ostream_iterator.hpp>
#include <tracking/Message.h>

using boost::asio::ip::tcp;
using namespace boost::archive::iterators;
typedef base64_from_binary<transform_width<const char *, 6, 8> > base64_text;

class BoostEmailCallbacks {
 private:
  std::string _server;
  unsigned int _port;
  std::string _user;
  std::string _password;
  std::string _from;
  std::string _to;
  std::string _subject;
  std::string _body;
  boost::asio::io_service _ioService;
  tcp::resolver _resolver;
  tcp::socket _socket;
  boost::asio::streambuf _request;
  boost::asio::streambuf _response;
  bool _isError;
  std::string _errorMsg;

  std::string encodeBase64(std::string data);
  void writeLine(std::string data);
  void handleResolve(const boost::system::error_code &error, tcp::resolver::iterator endpointIterator);
  void handleConnect(const boost::system::error_code &error, tcp::resolver::iterator endpointIterator);

 public:
  BoostEmailCallbacks(std::string, unsigned int, std::string, std::string);
  bool send(std::unique_ptr<Message> &&);
};

#endif //TASKMANAGER_EXAMPLE_INCLUDE_BOOSTEMAILCALLBACKS_H_
