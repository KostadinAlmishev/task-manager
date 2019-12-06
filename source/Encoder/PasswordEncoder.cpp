//
// Created by daniil on 09.11.2019.
//

#include "include/Encoder/PasswordEncoder.h"
std::string PasswordEncoder::Decode(std::string input) {
    return decryptor.Execute(input);
}
std::string PasswordEncoder::Encode(std::string input) {
    return encryptor.Execute(input);
}

