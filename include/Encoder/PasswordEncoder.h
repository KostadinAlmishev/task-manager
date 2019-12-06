//
// Created by daniil on 09.11.2019.
//

#ifndef TASK_MANAGER_PASSWORDENCODER_H
#define TASK_MANAGER_PASSWORDENCODER_H

#include "include/Encoder/Encoder.h"

class IPasswordEncoder{
protected:
    Encryptor  encryptor;
    Decryptor  decryptor;
    KeyGen keyGen = KeyGen(encryptor, decryptor);
public:


    virtual std::string Decode(std::string) = 0;
    virtual std::string Encode(std::string) = 0;
};
class PasswordEncoder: public IPasswordEncoder{
public:
     std::string Decode(std::string) override ;
     std::string Encode(std::string) override ;
};

#endif //TASK_MANAGER_PASSWORDENCODER_H