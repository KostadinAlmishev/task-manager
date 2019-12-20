//
// Created by Konstantin Pronin on 19.12.2019.
//

#include "BoostEmailCallbacks.h"

BoostEmailCallbacks::BoostEmailCallbacks(std::string server, unsigned int port, std::string user, std::string password) :
    _server(server), _port(port), _user(user), _password(password), _socket(_ioService), _resolver(_ioService) {
  tcp::resolver::query query(_server, std::to_string(_port));
  _resolver.async_resolve(query, boost::bind(&BoostEmailCallbacks::handleResolve, this, boost::asio::placeholders::error,
                                             boost::asio::placeholders::iterator));
}

std::string BoostEmailCallbacks::encodeBase64(std::string data) {
  std::stringstream os;
  size_t dataSize = data.size();
  std::copy(base64_text(data.c_str()), base64_text(data.c_str() + dataSize), ostream_iterator<char>(os));
  return os.str();
}

void BoostEmailCallbacks::writeLine(std::string data) {
  std::ostream requestStream(&_request);
  requestStream << data << "\r\n";
  boost::asio::write(_socket, _request);
  requestStream.clear();
}

void BoostEmailCallbacks::handleResolve(const boost::system::error_code &error, tcp::resolver::iterator endpointIterator) {
  if (!error) {
    tcp::endpoint endpoint = *endpointIterator;
    _socket.async_connect(endpoint,
                          boost::bind(&BoostEmailCallbacks::handleConnect,
                                      this,
                                      boost::asio::placeholders::error,
                                      ++endpointIterator));
  } else {
    _isError = true;
    _errorMsg = error.message();
  }
}

void BoostEmailCallbacks::handleConnect(const boost::system::error_code &error, tcp::resolver::iterator endpointIterator) {
  if (!error) {
    std::ostream requestStream(&_request);
    writeLine("EHLO " + _server);
    writeLine("AUTH LOGIN");
    writeLine(encodeBase64(_user));
    writeLine(encodeBase64(_password));
    writeLine("MAIL FROM:<" + _from + ">");
    writeLine("RCPT TO:<" + _to + ">");
    writeLine("DATA");
    writeLine("SUBJECT:" + _subject);
    writeLine("From:" + _from);
    writeLine("To:" + _to);
    writeLine("");
    writeLine(_body);
    writeLine(".\r\n");
  } else {
    _isError = true;
    _errorMsg = error.message();
  }
}

bool BoostEmailCallbacks::send(std::unique_ptr<Message> &&message) {
  _from = message->getFrom();
  _to = message->getTo();
  _subject = message->getSubject();
  _body = message->getBody();
  _ioService.run();
  return !_isError;
}



