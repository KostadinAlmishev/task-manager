//
// Created by Konstantin Pronin on 19.12.2019.
//

#include <curl/curl.h>
#include "CurlCallbacks.h"

std::vector<std::string> CurlCallbacks::_payloadData = std::vector<std::string>();

CurlCallbacks::CurlCallbacks(std::string server, unsigned int port, std::string login, std::string password) :
    _server(server), _port(port), _login(login), _password(password) {}

bool CurlCallbacks::send(std::unique_ptr<Message> &&msg) {
  CURLcode result;
  CURL *curl = curl_easy_init();
  curl_slist *recipients = nullptr;
  recipients = curl_slist_append(recipients, msg->getTo().c_str());
  upload_status upload_ctx{0};
  initPayloadData(msg->getTo(), msg->getFrom(), msg->getSubject(), msg->getBody());

  if (curl) {
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, NULL);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_URL, _server.c_str());
    curl_easy_setopt(curl, CURLOPT_USERNAME, _login.c_str());
    curl_easy_setopt(curl, CURLOPT_PASSWORD, _password.c_str());
    curl_easy_setopt(curl, CURLOPT_MAIL_FROM, msg->getFrom().c_str());
    curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);
    curl_easy_setopt(curl, CURLOPT_USE_SSL, (long)CURLUSESSL_ALL);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
    curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_callback);
    curl_easy_setopt(curl, CURLOPT_READDATA, &upload_ctx);
    curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    curl_easy_setopt(curl, CURLOPT_SSLVERSION, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_SESSIONID_CACHE, 0L);

    result = curl_easy_perform(curl);

    curl_slist_free_all(recipients);
    curl_easy_cleanup(curl);
    _payloadData.clear();
    return result == CURLE_OK;
  }

  return false;
}

size_t CurlCallbacks::read_callback(void *ptr, size_t size, size_t nmemb, void *userp) {
  auto *upload_ctx = (struct upload_status *)userp;
  const char *data;

  if((size == 0) || (nmemb == 0) || ((size*nmemb) < 1)) {
    return 0;
  }

  data = CurlCallbacks::_payloadData.at(upload_ctx->lines_read).c_str();

  if(strcmp(data, "") != 0) {
    size_t len = strlen(data);
    memcpy(ptr, data, len);
    upload_ctx->lines_read++;

    return len;
  }

  return 0;
}

void CurlCallbacks::initPayloadData(std::string to, std::string from, std::string subject, std::string body) {
  _payloadData.push_back("To: " + to + "\r\n");
  _payloadData.push_back("From: " + from + "\r\n");
  _payloadData.push_back("Subject: " + subject + "\r\n");
  _payloadData.push_back("\r\n");
  _payloadData.push_back("#" + body);
  _payloadData.push_back("");
}

size_t CurlCallbacks::write_data(void *buffer, size_t size, size_t nmemb, void *userp) {
  return size * nmemb;
}

