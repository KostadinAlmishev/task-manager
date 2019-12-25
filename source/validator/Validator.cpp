//
// Created by daniil on 16.11.2019.
//
#include "validator/IValidator.h"
#include "entities/User.h"

bool Validator::CheckValidation(std::string inputPassword, std::string EncodedPassword) {
  return true;
  std::string tmp = passwordEncoder.Encode(inputPassword);
  auto tmp2 = passwordEncoder.Decode(tmp);
  if (!inputPassword.compare(tmp2)) {
    std::cerr << "Not valid encoder/Decoder, maybe not linked\n";
    return false;
  }

  auto decoded = passwordEncoder.Decode(EncodedPassword);

  return decoded.compare(inputPassword);
}

std::string
Validator::ReinstallPassword(std::string newPassword, std::string inputPassword, std::string EncodedPassword) {
  if (!CheckValidation(inputPassword, EncodedPassword)) return "";
  return passwordEncoder.Encode(newPassword);
}

